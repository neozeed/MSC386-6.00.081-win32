# Functions grouped by COFF source contribution

## 000: main.c

RVA `0x00010000`–`0x00010ebc`.

- `_nextword`
- `_main`
- `_final`
- `_GetSourceLine`
- `_mingle`
- `_fin_mingle`
- `_recover`
- `_code_bias`
- `_get_node`
- `_heap_overflow`

## 003: memallo.c

RVA `0x00010ec0`–`0x00011154`.

- `_freemem`
- `_getmem`
- `_pcheck`
- `_adjust_code_pool`
- `_clear`
- `_freelst`
- `_pstrdup`
- `_cpybuf`
- `_CheckFarHeap`
- `_CheckNearHeap`

## 004: compiler_contribution_004 [_read_seginfo, _init_obj, _set_class...]

RVA `0x00011160`–`0x000124b8`.

- `_read_seginfo`
- `_init_obj`
- `_set_class`
- `_calc_fixes`
- `_fix_symbol`
- `_symbol_fixup`
- `_eGRPDEF`
- `_emit_comment`
- `_emit_huge_array`

## 005: omf.c

RVA `0x000124c0`–`0x00012ddc`.

- `_getnew`
- `_findseg`
- `_eFIXLIST`
- `_emitc`
- `_emitw`
- `_emitl`
- `_emitlp`
- `_emitn`
- `_StripDname`
- `_emitname`
- `_emitlongname`
- `_emitz`
- `_emitindex`
- `_emit_leafdescriptor`
- `_emit_comdeflength`
- `_init_rec`
- `_emit_init`
- `_uppercasify`
- `_put_data`
- `_makename`
- `_add_segment`
- `_init_seg`

## 006: omf_ms.c

RVA `0x00012de0`–`0x0001453c`.

- `_beginrec`
- `_flushn`
- `_newrec`
- `_endrec`
- `_eTHEADR`
- `_eCOMENT`
- `_eLLNAME`
- `_eLNAME`
- `_eSEGDEF`
- `_eCOMDEF`
- `_eEXTDEF`
- `_eLEXTDEF`
- `_eEDEF`
- `_eCEXTDEF`
- `_emit_comdat_sym`
- `_ePUBDEF`
- `_eLPUBDEF`
- `_ePDEF`
- `_emit_line_number`
- `_eLINNUM`
- `_eLIDATA`
- `_eCOMDAT`
- `_eLINSYM`
- `_emitnum`
- `_eFIXUPP`
- `_emit_thread`
- `_eMODEND`
- `_emit_syms`
- `_emit_pubs`
- `_common_name`
- `_symbols`
- `_fin_obj`
- `_put_object`
- `_put_val`
- `_fix_ms`
- `_fix_pointer`
- `_fix_32_pointer`
- `_fix_base`
- `_fix_offset`
- `_fix_relative`
- `_EmitRegVar`
- `_new_data_rec`
- `_find_comdat_index`
- `_create_comdat_index_list`

## 007: pgo.c

RVA `0x00014540`–`0x0001607c`.

- `_set_offset`
- `_calc_offsets`
- `_extract_node`
- `_ins_node`
- `_next_node`
- `_next_instr`
- `_prev_instr`
- `_prev_node`
- `_new_instr`
- `_label_check`
- `_new_label`
- `_clear_regtab_struct`
- `_add_label`
- `_del_ref`
- `_attach_refs`
- `_lremove`
- `_del_group`
- `_change_target`
- `_post_opt`
- `_move_code`
- `_sp_indep_opts`
- `_sp_dep_opts`
- `_br_size`
- `_isa_loop`
- `_dead_code`
- `_br_sequence`
- `_cross_jumps`
- `_br_self`
- `_jmp_next`
- `_jmp_jmp`
- `_branch_chain`
- `_loop_inversion`
- `_code_motion`
- `_new_ref`
- `_new_link_node`
- `_unlink_node`
- `_remove_labsym`
- `_same_instr`

