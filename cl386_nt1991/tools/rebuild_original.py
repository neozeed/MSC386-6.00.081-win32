#!/usr/bin/env python3
from pathlib import Path
import subprocess,sys,hashlib
root=Path(__file__).resolve().parents[1]
subprocess.check_call([sys.executable,str(root/'tools'/'build_text.py'),str(root/'src'/'cl386_nt1991_code.asm'),str(root/'build'/'text_segment.bin')])
t=bytearray((root/'parts'/'original_image_template_text_zeroed.bin').read_bytes())
code=(root/'build'/'text_segment.bin').read_bytes(); off=0x400
assert len(code)==0x8a00
t[off:off+len(code)]=code
out=root/'build'/'CL386-original-rebuilt.EXE';out.write_bytes(t)
print(out,hashlib.sha256(t).hexdigest())
