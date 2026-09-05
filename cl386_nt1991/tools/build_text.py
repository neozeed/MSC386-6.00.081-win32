#!/usr/bin/env python3
from pathlib import Path
import re,sys
src=Path(sys.argv[1] if len(sys.argv)>1 else 'src/cl386_nt1991_code.asm')
out=Path(sys.argv[2] if len(sys.argv)>2 else 'build/text_segment.bin')
b=bytearray()
for line in src.read_text().splitlines():
    m=re.match(r'\s*db\s+([^;]+)',line,re.I)
    if not m: continue
    for x in m.group(1).split(','): b.append(int(x.strip(),0))
out.parent.mkdir(parents=True,exist_ok=True);out.write_bytes(b);print(out,len(b))
