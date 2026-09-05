#!/usr/bin/env python3
from pathlib import Path
import re, hashlib, argparse
ROOT=Path(__file__).resolve().parents[1]
def main(out):
    asm=(ROOT/'src/c1_386_nt1991_annotated.asm').read_text('utf-8')
    data=bytearray()
    for line in asm.splitlines():
        m=re.match(r'\s*db\s+([^;]+)',line)
        if not m: continue
        for x in m.group(1).split(','):
            x=x.strip()
            if x:data.append(int(x,0))
    orig=(ROOT/'parts/text_segment.bin').read_bytes()
    if bytes(data)!=orig: raise SystemExit(f'text mismatch: emitted {len(data)} expected {len(orig)}')
    t=bytearray((ROOT/'parts/original_image_template_text_zeroed.bin').read_bytes())
    raw=0x400
    t[raw:raw+len(data)]=data
    Path(out).write_bytes(t)
    print(hashlib.sha256(t).hexdigest(),out)
if __name__=='__main__':
    ap=argparse.ArgumentParser();ap.add_argument('output',nargs='?',default=str(ROOT/'build/C1_386_rebuilt.EXE'));a=ap.parse_args();main(a.output)
