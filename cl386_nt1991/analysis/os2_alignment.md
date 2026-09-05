# Alignment with the earlier OS/2 CL386

The OS/2 CodeView reverse recovered 155 named procedures. This NT executable's retained COFF symbols match **154/155** by procedure name.

The only unmatched OS/2 procedure name is: `InitLeadByte`.

This is unusually strong evidence that the compiler-driver sources are essentially the same lineage, with target/platform and CRT changes around them. It is why the prior reverse is useful as a semantic cross-check rather than merely as a conceptual comparison. See `function_crosswalk_os2_to_nt.tsv` for every address pair.
