# C1_386.EXE — Dec-1991 Windows NT reverse/rebuild + modern Win32 conversion

This bundle analyses the uploaded 1991 NT `C1_386.EXE` and uses the previously reversed OS/2-hosted C1 as a semantic comparison.

## Headline findings

* Transitional **PE32/i386** dated 11 December 1991, not the final released-NT PE conventions.
* The file physically retains a **3,161-entry COFF symbol table**, despite the old characteristics claiming symbols are stripped.
* Recovered **795 public text symbols** and **28 static text symbols**, with **157 source contributions** and **2,095 `.text` line records**.
* Original compiler module names include `main.c`, `types.c`, `trees.c`, `grammar.c`, `p0scan.c`, `p0pragma.c`, `intrin.c`, `stmt.c`, `thunk.c`, `Common\error.c`, and early NT CRT paths.
* `Common\error.c` preserves original local names `get_err`, `get_msg`, `get_message`, `get_int`, `mark_pos`, `nearest`, plus public `_error`, `_fatal`, `_warning`, `_message`, `_format`, `_do_format`.
* **430** calls to `_error`/`_fatal`/`_warning` were found; **428** have an immediate low diagnostic number recovered, so the listing annotates the corresponding `C1_386.ERR` text.
* The NT error catalogue has **589** parsed messages versus **594** in the supplied OS/2 file. They are close but not byte-identical.

## Reversible reverse

`src/c1_386_nt1991_annotated.asm` is the authoritative listing. Every original `.text` byte is emitted as `db`; the x86 decode, source line, original symbol name, diagnostic, and target name are comments. `tools/rebuild_original.py` reinserts those bytes into a preserved image template.

Round trip is byte exact:

`9bfb785e5b08298be94f44256812378c094e0abd0a69e66f8d1ce2ba3745b933`

See `analysis/ROUNDTRIP_OK.txt`.

## Modern Win32 build

`build/C1_386-WIN32.EXE` + `build/C1_386COMPAT.DLL` are the conversion pair. The converter rewrites the old relocation format, rebases the image to `0x00400000`, normalises section metadata, and redirects the early BASE/NTDLL ABI through the compatibility DLL. See `analysis/win32_compatibility.md` for the ABI details and validation limits.

## Useful files

* `src/c1_386_nt1991_annotated.asm` — full reversible annotated `.text` listing
* `src/c1_386_nt1991_recovered_pseudocode.c` — conservative semantic pseudocode
* `analysis/functions.tsv` — 795 named public compiler/runtime routines with source attribution
* `analysis/module_function_index.md` — routines grouped by original source module
* `analysis/source_lines.tsv` — retained COFF line records
* `analysis/diagnostic_call_refs.tsv` — diagnostic call sites and decoded C1 error text
* `analysis/os2_to_nt_crosswalk.tsv` — high-confidence OS/2 ↔ NT semantic anchors
* `analysis/message_differences.md` — OS/2 vs NT `.ERR` differences
* `analysis/old_relocations.tsv` — all old relocation records and verification
* `analysis/win32_compatibility.md` — modernisation rationale
* `tools/modernize_c1_386.py` — reproducible PE converter
* `compat/c1_386_compat.c` / `.def` — compatibility DLL source
