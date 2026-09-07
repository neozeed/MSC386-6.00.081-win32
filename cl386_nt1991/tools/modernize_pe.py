#!/usr/bin/env python3
"""Convert the Dec-1991 transitional PE used by CL386 to a modern-loadable PE32.

This does NOT rewrite compiler code. It canonicalizes the shortened prototype
PE32 header, normalizes old PE/COFF section and base-relocation metadata, and
redirects the two imported system DLL descriptors to CL386COMPAT.DLL, which
adapts the early NT cdecl API ABI to modern Win32.  The original ImageBase and
original .reloc mapped extent are deliberately preserved.
"""
from pathlib import Path
import struct, collections, argparse

def main(src: Path, out: Path):
    b=bytearray(src.read_bytes())
    pe=struct.unpack_from('<I',b,0x3c)[0]
    assert b[pe:pe+4]==b'PE\0\0'
    fh=pe+4
    machine,nsec,timestamp,symptr,nsyms,optsz,chars=struct.unpack_from('<HHIIIHH',b,fh)
    assert machine==0x14c and nsec==6 and optsz==0xa8
    opt=fh+20; assert struct.unpack_from('<H',b,opt)[0]==0x10b
    imagebase=struct.unpack_from('<I',b,opt+28)[0]
    assert imagebase==0x10000

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

    # Modern COFF executable/i386 flags. Preserve relocations (not stripped).
    struct.pack_into('<H',b,fh+18,0x0102)
    # Give modern loaders non-zero NT/subsystem version targets.
    struct.pack_into('<HH',b,opt+40,4,0) # Major/MinorOperatingSystemVersion
    struct.pack_into('<HH',b,opt+48,4,0) # Major/MinorSubsystemVersion

    sh=opt+optsz; sec={}
    for i in range(nsec):
        o=sh+i*40
        name=bytes(b[o:o+8]).split(b'\0')[0].decode('ascii')
        phys,va,rawsz,rawptr,relptr,lineptr,nrel,nline,ch=struct.unpack_from('<IIIIIIHHI',b,o+8)
        sec[name]=(o,va,rawsz,rawptr,ch)
        # In this prototype header the first field was PhysicalAddress (zero).
        # In current PE it is VirtualSize. Recover it from old raw/memory sizes.
        if name=='.bss':
            struct.pack_into('<I',b,o+8,0x0c00)
            struct.pack_into('<I',b,o+16,0) # modern BSS has no raw bytes
            struct.pack_into('<I',b,o+20,0)
        else:
            struct.pack_into('<I',b,o+8,rawsz)
        if name in ('.reloc','.debug'):
            struct.pack_into('<I',b,o+36,ch|0x02000000) # discardable metadata

    def rva_to_off(rva):
        for name,(o,va,rawsz,rawptr,ch) in sec.items():
            if rawptr and va <= rva < va+rawsz:
                return rawptr+(rva-va)
        raise ValueError(f'RVA not file-backed: {rva:#x}')

    # The import layout is already recognisably PE, but the ABI behind base.dll
    # predates modern x86 WINAPI/stdcall. Redirect both descriptors to one
    # compatibility DLL while leaving all imported function names untouched.
    idata=sec['.idata'][3]
    for desc in (0,1):
        struct.pack_into('<I',b,idata+desc*20+4,0) # discard obsolete bind timestamps
    compat_rva=0x403a0
    compat=b'CL386COMPAT.DLL\0'
    co=rva_to_off(compat_rva)
    b[co:co+len(compat)]=compat
    struct.pack_into('<I',b,idata+12,compat_rva)
    struct.pack_into('<I',b,idata+20+12,compat_rva)

    # Old Dec-1991 relocation table:
    #   ULONG VirtualAddress; ULONG Value; USHORT Type; USHORT pad
    # and data-directory second DWORD == number of entries.
    # Convert type 3 entries to current IMAGE_BASE_RELOCATION page blocks.
    dd=opt+96+5*8
    old_rva,old_count=struct.unpack_from('<II',b,dd)
    assert (old_rva,old_count)==(0x50000,0x88b)
    relraw=sec['.reloc'][3]; relalloc=sec['.reloc'][2]
    rels=[]
    for i in range(old_count):
        va,value,typ,pad=struct.unpack_from('<IIHH',b,relraw+i*12)
        if typ==0: continue
        assert typ==3 and pad==0
        # The old format's Value is the RVA-like value to which image base is added.
        try: so=rva_to_off(va)
        except ValueError: so=None
        if so is not None:
            actual=struct.unpack_from('<I',b,so)[0]
            assert actual==imagebase+value, (hex(va),hex(actual),hex(value))
        rels.append(va)
    pages=collections.defaultdict(list)
    for va in rels: pages[va & ~0xfff].append((3<<12)|(va&0xfff))
    nr=bytearray()
    for page in sorted(pages):
        words=sorted(pages[page])
        if len(words)&1: words.append(0) # IMAGE_REL_BASED_ABSOLUTE padding
        nr += struct.pack('<II',page,8+2*len(words))
        nr += struct.pack('<'+'H'*len(words),*words)
    assert len(nr)<=relalloc
    b[relraw:relraw+relalloc]=nr+b'\0'*(relalloc-len(nr))
    struct.pack_into('<II',b,dd,old_rva,len(nr))
    # Keep the compact relocation-directory size above, but retain the original
    # .reloc mapped extent. CL386 happened to fit in one 64-KB alignment unit, so
    # the old bug did not prevent it launching; preserving the extent keeps all
    # four compiler components structurally consistent.
    struct.pack_into('<I',b,sec['.reloc'][0]+8,relalloc)

    section_alignment=struct.unpack_from('<I',b,opt+32)[0]
    align=lambda x,a:(x+a-1)&~(a-1)
    mapped=[]
    sh=opt+optsz
    for i in range(nsec):
        o=sh+i*40
        name=bytes(b[o:o+8]).split(b'\0')[0].decode('ascii')
        vs,rva=struct.unpack_from('<II',b,o+8)
        mapped.append((name,rva,vs))
    for (n0,r0,v0),(n1,r1,v1) in zip(mapped,mapped[1:]):
        assert align(r0+v0,section_alignment)==r1, (n0,n1,hex(r0),hex(v0),hex(r1))
    size_image=struct.unpack_from('<I',b,opt+56)[0]
    assert align(mapped[-1][1]+mapped[-1][2],section_alignment)==size_image

    out.write_bytes(b)
    print(f'{out}: {len(b)} bytes; {len(rels)} HIGHLOW relocations in {len(pages)} blocks ({len(nr):#x} bytes)')

if __name__=='__main__':
    ap=argparse.ArgumentParser()
    ap.add_argument('input',type=Path)
    ap.add_argument('output',type=Path)
    a=ap.parse_args(); main(a.input,a.output)