## 008: MD.c

RVA `0x00016080`–`0x00016110`.

- `_preg`

## 009: typemit.c

RVA `0x00016110`–`0x000164b0`.

- `_EmitTypes`
- `_EnterBase`
- `FindBaseOffset`

## 010: compiler_contribution_010 [_ref_types, _post_init, _spdep_init...]

RVA `0x000164b0`–`0x00018de4`.

- `_ref_types`
- `_post_init`
- `_spdep_init`
- `_sift_data_nodes`
- `_cond_code_not_used`
- `_absval`
- `_br_span`
- `_make_ubranch`
- `_same_location`
- `_loop_once`
- `_loop_type`
- `_dis_opls`
- `_clear_all`
- `_clear_regtab`
- `_clear_part_oprs`
- `_rm_dep_oprs`
- `_ref_class`
- `_clear_reg`
- `_find_xreg`
- `_find_reg`
- `_redundancies`
- `_rloads`
- `_reg_neq_index`
- `_removeopl`
- `_remove_nonopl`
- `_add_zero`
- `_remove_indirect_opnd`
- `_add_opl`
- `_Add_to_clear_list`
- `_in_reg`
- `_copy_oplist`
- `_UpdateLabTab`
- `_UpdateLab`
- `_RedundantJCC`
- `_ExpandJMP`
- `_rm_empty_routine`
- `_even_align`
- `_align`
- `_add_nop`
- `_clear_mem`
- `_check_scheduling`

## 011: compiler_contribution_011 [_set_W_bit, _calc_addr, _outb...]

RVA `0x00018df0`–`0x0001b5a4`.

- `_set_W_bit`
- `_calc_addr`
- `_outb`
- `_immed`
- `_symimmed`
- `_logicals`
- `_sreg`
- `_seg_reg`
- `_mov_mem_to_ax`
- `_mov_ax_to_mem`
- `_addtype`
- `_obj_ea`
- `_binop`
- `_br_disp`
- `_decode`
- `_mfbits`

## 012: compiler_contribution_012 [_emit_dbgsyms, _emit_stack_sym, _emit_var_dbgrecord...]

RVA `0x0001b5b0`–`0x0001be2c`.

- `_emit_dbgsyms`
- `_emit_stack_sym`
- `_emit_var_dbgrecord`
- `_emit_dbconst`
- `_wr_block_length`
- `_patch_block_length`
- `_save_entry_info`
- `_emit_dbgseginfo`
- `_emit_proc_start`
- `_emit_block`
- `_emit_end`
- `_emit_label`
- `_emit_stack_locals`
- `_emit_reg_vars`
- `_emit_parameters`
- `_emit_local_autos`
- `_emit_local_statics`
- `_emit_dbg_register`
- `_StartSymRec`
- `_EndSymRec`

## 013: csize.c

RVA `0x0001be30`–`0x0001ca38`.

- `_code_size`
- `_c_size`
- `_ea_size`
- `_imm_size`
- `_sign_extend`

## 014: p3symtab.c

RVA `0x0001ca40`–`0x0001ce34`.

- `_init_locsymtab`
- `_init_globsymtab`
- `_find_sym`
- `_find_key`
- `_add_sym`
- `_statsym_add`
- `_ls_find`

## 015: compiler_contribution_015 [_set_loop_flag, _check_loop, _ubranch_check...]

RVA `0x0001ce40`–`0x0001d1a0`.

- `_set_loop_flag`
- `_check_loop`
- `_ubranch_check`
- `_insert_in_flow_graph`
- `_new_transfer_node`
- `_unlink_transfer_node`
- `_find_insert_point`
- `_update_flow_group`

## 016: pgo2.c

RVA `0x0001d1a0`–`0x0001d9d4`.

- `_rec_pcheck`
- `_readproc`
- `_skip_asm`
- `_do_backward_check`
- `_check_who_first`

