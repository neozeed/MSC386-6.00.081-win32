#!/usr/bin/env python3
"""Modernize a December-1991 transitional NT PE32 image.

Unlike the older C1/C2/C3 scripts, this is not tied to one executable's
section count or preferred image base.

It:
  * accepts the shortened 0xA8 / 9-directory prototype PE32 optional header;
  * expands it to the canonical 0xE0 / 16-directory PE32 header;
  * preserves the image's existing preferred ImageBase;
  * normalizes the old section VirtualSize convention;
  * converts the prototype 12-byte relocation records to modern HIGHLOW blocks;
  * redirects BASE.DLL and NTDLL.DLL imports to DEC1991COMPAT.DLL.

The compatibility DLL must be present beside the converted executable.
"""
from pathlib import Path
import struct, collections, argparse

COMPAT = b"DEC1991COMPAT.DLL\0"

def align(x,a): return (x+a-1)&~(a-1)

def main(src:Path,out:Path):
    b=bytearray(src.read_bytes())
    pe=struct.unpack_from("<I",b,0x3c)[0]
    assert b[pe:pe+4]==b"PE\0\0"
    fh=pe+4
    machine,nsec,ts,symptr,nsyms,optsz,chars=struct.unpack_from("<HHIIIHH",b,fh)
    assert machine==0x14c, hex(machine)
    assert optsz==0xa8, f"expected Dec-1991 0xa8 optional header, got {optsz:#x}"
    opt=fh+20
    assert struct.unpack_from("<H",b,opt)[0]==0x10b
    oldbase=struct.unpack_from("<I",b,opt+28)[0]
    ndirs=struct.unpack_from("<I",b,opt+92)[0]
    assert ndirs==9, f"expected 9 prototype directories, got {ndirs}"

    # Move only the section table; raw section offsets stay unchanged.
    old_sh=opt+optsz
    old_table=bytes(b[old_sh:old_sh+nsec*40])
    raw_ptrs=[struct.unpack_from("<I",old_table,i*40+20)[0] for i in range(nsec)]
    first_raw=min(x for x in raw_ptrs if x)
    new_optsz=0xe0
    new_sh=opt+new_optsz
    assert new_sh+nsec*40<=first_raw
    b[new_sh:new_sh+nsec*40]=old_table
    b[old_sh:new_sh]=b"\0"*(new_sh-old_sh)
    struct.pack_into("<H",b,fh+16,new_optsz)
    struct.pack_into("<I",b,opt+92,16)
    b[opt+96+9*8:opt+96+16*8]=b"\0"*(7*8)
    optsz=new_optsz

    # Normal PE32 executable, relocations retained.
    struct.pack_into("<H",b,fh+18,0x0102)
    struct.pack_into("<HH",b,opt+40,4,0)
    struct.pack_into("<HH",b,opt+48,4,0)

    sh=opt+optsz
    secs=[]
    for i in range(nsec):
        o=sh+i*40
        name=bytes(b[o:o+8]).split(b"\0")[0].decode("ascii")
        oldfirst,rva,rawsz,rawptr,relptr,lineptr,nrel,nline,ch=struct.unpack_from("<IIIIIIHHI",b,o+8)
        secs.append(dict(name=name,hdr=o,rva=rva,rawsz=rawsz,rawptr=rawptr,ch=ch))

        # Prototype section headers left this field zero. Modern PE interprets
        # it as VirtualSize. For BSS, old RawSize was really its virtual extent.
        vsize=rawsz
        if name==".bss":
            struct.pack_into("<I",b,o+16,0)  # SizeOfRawData = 0
        struct.pack_into("<I",b,o+8,vsize)
        if name in (".reloc",".debug"):
            struct.pack_into("<I",b,o+36,ch|0x02000000)

    def one(name):
        xs=[s for s in secs if s["name"]==name]
        assert len(xs)==1,(name,len(xs))
        return xs[0]
    def rvaoff(rva):
        for s in secs:
            if s["rawptr"] and s["rva"]<=rva<s["rva"]+s["rawsz"]:
                return s["rawptr"]+(rva-s["rva"])
        raise ValueError(f"RVA not file-backed: {rva:#x}")

    # Redirect each historical import descriptor to the compatibility DLL.
    idata=one(".idata")
    ioff=idata["rawptr"]
    descriptors=[]
    d=0
    while True:
        vals=struct.unpack_from("<IIIII",b,ioff+d*20)
        if not any(vals): break
        descriptors.append(ioff+d*20)
        d+=1
    assert descriptors, "no imports"

    # Find zero-filled room inside .idata for the new DLL name.
    local=None
    for candidate in range(0,idata["rawsz"]-len(COMPAT)+1):
        # Don't overwrite the import descriptors themselves.
        if candidate < (len(descriptors)+1)*20:
            continue
        if all(x==0 for x in b[ioff+candidate:ioff+candidate+len(COMPAT)]):
            local=candidate
            break
    assert local is not None, "no room in .idata for compatibility DLL name"
    b[ioff+local:ioff+local+len(COMPAT)]=COMPAT
    compat_rva=idata["rva"]+local
    for doff in descriptors:
        struct.pack_into("<I",b,doff+4,0)       # clear old bind timestamp
        struct.pack_into("<I",b,doff+12,compat_rva)

    # Prototype relocation directory: second DWORD is a RECORD COUNT.
    dd=opt+96+5*8
    old_rva,old_count=struct.unpack_from("<II",b,dd)
    rs=one(".reloc")
    assert old_rva==rs["rva"]
    assert old_count*12<=rs["rawsz"]
    relsites=[]
    for i in range(old_count):
        va,value,typ,pad=struct.unpack_from("<IIHH",b,rs["rawptr"]+i*12)
        assert pad==0
        if typ==0: continue
        assert typ==3,(i,typ)
        o=rvaoff(va)
        actual=struct.unpack_from("<I",b,o)[0]
        assert actual==oldbase+value,(i,hex(va),hex(actual),hex(oldbase+value))
        relsites.append(va)

    pages=collections.defaultdict(list)
    for va in relsites:
        pages[va&~0xfff].append((3<<12)|(va&0xfff))
    nr=bytearray()
    for page in sorted(pages):
        words=sorted(pages[page])
        if len(words)&1: words.append(0)
        nr+=struct.pack("<II",page,8+2*len(words))
        nr+=struct.pack("<"+"H"*len(words),*words)
    assert len(nr)<=rs["rawsz"]
    b[rs["rawptr"]:rs["rawptr"]+rs["rawsz"]]=nr+b"\0"*(rs["rawsz"]-len(nr))
    struct.pack_into("<II",b,dd,rs["rva"],len(nr))
    # Keep the section's full mapped extent; only the directory payload shrinks.
    struct.pack_into("<I",b,rs["hdr"]+8,rs["rawsz"])

    section_alignment=struct.unpack_from("<I",b,opt+32)[0]
    mapped=[]
    for s in secs:
        vs=struct.unpack_from("<I",b,s["hdr"]+8)[0]
        mapped.append((s["name"],s["rva"],vs))
    for (n0,r0,v0),(n1,r1,v1) in zip(mapped,mapped[1:]):
        assert align(r0+v0,section_alignment)==r1,(n0,n1,hex(r0),hex(v0),hex(r1))
    size_image=struct.unpack_from("<I",b,opt+56)[0]
    assert align(mapped[-1][1]+mapped[-1][2],section_alignment)==size_image

    # C3_386 Dec-1991 /Fa long-double formatter repair.
    #
    # The C3 CRT's __cfltcvt_init initializes __cfltcvt_tab[0..4] but leaves
    # [5] as __fptrap. printf/output.c uses [5] for 12-byte long double, and
    # C3's own assembly listing uses "%.32Le", causing R6002.
    #
    # Detect the exact C3 pattern rather than the filename. If present, append
    # a tiny adapter that converts the 12-byte value with C3's own ___ldtod
    # and then calls the ordinary __cfltcvt formatter. Object emission and the
    # exact hexadecimal DT payload are untouched; only the decimal comment is
    # reduced to double precision.
    C3_LDTOD=0x27e4a
    C3_INIT=0x282aa
    C3_CFLTCVT=0x287ba
    C3_FPTRAP=0x28ebe
    C3_TAB5=0x444b4
    c3_fix=False
    fix_rva=None
    try:
        sig_ldtod=bytes(b[rvaoff(C3_LDTOD):rvaoff(C3_LDTOD)+7])
        sig_init=bytes(b[rvaoff(C3_INIT):rvaoff(C3_INIT)+10])
        tab5=struct.unpack_from('<I',b,rvaoff(C3_TAB5))[0]
        c3_fix=(sig_ldtod==b'\x55\x8b\xec\x83\xec\x24\x66' and
                sig_init[:2]==b'\xc7\x05' and
                tab5==oldbase+C3_FPTRAP and
                b.find(b'%.32Le')!=-1 and
                C3_TAB5 in relsites)
    except ValueError:
        c3_fix=False

    if c3_fix:
        file_alignment=struct.unpack_from('<I',b,opt+36)[0]
        fix_rva=size_image                 # SizeOfImage is already section-aligned
        rawptr=align(len(b),file_alignment)
        if len(b)<rawptr:
            b+=b'\0'*(rawptr-len(b))

        code=bytearray()
        code += b'\x55\x8b\xec'          # push ebp ; mov ebp,esp
        code += b'\x83\xec\x08'          # sub esp,8
        code += b'\x8b\x45\x08'          # mov eax,[ebp+8]  (long double *)
        code += b'\xff\x70\x08'          # push [eax+8]
        code += b'\xff\x70\x04'          # push [eax+4]
        code += b'\xff\x30'              # push [eax]
        call_site=fix_rva+len(code)
        code += b'\xe8'+struct.pack('<i',C3_LDTOD-(call_site+5))
        code += b'\x83\xc4\x0c'          # add esp,12
        code += b'\xdd\x5d\xf8'          # fstp qword [ebp-8]
        code += b'\xff\x75\x18'          # push caps
        code += b'\xff\x75\x14'          # push precision
        code += b'\xff\x75\x10'          # push format char
        code += b'\xff\x75\x0c'          # push output buffer
        code += b'\x8d\x45\xf8\x50'      # lea eax,[ebp-8] ; push eax
        call_site=fix_rva+len(code)
        code += b'\xe8'+struct.pack('<i',C3_CFLTCVT-(call_site+5))
        code += b'\x83\xc4\x14'          # add esp,20
        code += b'\xc9\xc3'              # leave ; ret

        rawsz=align(len(code),file_alignment)
        b += code + b'\0'*(rawsz-len(code))

        new_hdr=sh+nsec*40
        size_headers=struct.unpack_from('<I',b,opt+60)[0]
        assert new_hdr+40<=size_headers
        b[new_hdr:new_hdr+40]=b'.c3fp\0\0\0'+struct.pack(
            '<IIIIIIHHI',len(code),fix_rva,rawsz,rawptr,0,0,0,0,0x60000020)
        struct.pack_into('<H',b,fh+2,nsec+1)
        struct.pack_into('<I',b,opt+56,align(fix_rva+len(code),section_alignment))
        old_size_code=struct.unpack_from('<I',b,opt+4)[0]
        struct.pack_into('<I',b,opt+4,old_size_code+rawsz)

        # This slot already had a HIGHLOW relocation because it originally
        # pointed to __fptrap. Keep the relocation and only change its target.
        struct.pack_into('<I',b,rvaoff(C3_TAB5),oldbase+fix_rva)
        nsec += 1

    out.write_bytes(b)
    extra=(f'; C3 /Fa long-double fix RVA={fix_rva:#x}' if c3_fix else '')
    print(f"{out}: sections={nsec}; {len(relsites)} HIGHLOW relocations in "
          f"{len(pages)} pages; ImageBase={oldbase:#x}; compat RVA={compat_rva:#x}{extra}")

if __name__=="__main__":
    ap=argparse.ArgumentParser()
    ap.add_argument("input",type=Path)
    ap.add_argument("output",type=Path)
    a=ap.parse_args()
    main(a.input,a.output)
