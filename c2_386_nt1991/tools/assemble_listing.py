#!/usr/bin/env python3
from pathlib import Path
import re,sys
src=Path(sys.argv[1]); out=Path(sys.argv[2]); data=bytearray()
for line in src.read_text(encoding='utf-8').splitlines():
    code=line.split(';',1)[0].strip()
    if not code.lower().startswith('db '): continue
    for tok in code[3:].split(','):
        tok=tok.strip(); data.append(int(tok,0)&0xff)
out.write_bytes(data)
print(f'{out}: {len(data)} bytes')