## 017: p3io.c

RVA `0x0001d9e0`–`0x0001f3d4`.

- `_read_operand`
- `_get_operands`
- `_read_ail`
- `_GetMultiByteBuff`
- `_read_value`
- `_read_init`
- `_read_sil`
- `_read_locsil`
- `_read_globsil`
- `_walk_syms`

## 018: compiler_contribution_018 [_check_mode, _chg_mode, _set_val...]

RVA `0x0001f3e0`–`0x0001f764`.

- `_check_mode`
- `_chg_mode`
- `_set_val`
- `_check_opcode`

## 019: srclist.c

RVA `0x0001f770`–`0x00020c60`.

- `_init_list`
- `_fin_list`
- `_list_to_here`
- `_digits`
- `_print_line`
- `_whitespace`
- `_include_line`
- `_print_errs`
- `_find_errs`
- `_del_err`
- `_match`
- `_new_page`
- `_truncate`
- `_to_string`
- `_get_date`
- `_get_time`
- `_read_errors`
- `_add_err`
- `_list_locals`
- `_lst_dynamic`
- `_lst_static`
- `_sprint`
- `_pr_pr_header`
- `_pr_gl_header`
- `_pr_lc_header`
- `_pr_globsym`
- `_pr_sym`
- `_gettype`
- `_sort_sym`
- `_newline`
- `_list_name`
- `_pr_globals`
- `_get_list_pragma`
- `_exec_list_pragma`
- `_Save_List_Vars`
- `_Restore_List_Vars`

## 021: compiler_contribution_021 [_segheader, _new_seg, _asm_init...]

RVA `0x00020c60`–`0x00022a58`.

- `_segheader`
- `_new_seg`
- `_asm_init`
- `_name_dict`
- `_fin_asm`
- `_disasm`
- `_disinstr`
- `_masm_size`
- `_disea`
- `_ea_ns`
- `_not_sized`
- `_display_regs`
- `_pdisp`
- `_begin_line`
- `_end_line`
- `_storage`
- `_wr_uninit`
- `_cm_gcvt`
- `_printsingle`
- `_print_double`
- `_print_treal`
- `_pretty_print`
- `_wr_val`
- `_wr_init`
- `_do_init`
- `_asm_data`
- `_pub_syms`
- `_ext_procs`
- `_ext_syms`
- `_dis_EXTDEF`

## 022: operand.c

RVA `0x00022a60`–`0x00023184`.

- `_init_operand`
- `_clear_reg_flag`
- `_rewrite`
- `_free_opndlist`
- `_find_operand`
- `_create_operand`
- `_remove_operand`
- `_copy_operands`
- `_compare_operand`
- `_indirectly_used`

## 023: compiler_contribution_023 [_set_instr_vars, _rm_deadload, _rm_deadinstr...]

RVA `0x00023190`–`0x00026888`.

- `_set_instr_vars`
- `_rm_deadload`
- `_rm_deadinstr`
- `_Update_offset`
- `_remove_entry_exit_sequence`
- `_keep_carry_instr`
- `_regtopref`
- `_mark_ref`
- `_mark_changed`
- `_set_refmode`
- `_same_reg`
- `_clear_reference`
- `_remove_node`
- `_mark_changed_locsym`
- `_no_lab_in_between`
- `_mark_ref_locsym`
- `_clear_locsym_space`
- `_rm_dead_store`
- `_peephole`
- `_carry_not_used`
- `_change_to_inc_dec`
- `_rem_inv_inst`
- `_mov_to_cwd`
- `_extra_compare`
- `_check_for_byteop`
- `_fdload`
- `_compress_JCC_seq`
- `_compress_TEST_seq`
- `_shorten_instr`
- `_check_reg_chain`
- `_clear_reg_chain`
- `_rm_reg_chain`
- `_do_forward_check`

## 026: ioin.c

RVA `0x00026890`–`0x00026d4c`.

