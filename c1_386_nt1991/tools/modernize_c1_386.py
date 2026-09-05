#!/usr/bin/env python3
"""Convert the Dec-1991 transitional PE C1_386 into a modern PE32 image.

Changes:
  * normalize obsolete COFF/PE characteristics and section VirtualSize fields
  * rebase preferred image 0x00010000 -> 0x00400000, applying the delta at
    every validated old type-3 relocation site
  * convert the Dec-1991 12-byte relocation records into current page-block
    IMAGE_BASE_RELOCATION/HIGHLOW records
  * redirect both BASE.DLL and NTDLL.DLL import descriptors to C1_386COMPAT.DLL

Compiler code is otherwise unchanged.
"""
from pathlib import Path
import struct, collections, argparse

def main(src:Path,out:Path):
    b=bytearray(src.read_bytes())
    pe=struct.unpack_from('<I',b,0x3c)[0]; assert b[pe:pe+4]==b'PE\0\0'
    fh=pe+4
    machine,nsec,timestamp,symptr,nsyms,optsz,chars=struct.unpack_from('<HHIIIHH',b,fh)
    assert machine==0x14c and nsec==8 and optsz==0xa8
    opt=fh+20; assert struct.unpack_from('<H',b,opt)[0]==0x10b
    oldbase=struct.unpack_from('<I',b,opt+28)[0]; assert oldbase==0x10000
    newbase=0x400000; delta=newbase-oldbase
    struct.pack_into('<I',b,opt+28,newbase)
    struct.pack_into('<H',b,fh+18,0x0102)  # executable + 32-bit, relocations retained
    struct.pack_into('<HH',b,opt+40,4,0)
    struct.pack_into('<HH',b,opt+48,4,0)

    sh=opt+optsz; secs=[]
    for i in range(nsec):
        o=sh+i*40; name=bytes(b[o:o+8]).split(b'\0')[0].decode('ascii')
        oldfirst,rva,rawsz,rawptr,relptr,lineptr,nrel,nline,ch=struct.unpack_from('<IIIIIIHHI',b,o+8)
        secs.append(dict(i=i,name=name,hdr=o,rva=rva,rawsz=rawsz,rawptr=rawptr,ch=ch))
        # old first field was PhysicalAddress and is zero in this image; modern PE uses VirtualSize
        vsize = 0x7e00 if name=='.bss' else rawsz
        struct.pack_into('<I',b,o+8,vsize)
        if name in ('.reloc','.debug'):
            struct.pack_into('<I',b,o+36,ch|0x02000000)

    def one(name):
        xs=[s for s in secs if s['name']==name]; assert len(xs)==1,(name,len(xs)); return xs[0]
    def rvaoff(rva):
        for s in secs:
            if s['rawptr'] and s['rva']<=rva<s['rva']+s['rawsz']:
                return s['rawptr']+(rva-s['rva'])
        raise ValueError(f'RVA not file-backed: {rva:#x}')

    # Imports: structure is already recognizable PE, only the providing DLL/ABI is obsolete.
    idata=one('.idata'); ioff=idata['rawptr']
    for d in (0,1): struct.pack_into('<I',b,ioff+d*20+4,0)  # clear obsolete bind stamps
    compat=b'C1_386COMPAT.DLL\0'
    # Known unused zero tail in this image's .idata (verified at conversion time).
    local=0x2d0; assert local+len(compat)<=idata['rawsz']
    assert all(x==0 for x in b[ioff+local:ioff+local+len(compat)])
    b[ioff+local:ioff+local+len(compat)]=compat
    compat_rva=idata['rva']+local
    struct.pack_into('<I',b,ioff+12,compat_rva)
    struct.pack_into('<I',b,ioff+20+12,compat_rva)

    # Transitional relocation directory: second DWORD is count of 12-byte records.
    dd=opt+96+5*8; old_rva,old_count=struct.unpack_from('<II',b,dd)
    assert old_rva==0x90000 and old_count==0x19ff
    rs=one('.reloc'); assert old_count*12<=rs['rawsz']
    relsites=[]
    for i in range(old_count):
        va,value,typ,pad=struct.unpack_from('<IIHH',b,rs['rawptr']+i*12)
        assert pad==0
        if typ==0: continue
        assert typ==3,(i,typ)
        o=rvaoff(va); actual=struct.unpack_from('<I',b,o)[0]
        assert actual==oldbase+value,(i,hex(va),hex(actual),hex(value))
        # Rebase file contents to the new preferred ImageBase.
        struct.pack_into('<I',b,o,(actual+delta)&0xffffffff)
        relsites.append(va)

    pages=collections.defaultdict(list)
    for va in relsites: pages[va&~0xfff].append((3<<12)|(va&0xfff))
    nr=bytearray()
    for page in sorted(pages):
        words=sorted(pages[page])
        if len(words)&1: words.append(0)
        nr+=struct.pack('<II',page,8+2*len(words))
        nr+=struct.pack('<'+'H'*len(words),*words)
    assert len(nr)<=rs['rawsz']
    b[rs['rawptr']:rs['rawptr']+rs['rawsz']]=nr+b'\0'*(rs['rawsz']-len(nr))
    struct.pack_into('<II',b,dd,old_rva,len(nr))
    struct.pack_into('<I',b,rs['hdr']+8,len(nr))

    out.write_bytes(b)
    print(f'{out}: {len(relsites)} HIGHLOW relocations, {len(pages)} pages, reloc size {len(nr):#x}, ImageBase {newbase:#x}')

if __name__=='__main__':
    ap=argparse.ArgumentParser(); ap.add_argument('input',type=Path); ap.add_argument('output',type=Path); a=ap.parse_args(); main(a.input,a.output)
