#!/usr/bin/env python3
from pathlib import Path
import subprocess,sys
root=Path(__file__).resolve().parent.parent
listing=root/'src/c2_386_nt1991_annotated.asm'
tmp=root/'build/text_from_listing.bin'
subprocess.check_call([sys.executable,str(root/'tools/assemble_listing.py'),str(listing),str(tmp)])
b=bytearray((root/'parts/original_image_template_text_zeroed.bin').read_bytes()); t=tmp.read_bytes()
assert len(t)==0x59600
b[0x400:0x59a00]=t
out=root/'build/C2_386_rebuilt.EXE'; out.write_bytes(b); print(out)