- `_chread`
- `_keyread`
- `_shread`
- `_loread`
- `_flread`
- `_doread`
- `_rtread`
- `_zsread`
- `_lsread`
- `_lsignore`
- `_buff_check`
- `_il_file`
- `_werr`

## 028: error.c

RVA `0x00026d50`–`0x00027110`.

- `_error`
- `_fatal`
- `_warning`
- `_message`
- `format`
- `_do_format`
- `_close_all`

## 029: D:\nt\private\crt32st\lowio\close.c

RVA `0x00027110`–`0x0002718c`.

- `__close`

## 030: i386\chkstk.asm

RVA `0x0002719c`–`0x000271c9`.

- `__chkstk`

## 032: D:\nt\private\crt32st\startup\crt0dat.c

RVA `0x000271cc`–`0x00027380`.

- `__cinit`
- `_exit`
- `__exit`
- `__cexit`
- `__c_exit`
- `doexit`
- `_doinitterm`

## 033: D:\nt\private\crt32st\dos\dosmap.c

RVA `0x0002739e`–`0x0002741e`.

- `__dosmaperr`

## 034: D:\nt\private\crt32st\convert\fcvt.c

RVA `0x0002741e`–`0x000274ba`.

- `__fcvt`
- `__ecvt`
- `_fpcvt`

## 035: D:\nt\private\crt32st\stdio\_filbuf.c

RVA `0x000274be`–`0x0002756e`.

- `__filbuf`

## 036: D:\nt\private\crt32st\stdio\_flsbuf.c

RVA `0x0002756e`–`0x00027692`.

- `__flsbuf`

## 037: D:\nt\private\fp32st\conv\cfout.c

RVA `0x0002769e`–`0x0002770e`.

- `__fltout`

## 038: D:\nt\private\fp32st\conv\x10fout.c

RVA `0x0002770e`–`0x00027ab6`.

- `_$I10_OUTPUT`

## 039: D:\nt\private\fp32st\conv\mantold.c

RVA `0x00027abe`–`0x00027d32`.

- `___addl`
- `___add_12`
- `___shl_12`
- `___shr_12`
- `___mtold12`

## 040: D:\nt\private\fp32st\conv\ldtod.c

RVA `0x00027d3e`–`0x00027faa`.

- `___dtold`
- `___ldtod`

## 041: D:\nt\private\fp32st\conv\tenpow.c

RVA `0x00027fae`–`0x0002829e`.

- `___ld12mul`
- `___multtenpow12`

## 042: D:\nt\private\fp32st\conv\fpinit.c

RVA `0x0002829e`–`0x000282de`.

- `__fpmath`
- `__fpclear`
- `__cfltcvt_init`

## 043: D:\nt\private\fp32st\conv\cvt.c

RVA `0x000282de`–`0x00028832`.

- `__forcdecpt`
- `__cropzeros`
- `__positive`
- `__fassign`
- `__cftoe`
- `_cftoe_g`
- `__cftof`
- `_cftof_g`
- `__cftog`
- `__cfltcvt`
- `_shift`

## 044: D:\nt\private\fp32st\conv\i386\atold.c

RVA `0x0002883e`–`0x00028862`.

- `__atold`

## 045: D:\nt\private\fp32st\conv\strgtold.c

RVA `0x0002886e`–`0x00028e2a`.

- `___STRINGTOLD`

## 047: D:\nt\private\crt32st\convert\_fptostr.c

RVA `0x00028e2e`–`0x00028ebe`.

- `__fptostr`

## 048: D:\nt\private\crt32st\startup\crt0fp.c

RVA `0x00028ebe`–`0x00028eca`.

- `__fptrap`

## 049: D:\nt\private\crt32st\startup\crt0.c

RVA `0x00028ece`–`0x0002907a`.

- `_mainCRTStartup`
- `inherit`
- `__amsg_exit`

