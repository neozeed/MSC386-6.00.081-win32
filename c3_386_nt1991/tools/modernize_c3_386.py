#!/usr/bin/env python3
"""Modernize the Dec-1991 transitional PE C3_386 image for 32-bit Win32.

Changes are deliberately narrow:
  * expand the shortened 0xA8/9-directory prototype optional header to the
    canonical PE32 0xE0/16-directory form;
  * normalize old PE/COFF header/section semantics;
  * preserve the historical preferred ImageBase 0x00010000;
  * convert the 12-byte pre-release relocation records to modern HIGHLOW blocks;
  * preserve the original .reloc mapped extent after compacting the relocation
    payload, avoiding 64-KB virtual holes rejected by native Windows;
  * redirect BASE.DLL and NTDLL.DLL imports to C3_386COMPAT.DLL.

The compiler's .text is otherwise unchanged.  This form is validated on
64-bit Windows 10 (build 19045) in the complete CL386/C1/C2/C3 pipeline.
"""
from pathlib import Path
import struct,collections,argparse

def main(src:Path,out:Path):
    b=bytearray(src.read_bytes())
    pe=struct.unpack_from('<I',b,0x3c)[0]; assert b[pe:pe+4]==b'PE\0\0'
    fh=pe+4
    machine,nsec,ts,symptr,nsyms,optsz,chars=struct.unpack_from('<HHIIIHH',b,fh)
    assert machine==0x14c and nsec==7 and optsz==0xa8
    opt=fh+20; assert struct.unpack_from('<H',b,opt)[0]==0x10b
    oldbase=struct.unpack_from('<I',b,opt+28)[0]; assert oldbase==0x10000

    # Canonicalize the shortened Dec-1991 PE32 optional header.  The prototype
    # uses SizeOfOptionalHeader=0xA8 and only 9 data directories.  Contemporary
    # PE32 normally uses 0xE0/16.  There is sufficient zero/header slack before
    # the first raw section, so move only the section-table headers; section raw
    # data and all file offsets remain unchanged.
    old_sh=opt+optsz
    old_section_table=bytes(b[old_sh:old_sh+nsec*40])
    raw_ptrs=[struct.unpack_from('<I',old_section_table,i*40+20)[0] for i in range(nsec)]
    first_raw=min(x for x in raw_ptrs if x)
    new_optsz=0xe0; new_sh=opt+new_optsz
    assert new_sh+nsec*40<=first_raw
    b[new_sh:new_sh+nsec*40]=old_section_table
    b[old_sh:new_sh]=b'\0'*(new_sh-old_sh)
    struct.pack_into('<H',b,fh+16,new_optsz)
    struct.pack_into('<I',b,opt+92,16)
    b[opt+96+9*8:opt+96+16*8]=b'\0'*(7*8)
    optsz=new_optsz
    newbase=oldbase; delta=0

    # Normalize enough legacy header fields for a contemporary PE32 loader.
    struct.pack_into('<H',b,fh+18,0x0102)   # executable, 32-bit; relocs retained
    struct.pack_into('<HH',b,opt+40,4,0)    # OS version 4.0
    struct.pack_into('<HH',b,opt+48,4,0)    # subsystem version 4.0

    sh=opt+optsz; secs=[]
    for i in range(nsec):
        o=sh+i*40
        name=bytes(b[o:o+8]).split(b'\0')[0].decode('ascii')
        oldfirst,rva,rawsz,rawptr,relptr,lineptr,nrel,nline,ch=struct.unpack_from('<IIIIIIHHI',b,o+8)
        secs.append(dict(i=i,name=name,hdr=o,rva=rva,rawsz=rawsz,rawptr=rawptr,ch=ch))
        # In this 1991 image the first section DWORD is zero; modern PE reads it as VirtualSize.
        vsize=rawsz
        if name=='.bss':
            vsize=rawsz
            struct.pack_into('<I',b,o+16,0) # virtual-only BSS
        struct.pack_into('<I',b,o+8,vsize)
        if name in ('.reloc','.debug'):
            struct.pack_into('<I',b,o+36,ch|0x02000000) # discardable

    def one(name):
        xs=[s for s in secs if s['name']==name]; assert len(xs)==1,(name,len(xs)); return xs[0]
    def rvaoff(rva):
        for s in secs:
            if s['rawptr'] and s['rva']<=rva<s['rva']+s['rawsz']:
                return s['rawptr']+(rva-s['rva'])
        raise ValueError(f'RVA not file-backed: {rva:#x}')

    # Redirect both import descriptors to one cdecl compatibility DLL. Existing thunk/name tables stay intact.
    idata=one('.idata'); ioff=idata['rawptr']
    descriptors=[]; d=0
    while True:
        vals=struct.unpack_from('<IIIII',b,ioff+d*20)
        if not any(vals): break
        descriptors.append(ioff+d*20); d+=1
    assert len(descriptors)==2
    compat=b'C3_386COMPAT.DLL\0'
    # Find a naturally zero-filled slot after the original import-name strings.
    local=None
    for candidate in range(0x260,idata['rawsz']-len(compat)+1,4):
        if all(x==0 for x in b[ioff+candidate:ioff+candidate+len(compat)]):
            local=candidate; break
    assert local is not None
    b[ioff+local:ioff+local+len(compat)]=compat
    compat_rva=idata['rva']+local
    for doff in descriptors:
        struct.pack_into('<I',b,doff+4,0)       # remove old bind timestamp
        struct.pack_into('<I',b,doff+12,compat_rva)

    # Transitional relocation directory: second DWORD is a COUNT of 12-byte records.
    dd=opt+96+5*8
    old_rva,old_count=struct.unpack_from('<II',b,dd)
    rs=one('.reloc'); assert old_rva==rs['rva']; assert old_count*12<=rs['rawsz']
    relsites=[]
    for i in range(old_count):
        va,value,typ,pad=struct.unpack_from('<IIHH',b,rs['rawptr']+i*12)
        assert pad==0
        if typ==0: continue
        assert typ==3,(i,typ)
        o=rvaoff(va); actual=struct.unpack_from('<I',b,o)[0]
        assert actual==oldbase+value,(i,hex(va),hex(actual),hex(value))
        struct.pack_into('<I',b,o,(actual+delta)&0xffffffff)
        relsites.append(va)

    pages=collections.defaultdict(list)
    for va in relsites:
        pages[va&~0xfff].append((3<<12)|(va&0xfff))
    nr=bytearray()
    for page in sorted(pages):
        words=sorted(pages[page])
        if len(words)&1: words.append(0)
        nr+=struct.pack('<II',page,8+2*len(words))
        nr+=struct.pack('<'+'H'*len(words),*words)
    assert len(nr)<=rs['rawsz']
    b[rs['rawptr']:rs['rawptr']+rs['rawsz']]=nr+b'\0'*(rs['rawsz']-len(nr))
    struct.pack_into('<II',b,dd,rs['rva'],len(nr))
    # The relocation DIRECTORY contains only len(nr) bytes, but the SECTION's
    # mapped extent must remain the original allocation. Shrinking VirtualSize
    # creates SectionAlignment-sized RVA gaps that Wine tolerates but Windows 10
    # rejects during CreateProcess (ERROR_ACCESS_DENIED).
    struct.pack_into('<I',b,rs['hdr']+8,rs['rawsz'])

    section_alignment=struct.unpack_from('<I',b,opt+32)[0]
    align=lambda x,a:(x+a-1)&~(a-1)
    mapped=[]
    for s in secs:
        vs=struct.unpack_from('<I',b,s['hdr']+8)[0]
        mapped.append((s['name'],s['rva'],vs))
    for (n0,r0,v0),(n1,r1,v1) in zip(mapped,mapped[1:]):
        assert align(r0+v0,section_alignment)==r1, (n0,n1,hex(r0),hex(v0),hex(r1))
    size_image=struct.unpack_from('<I',b,opt+56)[0]
    assert align(mapped[-1][1]+mapped[-1][2],section_alignment)==size_image

    out.write_bytes(b)
    print(f'{out}: {len(relsites)} HIGHLOW relocations in {len(pages)} pages; reloc bytes={len(nr):#x}; ImageBase={newbase:#x}; compat name RVA={compat_rva:#x}')

if __name__=='__main__':
    ap=argparse.ArgumentParser(); ap.add_argument('input',type=Path); ap.add_argument('output',type=Path); a=ap.parse_args(); main(a.input,a.output)
