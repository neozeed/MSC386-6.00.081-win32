#!/usr/bin/env python3
from pathlib import Path
import hashlib,sys
root=Path(__file__).resolve().parents[1]
def h(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
a=root/'reference'/'CL386-1991.EXE'; r=root/'build'/'CL386-original-rebuilt.EXE'
print('reference',h(a)); print('rebuilt  ',h(r)); print('BYTE-EXACT MATCH' if a.read_bytes()==r.read_bytes() else 'MISMATCH')