## 050: D:\nt\private\crt32st\startup\crt0msg.c

RVA `0x0002909c`–`0x00029130`.

- `__FF_MSGBANNER`
- `__NMSG_WRITE`

## 051: i386\crtexcpt.asm

RVA `0x00029142`–`0x000291b7`.

- `__except_handler`
- `__global_unwind`
- `__local_unwind`

## 052: D:\nt\private\crt32st\lowio\osfinfo.c

RVA `0x000291ce`–`0x000293ea`.

- `__alloc_osfhnd`
- `__set_osfhnd`
- `__free_osfhnd`
- `__get_osfhandle`
- `__open_osfhandle`

## 053: D:\nt\private\crt32st\stdio\_getbuf.c

RVA `0x000293f4`–`0x00029444`.

- `__getbuf`

## 054: D:\nt\private\crt32st\stdio\fflush.c

RVA `0x00029444`–`0x000295a0`.

- `_fflush`
- `__flush`
- `__flushall`
- `flsall`
- `__endstdio`

## 055: D:\nt\private\crt32st\lowio\commit.c

RVA `0x000295a4`–`0x00029614`.

- `__commit`

## 056: D:\nt\private\crt32st\stdio\closeall.c

RVA `0x0002961a`–`0x0002964a`.

- `__fcloseall`

## 057: D:\nt\private\crt32st\heap\heapinit.c

RVA `0x0002964a`–`0x000296aa`.

- `__heap_init`
- `__heap_grow_emptylist`

## 058: D:\nt\private\crt32st\heap\hpabort.c

RVA `0x000296b0`–`0x000296bc`.

- `__heap_abort`

## 060: D:\nt\private\crt32st\lowio\isatty.c

RVA `0x000296c0`–`0x000296e4`.

- `__isatty`

## 061: D:\nt\private\crt32st\lowio\lseek.c

RVA `0x000296f0`–`0x0002976c`.

- `__lseek`

## 063: D:\nt\private\crt32st\lowio\read.c

RVA `0x00029776`–`0x000299ae`.

- `__read`

## 064: D:\nt\private\crt32st\startup\stdargv.c

RVA `0x000299bc`–`0x00029bd4`.

- `__setargv`
- `parse_cmdline`

## 065: D:\nt\private\crt32st\startup\stdenvp.c

RVA `0x00029be2`–`0x00029ce6`.

- `__setenvp`

## 066: D:\nt\private\crt32st\string\stricmp.c

RVA `0x00029cf2`–`0x00029d5e`.

- `__stricmp`
- `__strcmpi`

## 067: D:\nt\private\crt32st\string\strupr.c

RVA `0x00029d62`–`0x00029d86`.

- `__strupr`

## 068: D:\nt\private\crt32st\lowio\write.c

RVA `0x00029d92`–`0x00029f8e`.

- `__write`

## 069: debug.c

RVA `0x00029f92`–`0x00029fb2`.

- `_assert`
- `_prof_start`
- `_prof_end`

## 070: D:\nt\private\crt32st\convert\atof.c

RVA `0x00029fb2`–`0x00029ff6`.

- `_atof`

## 071: D:\nt\private\fp32st\conv\cfin.c

RVA `0x0002a002`–`0x0002a0d2`.

- `__fltin`

## 072: D:\nt\private\crt32st\convert\atox.c

RVA `0x0002a0d2`–`0x0002a15a`.

- `_atol`
- `_atoi`

## 073: getflags.c

RVA `0x0002a162`–`0x0002a5e2`.

- `_crack_cmd`
- `_substr`
- `getnumber`
- `isita`
- `tailmatch`
- `copyover`
- `_unconcat`

## 074: D:\nt\private\crt32st\string\strdup.c

RVA `0x0002a5e2`–`0x0002a63e`.

- `__strdup`

## 075: labels.c

RVA `0x0002a642`–`0x0002a6ae`.

- `_createlabel`

## 076: D:\nt\private\crt32st\stdio\fclose.c

RVA `0x0002a6b2`–`0x0002a78e`.

- `_fclose`

## 077: D:\nt\private\crt32st\stdio\_freebuf.c

RVA `0x0002a792`–`0x0002a7c2`.

- `__freebuf`

## 078: D:\nt\private\crt32st\convert\xtoa.c

RVA `0x0002a7c2`–`0x0002a8a2`.

- `xtoa`
- `__itoa`
- `__ltoa`
- `__ultoa`

## 079: D:\nt\private\crt32st\dos\unlink.c

RVA `0x0002a8a2`–`0x0002a8ee`.

- `_remove`
- `__unlink`

## 080: D:\nt\private\crt32st\stdio\fgets.c

RVA `0x0002a8f8`–`0x0002a97c`.

- `_fgets`

## 081: D:\nt\private\crt32st\stdio\fopen.c

RVA `0x0002a988`–`0x0002a9bc`.

- `__fsopen`
- `_fopen`

## 082: D:\nt\private\crt32st\stdio\stream.c

RVA `0x0002a9c8`–`0x0002aa08`.

- `__getstream`

## 083: D:\nt\private\crt32st\stdio\_open.c

RVA `0x0002aa08`–`0x0002ab34`.

- `__openfile`

## 085: D:\nt\private\crt32st\lowio\open.c

RVA `0x0002ab38`–`0x0002ae40`.

- `__open`
- `__sopen`

## 086: D:\nt\private\crt32st\dos\access.c

RVA `0x0002ae5a`–`0x0002aeb2`.

- `__access`

## 087: D:\nt\private\crt32st\lowio\chsize.c

RVA `0x0002aeba`–`0x0002b006`.

- `__chsize`

## 088: D:\nt\private\crt32st\lowio\setmode.c

RVA `0x0002b00a`–`0x0002b08e`.

- `__setmode`

## 089: D:\nt\private\crt32st\stdio\fprintf.c

RVA `0x0002b09a`–`0x0002b0d6`.

- `_fprintf`

## 090: D:\nt\private\crt32st\stdio\_sftbuf.c

RVA `0x0002b0da`–`0x0002b1c2`.

- `__stbuf`
- `__ftbuf`

## 091: D:\nt\private\crt32st\stdio\output.c

RVA `0x0002b1ca`–`0x0002ba06`.

- `__output`
- `write_char`
- `write_multi_char`
- `write_string`
- `write_wstring`
- `get_int_arg`
- `get_long_arg`

## 092: D:\nt\private\crt32st\stdio\fputc.c

RVA `0x0002ba0a`–`0x0002ba5e`.

- `_fputc`
- `_putc`

## 093: D:\nt\private\crt32st\stdio\fread.c

RVA `0x0002ba6a`–`0x0002bb86`.

- `_fread`

## 094: D:\nt\private\crt32st\heap\free.c

RVA `0x0002bb8a`–`0x0002bbee`.

- `_free`

## 095: D:\nt\private\crt32st\stdio\freopen.c

RVA `0x0002bbfa`–`0x0002bc4e`.

- `_freopen`

## 096: D:\nt\private\crt32st\stdio\fseek.c

RVA `0x0002bc5a`–`0x0002bcde`.

- `_fseek`

## 097: D:\nt\private\crt32st\stdio\ftell.c

RVA `0x0002bcea`–`0x0002be46`.

- `_ftell`

## 098: D:\nt\private\crt32st\stdio\fwrite.c

RVA `0x0002be4a`–`0x0002bf8e`.

- `_fwrite`

## 099: get_err.c

RVA `0x0002bf9a`–`0x0002c1e2`.

- `_get_err`
- `get_msg`
- `get_message`
- `get_int`
- `mark_pos`
- `nearest`

## 100: D:\nt\private\crt32st\misc\getenv.c

RVA `0x0002c1ea`–`0x0002c262`.

- `_getenv`

## 101: srclist2.c

RVA `0x0002c26a`–`0x0002c2e6`.

- `_build_symtab`
- `_list_globals`

## 102: D:\nt\private\crt32st\time\localtim.c

RVA `0x0002c2ea`–`0x0002c356`.

- `_localtime`

## 103: D:\nt\private\crt32st\time\tzset.c

RVA `0x0002c35a`–`0x0002c4e2`.

- `___tzset`
- `__tzset`
- `__isindst`

## 106: D:\nt\private\crt32st\time\gmtime.c

RVA `0x0002c4ea`–`0x0002c68e`.

- `_gmtime`

## 107: D:\nt\private\crt32st\heap\malloc.c

RVA `0x0002c69a`–`0x0002c78e`.

- `_malloc`
- `__heap_split_block`

## 108: D:\nt\private\crt32st\heap\heapgrow.c

RVA `0x0002c79a`–`0x0002c9c2`.

- `__heap_grow`
- `_heap_new_region`
- `__heap_grow_region`
- `__heap_free_region`

## 109: D:\nt\private\crt32st\heap\heapadd.c

RVA `0x0002c9d0`–`0x0002cc64`.

- `__heapadd`
- `__heap_addblock`
- `_before`

## 110: D:\nt\private\crt32st\heap\findaddr.c

RVA `0x0002cc70`–`0x0002cce4`.

- `__heap_findaddr`

## 111: D:\nt\private\crt32st\heap\heapsrch.c

RVA `0x0002ccf0`–`0x0002ce08`.

- `__heap_search`

## 112: D:\nt\private\crt32st\string\memchr.c

RVA `0x0002ce10`–`0x0002ce48`.

- `_memchr`

## 113: D:\nt\private\crt32st\string\memmove.c

RVA `0x0002ce50`–`0x0002cea8`.

- `_memmove`

## 114: D:\nt\private\crt32st\string\memset.c

RVA `0x0002ceb0`–`0x0002cedc`.

- `_memset`

## 115: ltoa.c

RVA `0x0002cee0`–`0x0002cf60`.

- `_our_ltoa`

## 116: D:\nt\private\crt32st\misc\perror.c

RVA `0x0002cf60`–`0x0002d000`.

- `_perror`

## 118: D:\nt\private\crt32st\stdio\printf.c

RVA `0x0002d000`–`0x0002d040`.

- `_printf`

## 119: D:\nt\private\crt32st\stdio\rewind.c

RVA `0x0002d040`–`0x0002d088`.

- `_rewind`

## 120: D:\nt\private\crt32st\stdio\setvbuf.c

RVA `0x0002d090`–`0x0002d154`.

- `_setvbuf`

## 121: D:\nt\private\crt32st\stdio\sprintf.c

RVA `0x0002d160`–`0x0002d1cc`.

- `_sprintf`

## 122: D:\nt\private\crt32st\string\strchr.c

RVA `0x0002d1d0`–`0x0002d1fc`.

- `_strchr`

## 123: D:\nt\private\crt32st\string\strcat.c

RVA `0x0002d200`–`0x0002d244`.

- `_strcat`
- `_strcpy`

## 124: D:\nt\private\crt32st\string\strlen.c

RVA `0x0002d250`–`0x0002d268`.

- `_strlen`

## 125: D:\nt\private\crt32st\string\strncmp.c

RVA `0x0002d270`–`0x0002d2a4`.

- `_strncmp`

## 126: D:\nt\private\crt32st\string\strncpy.c

RVA `0x0002d2b0`–`0x0002d2e8`.

- `_strncpy`

## 127: D:\nt\private\crt32st\time\time.c

RVA `0x0002d2f0`–`0x0002d340`.

- `_time`

## 128: D:\nt\private\crt32st\time\dtoxtime.c

RVA `0x0002d346`–`0x0002d40a`.

- `__dtoxtime`

