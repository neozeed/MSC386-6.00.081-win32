# Functions grouped by COFF source contribution

## 000: compiler_contribution_000 [_nextword, _out_of_mem, _startp2...]

RVA `0x00010000`–`0x00010d98`.

- `_nextword`
- `_out_of_mem`
- `_startp2`
- `_settle_Oswitches`
- `_dop2`
- `_main`
- `_real_main`
- `_put_block`
- `_freeblock`

## 002: compiler_contribution_002 [_bitv_init, _bvalloc, _freebv...]

RVA `0x00010da0`–`0x00011708`.

- `_bitv_init`
- `_bvalloc`
- `_freebv`
- `_bvnodecount`
- `_bvextend`
- `_bvcpy`
- `_bvclr`
- `_bvset`
- `_bvany`
- `_bvcount`
- `_bvnext`
- `_bvnnext`
- `_bvcmp`
- `_bvor`
- `_bvand`
- `_bvandnot`
- `_bvnotand`
- `_bvunion`
- `_bvintersect`
- `_bvunionminus`
- `_bvunion_am`
- `_bitscom`
- `_bitset`
- `_bitclr`
- `_bittst`
- `_prbv`
- `_print_bitv`
- `_prbbva`

## 003: compiler_contribution_003 [_globalregs, _gather_gramregs_requirements, _build_allocation_ranges...]

RVA `0x00011710`–`0x0001a5f4`.

- `_globalregs`
- `_gather_gramregs_requirements`
- `_build_allocation_ranges`
- `_build_ars_recursive`
- `_build_ar`
- `_que_build_ar`
- `_deque_build_ar`
- `_do_ar_annexation`
- `_new_arnode`
- `_free_arnode`
- `_foreach_bl`
- `_gather_ar_gramregs`
- `_proc_interferes`
- `_proc_i_internal`
- `_color_regs`
- `_calc_savings`
- `_chuck_invalid`
- `_calculate_interf_graph`
- `_calculate_adjacency_life`
- `_check_lifes`
- `_allocate_trivially_colorable`
- `_sort_scaledsavings`
- `_sort_fp_regnums`
- `_allocate_tough_ones`
- `_adjacent_got_allocated`
- `_samelife_got_allocated`
- `_any_regs_avail_in_ar`
- `_allocate_ar`
- `_deallocate_ar`
- `_sort_life_thread`
- `_propagate_adr_attribute`
- `_propagate_def_attribute`
- `_assign_regs`
- `_dup_shrunk_ar`
- `_too_cheap_shrink`
- `_do_ar_conservative_annexation`
- `_post_assign_reassign`
- `_allocate_assign_segments`
- `_find_au_in_bl`
- `_is_exactly_loop`
- `_global_worthit`
- `_reg_rewrite`
- `_tree_reg_rewrite`
- `_rewrite_short_addr`
- `_tree_reg_rewrite_seg`
- `_tree_reg_rewrite_seg_recursive`
- `_regpragmas`
- `_in_life`
- `_find_ar`
- `_delete_regarg_intrinsics`
- `_enterloads_exitsaves`
- `_skip_airlocks`
- `_foreach_flow`
- `_update_fp_inregs`
- `_enterloads`
- `_insert_segload_maybe`
- `_exitsaves`
- `_exithack`
- `_exithack_internal`
- `_insert_load`
- `_fold_seg_load`
- `_ins_label`
- `_build_airlock`
- `_buildload`
- `_buildsave`
- `_dgroup_tree`
- `_save_dgroup_maybe`
- `_mark_blocks_gramregs`
- `_build_prreg`
- `_findtrees`
- `_findtrees_internal`
- `_handle_fp_stack_top`
- `_lock_and_dereg`
- `_build_fp_prreg`
- `_color_locals`
- `_loop_scale`
- `_loop_scale2`
- `_ghash_find`
- `_find_const_erseg`
- `_free_some_bits`
- `_build_const_bits`
- `_bcb_recursive_guy`
- `_seg_pseudo_extract_bit`
- `_add_arblset`
- `_checkfor_warnings`
- `_prars`
- `_prarss`
- `_prarsl`
- `_prardex`
- `_prarintrf`
- `_prar`

## 004: compiler_contribution_004 [_assign_regMD, _assign_segregMD, _wanto_reassignMD...]

RVA `0x0001a600`–`0x0001c720`.

- `_assign_regMD`
- `_assign_segregMD`
- `_wanto_reassignMD`
- `_reassign_regMD`
- `_reg_classMD`
- `_init_class_countsMD`
- `_Dgroup_for_sureMD`
- `_dont_loadMD`
- `_get_class_countMD`
- `_dec_class_countMD`
- `_mark_reg_statusMD`
- `_get_reg_statusMD`
- `_gramregs_reqMD`
- `_gramregs_reqMD_internal`
- `_seg_is_considered`
- `_reg_interferesMD`
- `_foreach_calleesaveMD`
- `_intrinsic_gramregs`
- `_init_grammarstyle_gramregsMD`
- `_mark_grammarstyle_regMD`
- `_lock_axdxMD`
- `_lock_returnFPregMD`
- `_twiddle_ax_opreturn_bitsMD`
- `_handle_ax_returnMD`
- `_handle_FP0_returnMD`
- `_fp_stack_levelMD`
- `_combine_regsMD`
- `_offsetpartMD`
- `_segpartMD`
- `_Dgroup_trashedMD`
- `_cmp_regvalsMD`
- `_is_seg_regMD`
- `_allocMD`
- `_aligned_okMD`
- `_wrapup_localsMD`
- `_init_localsMD`
- `_is_regargMD`
- `_isthere_proccallMD`
- `_is_ds_lockedMD`
- `_isthere_introrproccallMD`
- `_float_regs_required`
- `_float_expr`
- `_frval_notmp`
- `_frval_int`
- `_adr`
- `_clear_copyval`
- `_fld`
- `_fstp`
- `_prgramregs`

## 005: compiler_contribution_005 [_frame_addr, _segnumtoreg, _relseg_internal...]

RVA `0x0001c720`–`0x0001f7f0`.

- `_frame_addr`
- `_segnumtoreg`
- `_relseg_internal`
- `_relseg`
- `_csrel`
- `_framerel`
- `_mayberelseg`
- `_segpart`
- `_MDlongaddr`
- `_near_address`
- `_skipcv`
- `_md_complex`
- `_mdcanontree`
- `_mdcanonnode`
- `_mbretptr`
- `_farlocal`
- `_cheap_op`
- `_check_predef`
- `_adjust_frame`
- `_set_base`
- `_datalloc`
- `_allotemp`
- `_realign`
- `_redo_locals`
- `_cg_exit`
- `_segconst`
- `_isreallyfloatconst`
- `_findfloatconst`
- `_findfloatconstval`
- `_float_il`
- `_floatconst`
- `_findseg`
- `_sym_is_const`
- `_segment`
- `_create_seg`
- `_newseg`
- `_user_naminseg`
- `_segtable`
- `_segcheck`
- `_read_export`
- `_write_export`
- `_md_blk_asg`
- `_MDlo_part`
- `_MDhi_part`
- `_new_text_seg`
- `_find_seg`
- `_init_current_seg`
- `_write_seg_offs`
- `_all_segregs_lockedMD`
- `_data_in_code`
- `_emit_data_in_code`
- `_save_allocMD`
- `_reset_allocMD`
- `_get_default_blregs`
- `_howcheap`
- `_howcheap_services`
- `_howcheap_internal`
- `_find_foptype`
- `_fptoocheap`
- `_nofloat`

## 006: compiler_contribution_006 [_gettree, _gettree_internal, _tl_to_EBB...]

RVA `0x0001f7f0`–`0x0002148c`.

- `_gettree`
- `_gettree_internal`
- `_tl_to_EBB`
- `_characteristic`
- `_tree_init`
- `_newnode`
- `_newleaf`
- `_do_allotemp`
- `_clear_leaf_pool`
- `_free_leaf_pool`
- `_foreach_leaf`
- `_prleafpool`
- `_freenode`
- `_isfreenode`
- `_freetree`
- `_unlink_mark`
- `_freechildren`
- `_freehyb`
- `_countnode`
- `_lstcount`
- `_nodestats`
- `_pfreenodes`
- `_getnode`
- `_readc`
- `_new_tl`
- `_tl_count`
- `_addtree`
- `_free_tl`
- `_new_bl`
- `_add_tl`
- `_free_bl`
- `_treewalk`
- `_treewalkp`
- `_blockwalk`
- `_blockwalkp`
- `_tr_insert`
- `_ntr_insert`
- `_tl_insert`
- `_endproc`
- `_endblock`
- `_maketree`
- `_copynode`
- `_copytype`
- `_dupnode`

## 007: compiler_contribution_007 [_cg_canon, _imbed_walk, _linkmarks...]

RVA `0x00021490`–`0x00026a88`.

- `_cg_canon`
- `_imbed_walk`
- `_linkmarks`
- `_construct_clause`
- `_check_exprimbed`
- `_build_shtree`
- `_subexpr_imbed`
- `_ok_to_imbed_here`
- `_enter_assign`
- `_remove_conflicts`
- `_moveto_imlist`
- `_move_assign`
- `_move_imbedded_assign`
- `_deadnode`
- `_dead_store`
- `_count_marks`
- `_find_repl`
- `_calc_vused`
- `_post_imbed_walk`
- `_post_tree_walk`
- `_pushmark`
- `_dummy_mark`
- `_final_walk`
- `_final_walk_of_trees`
- `_final_walk_td`
- `_rewrite_regarg`
- `_flttostruct`
- `_final_walk_bu`
- `_small_mb`
- `_deep_search_opeq`
- `_typetree`
- `_check_opeq`
- `_skipmark`
- `_check_postfix`
- `_is_assigntemp`
- `_eq_xform`
- `_remove_used`
- `_samecvt`
- `_uses_reg`
- `_av_interf`
- `_mark_above_assign`
- `_clear_avlist`
- `_free_assign`
- `_free_interf`
- `_free_shtree`
- `_new_avnode`
- `_new_shnode`
- `_free_some_shnodes`
- `_free_avnode`
- `_free_shnode`
- `_new_il`
- `_free_il`
- `_append_list`
- `_copy_list`
- `_do_enreg`
- `_blenregt`
- `_handle_reg_args`
- `_globcse_stats`
- `_globcse_rewrite`
- `_prshtree`
- `_printerf`
- `_shnode_stats`

## 008: compiler_contribution_008 [_flow, _find_label, _add_caller...]

RVA `0x00026a90`–`0x00029c28`.

- `_flow`
- `_find_label`
- `_add_caller`
- `_break_synonyms`
- `_add_label`
- `_transitive_closure_alternates`
- `_transitive_closure_internal`
- `_print_labels`
- `_build_label_map`
- `_coalesce_labels`
- `_dont_coalesce_these`
- `_initialize_lexer`
- `_unget_treelist`
- `_next_treelist`
- `_build_flow_graph`
- `_add_fflow`
- `_add_bflow`
- `_add_flows`
- `_in_flow`
- `_remove_flow`
- `_remove_flow_if`
- `_fixup_labels`
- `_build_DFO`
- `_recursive_DFO`
- `_sort_flow`
- `_flow_count`
- `_break_fallthrough`
- `_transfer_dest`
- `_last_tl`
- `_filter_dead_code`
- `_recursive_all_paths`
- `_free_dead_code`
- `_pack_DFO`
- `_blockmerge_loopupdate`
- `_check_flow`
- `_calc_dom`
- `_find_loops`
- `_src_is_reachable`
- `_src_is_reachable_internal`
- `_collect_tails`
- `_mark_loop_body`
- `_mark_loop_body_internal`
- `_expand_tails`
- `_fixup_tails`
- `_update_tails`
- `_remove_break_blocks`
- `_remove_break_blocks_1loop`
- `_not_parent_loop`
- `_enumerate_DFO`
- `_canonicalize_loops1`
- `_canonicalize_loops2`
- `_is_in_loop`
- `_handle_blkstart_opexit`
- `_print_flow`
- `_print_loop`
- `_print_loop_internal`
- `_print_dom`
- `_init_heap`
- `_new_labelnode`
- `_new_flownode`
- `_free_flownode`
- `_free_bl_flow`
- `_new_loopnode`
- `_free_heap`

## 009: compiler_contribution_009 [_machine_type, _ReserveBxMask, _alloregparams...]

RVA `0x00029c30`–`0x0002a728`.

- `_machine_type`
- `_ReserveBxMask`
- `_alloregparams`
- `_is_huge`
- `_halloc`
- `_new_entry`
- `_far16_tree`
- `_emit_far16`

## 010: compiler_contribution_010 [_confold, _int_arith, _fix_laddr...]

RVA `0x0002a730`–`0x0002b7b4`.

- `_confold`
- `_int_arith`
- `_fix_laddr`
- `_float_arith`
- `_const_conv`
- `_fix_pt`
- `_fix_val`
- `_relconf`
- `_relfold`
- `_frelfold`
- `_fltinit`

## 011: compiler_contribution_011 [OVMCHK, OVACHK, OVSCHK]

RVA `0x0002b7c0`–`0x0002b884`.

- `OVMCHK`
- `OVACHK`
- `OVSCHK`

## 012: compiler_contribution_012 [_grammar, _clean_prewalk, _lonemark...]

RVA `0x0002b890`–`0x0002c704`.

- `_grammar`
- `_clean_prewalk`
- `_lonemark`
- `_del_OPregister_cse`
- `_find_leaf_cse`
- `_prinfo`
- `_grammar_prewalk`
- `_info_offset`
- `_do_grammar`
- `_clear_inreg`
- `_lexpush`
- `_xxerr`
- `_prreglist`
- `_do_pragma`
- `_addsp`

## 013: compiler_contribution_013 [_expand, _eval, _mcond...]

RVA `0x0002c710`–`0x00030284`.

- `_expand`
- `_eval`
- `_mcond`
- `_nox`
- `_alop`
- `_isrc`
- `_isr`
- `_xnew`
- `_xconstrain`
- `_xasg`
- `_xfree`
- `_reg_not_in`
- `_lodseg`
- `_append`
- `_cpylineno`
- `_extrlocal`
- `_regintree`
- `_profiler_code`

## 014: compiler_contribution_014 [_read_pragma_info, _reverse_Otab_sense, _read_comment...]

RVA `0x00030290`–`0x00030928`.

- `_read_pragma_info`
- `_reverse_Otab_sense`
- `_read_comment`
- `_write_comments`

## 015: compiler_contribution_015 [_canontree, _canonnode, _canons_td...]

RVA `0x00030930`–`0x000339d0`.

- `_canontree`
- `_canonnode`
- `_canons_td`
- `_canons_bu`
- `_hoisttree`
- `_hoistnode`
- `_hoist_td`
- `_hoist_lr`
- `_hoist_bu`
- `_temp_asgn`
- `_asgn_val`
- `_bit_const`
- `_make_maxmin`
- `_const_questop`
- `_trans_questop`
- `_trans_comma`
- `_make_arm`
- `_trans_logical`
- `_notrelop`
- `_relcheck`
- `_rel_to_q`
- `_logical_fold`
- `_do_transform`
- `_vmfunc_transform`
- `_rev_args`
- `_mbreturn`
- `_structparam`
- `_alloc_parms`
- `_hoist`
- `_calc_interfere`
- `_interference`
- `_pop_binaryL`
- `_pop_binaryR`

## 016: compiler_contribution_016 [_emit, _put_operand, _write_sil...]

RVA `0x000339d0`–`0x0003529c`.

- `_emit`
- `_put_operand`
- `_write_sil`
- `_namestring`
- `_sil_proc`
- `_opndattrsize`
- `_emit_line`

## 018: compiler_contribution_018 [_crack_cmd, _substr, _getnumber...]

RVA `0x000352a0`–`0x0003577c`.

- `_crack_cmd`
- `_substr`
- `_getnumber`
- `_isita`
- `_tailmatch`
- `_copyover`
- `_unconcat`

## 019: compiler_contribution_019 [_FCMADD, _FCMSUB, _FCMMUL...]

RVA `0x00035780`–`0x000359d6`.

- `_FCMADD`
- `_FCMSUB`
- `_FCMMUL`
- `_FCMDIV`
- `_FCMCOMPARE`

## 020: compiler_contribution_020 [_FMSIZE, _FMADD, _FMSUB...]

RVA `0x000359e0`–`0x00035f54`.

- `_FMSIZE`
- `_FMADD`
- `_FMSUB`
- `_FMMUL`
- `_FMDIV`
- `_FMRT_R4`
- `_FMRT_R8`
- `_FMRT_R10`
- `_FMR4_RT`
- `_FMR8_RT`
- `_FMR10_RT`
- `_FMI4_RT`
- `_FMU4_RT`
- `_FMRT_I4`
- `_FMRT_U4`
- `_FMRT_I4R`
- `_FMMIN`
- `_FMMAX`
- `_FMABS`
- `_FMCOMPARE`

## 021: compiler_contribution_021 [_rematch, _findhashnode, _inshashnode...]

RVA `0x00035f60`–`0x0003d0ec`.

- `_rematch`
- `_findhashnode`
- `_inshashnode`
- `_rmhashnode`
- `_newru`
- `_freeru`
- `_pushru`
- `_freeuselist`
- `_clearuses`
- `_finduse`
- `_findadruse`
- `_findreguse`
- `_rmuse`
- `_rmusei`
- `_rmbits`
- `_mvuse`
- `_clearbits`
- `_allsaved`
- `_regmap_init`
- `_initMD`
- `_resetMD`
- `_annexlist`
- `_doannex`
- `_reg_find`
- `_reg_pick`
- `_reg_alloc`
- `_reg_build`
- `_numtomap`
- `_rset`
- `_regset`
- `_ea_walk`
- `_ea_set`
- `_ustati`
- `_ustat`
- `_uustat`
- `_set_pref`
- `_reg_assign`
- `_grab_reg`
- `_chgreg`
- `_reg_construct`
- `_reg_this_size`
- `_dereg`
- `_set_rtab`
- `_add_rtab`
- `_lastreg`
- `_get_rtab`
- `_rtop`
- `_checkavail`
- `_lastref`
- `_reg_avail`
- `_reg_steal`
- `_reg_restore`
- `_is_stolen`
- `_reg_occupied`
- `_clearmap`
- `_reguse_refsleft`
- `_regrefsleft`
- `_move_reg`
- `_is_eaopnd`
- `_seg_pos`
- `_ea_free`
- `_freestandard`
- `_freespecial`
- `_freemarknode`
- `_dstrmarknode`
- `_clearcopies`
- `_dstrmark`
- `_freemark`
- `_clear_saved`
- `_ea_freea`
- `_live_inreg`
- `_live_efad`
- `_is_locked`
- `_is_segreg`
- `_constrain_addreg`
- `_constrain_inreg`
- `_rmuseintree`
- `_advancemark`
- `_advanceseq`
- `_dis_inreg`
- `_un_inreg`
- `_dec_refcnt`
- `_nodeintree`
- `_eqnode`
- `_eqreg`
- `_dontspill`
- `_alternative`
- `_checkrematch`
- `_chkupd`
- `_newlyinreg`
- `_upd_busy`
- `_regno`
- `_opndofs`
- `_rew_half`
- `_regstring`
- `_uses_segreg`
- `_spillee`
- `_spiller`
- `_abandon`
- `_spill`
- `_un_inreg_walk`
- `_rew_lmem`
- `_rew_mem`
- `_fix_pair`
- `_fix_halflong`
- `_rew_inreg`
- `_spill_look`
- `_spill_track`
- `_spill_untrack`
- `_clear_effaddr`
- `_spill_reg`
- `_do_spill`
- `_clr_except`
- `_regisin`
- `_spilllist`
- `_loadargs`
- `_InitGlobCSEReg`
- `_SetGlobCSEReg`
- `_IsGlobCSEReg`
- `_FinishGlobCSEInit`
- `_chkmap`
- `_mch`
- `_printreg`
- `_mypreg`
- `_pruse`
- `_dumpreg`
- `_prhashtab`
- `_prhist`
- `_propndi`
- `_propnd`

## 022: compiler_contribution_022 [_FltChr, _FltSize, _maclook...]

RVA `0x0003d0f0`–`0x0003d5dc`.

- `_FltChr`
- `_FltSize`
- `_maclook`
- `_condlook`
- `_mactext`
- `_libname`
- `_opcall`
- `_fop`

## 023: compiler_contribution_023 [_cseopt, _csecheck, _csech0...]

RVA `0x0003d5e0`–`0x0003f8cc`.

- `_cseopt`
- `_csecheck`
- `_csech0`
- `_csech1`
- `_csech2`
- `_loc_hash`
- `_put_mark`
- `_update_lastuses`
- `_rstores`
- `_extr_val`
- `_extr_gval`
- `_rst_find`
- `_csekill`
- `_cse_dkill`
- `_dag_mark`
- `_hash_find`
- `_hash_insert`
- `_syn_find`
- `_asyn_find`
- `_cse_interference`
- `_is_sym_global`
- `_is_global`
- `_safe_local`
- `_unsafe_var`
- `_makeextract`
- `_upd_mark`
- `_ins_mark`
- `_update_flow`
- `_find_par`
- `_csedump`
- `_valdump`
- `_csebvc`
- `_loc_attrib`
- `_glob_hash`
- `_smartdup`
- `_clear_glob_hash`
- `_build_ghash`
- `_build_ghash1`
- `_gkillmsk`
- `_killamask`
- `_extr_extr_mask`
- `_is_altered`
- `_hybvalmatch`
- `_nmduptree`
- `_mduptree`

## 024: compiler_contribution_024 [_dumpstr, _pr_cc, _pr_s...]

RVA `0x0003f8d0`–`0x000411b4`.

- `_dumpstr`
- `_pr_cc`
- `_pr_s`
- `_ov_check`
- `_ov_call`
- `_emit_ov_call`
- `_emit_check`
- `_opnd_check`
- `_reginopnd`
- `_cc_su`
- `_cc_tst`
- `_cc_unsign`
- `_addeq`
- `_noeq`
- `_is_branch`
- `_hi_low`
- `_hireg`
- `_bininst`
- `_genmov`
- `_si_di_setup`
- `_increg`
- `_strcopy`
- `_inc_and_mov`
- `_restore_ds`
- `_setcx`
- `_gen_movs`
- `_set_seg`
- `_put_lea`
- `_pupo`
- `_noexpand`
- `_getlr`
- `_patchname`

## 025: compiler_contribution_025 [_pril, _pri, _xpril...]

RVA `0x000411c0`–`0x00041e88`.

- `_pril`
- `_pri`
- `_xpril`
- `_printnode`
- `_prtl`
- `_prtls`
- `_prbl`
- `_prblinfo`
- `_prbl1s`
- `_prilblk`
- `_dbgprint`
- `_dbgprint_internal`
- `_scr`

## 027: compiler_contribution_027 [_is_predefined, _SetNearFarFrame, _getsym...]

RVA `0x00041e90`–`0x00043cb4`.

- `_is_predefined`
- `_SetNearFarFrame`
- `_getsym`
- `_initsym`
- `_init0sym`
- `_symadd`
- `_freesym`
- `_write_symtab`
- `_debugsyms`
- `_param_recurse`
- `_symlook`
- `_prssr`
- `_prsymtab`
- `_newlabel`
- `_newname`
- `_newdummy`
- `_getsmem`
- `_endp2`
- `_ProcessInitBlock`
- `_alloc_init_syms`
- `_getvalues`
- `_helpsym`
- `_chkplmnf`
- `_ail_locsym`

## 029: compiler_contribution_029 [_pool_init, _getmem, _sgetmem...]

RVA `0x00043cc0`–`0x00044230`.

- `_pool_init`
- `_getmem`
- `_sgetmem`
- `_pool_malloc`
- `_freemem`
- `_freelst`
- `_palloc`
- `_pstrdup`
- `_cpybuf`
- `_memstats`
- `_mem_print`
- `_poolcount`
- `_mem_check`

## 030: compiler_contribution_030 [_gencode, _genlink, _generate...]

RVA `0x00044230`–`0x000455f0`.

- `_gencode`
- `_genlink`
- `_generate`
- `_rereg`
- `_rerc`
- `_reext`
- `_findchild`
- `_findparent`
- `_child`
- `_parent`
- `_split_mark`
- `_numargs`
- `_refsleft`
- `_foldreg`
- `_indent`
- `_prpnode`
- `_genln`
- `_is_genln`

## 032: compiler_contribution_032 [_preg]

RVA `0x000455f0`–`0x000456c4`.

- `_preg`

## 033: compiler_contribution_033 [_dumpn, _setc, _perr...]

RVA `0x000456d0`–`0x000459a8`.

- `_dumpn`
- `_setc`
- `_perr`
- `_setflags`
- `_addflag`
- `_conexec`
- `_ifdb`
- `_PANIC`
- `_assertloop`
- `_assert`
- `_assertm`
- `_expect`
- `_prof_start`
- `_prof_end`

## 034: compiler_contribution_034 [_codegen, _tokpush, _tokinit...]

RVA `0x000459b0`–`0x00046160`.

- `_codegen`
- `_tokpush`
- `_tokinit`
- `_xxdump`
- `_get_index`
- `_ppop`

## 035: codegen.c

RVA `0x00046160`–`0x00049dd4`.

- `_constrmatch`
- `_addr_spill`
- `_which_reg`
- `_half_const`
- `_oktomultipush`
- `_regtocnstr`
- `_worth_tworeg`
- `_worthit`
- `_doescc`
- `_xxcondition`
- `_xxaction`

## 037: compiler_contribution_037 [_chread, _keyread, _shread...]

RVA `0x00049de0`–`0x0004a2b0`.

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

## 039: compiler_contribution_039 [_matchtree, _matchtreetypeless, _mtchtree...]

RVA `0x0004a2b0`–`0x0004b814`.

- `_matchtree`
- `_matchtreetypeless`
- `_mtchtree`
- `_findtree`
- `_findtree_internal`
- `_lmatchesr`
- `_eqmap`
- `_constant`
- `_datalength`
- `_duptree`
- `_init_tmphead`
- `_maketemp`
- `_treetemp`
- `_treesymtemp`
- `_get_temp`
- `_free_temps`
- `_reuse_temps`
- `_is_local`
- `_eatmark`
- `_ispure`
- `_ispure_nogsrc`
- `_purewart`
- `_makelabel`
- `_noeffect`
- `_noeffect_hoist`
- `_noeffect_tree`
- `_noeffect_optimize`
- `_fruitless`
- `_ovsum`
- `_typer`
- `_bitextract`
- `_bitassign`
- `_prtemps`
- `_makelist`
- `_findnode`
- `_skipcvtmark`

## 040: compiler_contribution_040 [_canon_except, _canon_except_bu, _resetsp...]

RVA `0x0004b820`–`0x0004c52c`.

- `_canon_except`
- `_canon_except_bu`
- `_resetsp`
- `_savesp`
- `_allocsavesp`
- `_unwindcall`

## 041: compiler_contribution_041 [_error, _fatal, _warning...]

RVA `0x0004c530`–`0x0004c94c`.

- `_error`
- `_fatal`
- `_warning`
- `_message`
- `_print`
- `_format`
- `_do_format`
- `_close_all`

## 042: compiler_contribution_042 [_chwrite, _shwrite, _keywrite...]

RVA `0x0004c950`–`0x0004ccc8`.

- `_chwrite`
- `_shwrite`
- `_keywrite`
- `_lowrite`
- `_flwrite`
- `_dowrite`
- `_rtwrite`
- `_zswrite`
- `_lswrite`

## 044: i386\chkstk.asm

RVA `0x0004ccd0`–`0x0004ccfd`.

- `__chkstk`

## 045: D:\nt\private\crt32st\lowio\close.c

RVA `0x0004cd00`–`0x0004cd7c`.

- `__close`

## 046: D:\nt\private\fp32st\tran\i386\ieee87.c

RVA `0x0004cd8c`–`0x0004cde0`.

- `__status87`
- `__clear87`
- `__control87`

## 048: D:\nt\private\crt32st\startup\crt0dat.c

RVA `0x0004cdec`–`0x0004cfa0`.

- `__cinit`
- `_exit`
- `__exit`
- `__cexit`
- `__c_exit`
- `doexit`
- `_doinitterm`

## 049: D:\nt\private\crt32st\dos\dosmap.c

RVA `0x0004cfbe`–`0x0004d03e`.

- `__dosmaperr`

## 050: i386\crtexcpt.asm

RVA `0x0004d03e`–`0x0004d0b3`.

- `__except_handler`
- `__global_unwind`
- `__local_unwind`

## 051: D:\nt\private\crt32st\stdio\_filbuf.c

RVA `0x0004d0ca`–`0x0004d17a`.

- `__filbuf`

## 052: D:\nt\private\crt32st\stdio\_flsbuf.c

RVA `0x0004d17a`–`0x0004d29e`.

- `__flsbuf`

## 053: D:\nt\private\fp32st\conv\fpinit.c

RVA `0x0004d2aa`–`0x0004d2ea`.

- `__fpmath`
- `__fpclear`
- `__cfltcvt_init`

## 054: D:\nt\private\fp32st\conv\cvt.c

RVA `0x0004d2ea`–`0x0004d83e`.

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

## 055: D:\nt\private\fp32st\conv\i386\atold.c

RVA `0x0004d84a`–`0x0004d86e`.

- `__atold`

## 056: D:\nt\private\fp32st\conv\strgtold.c

RVA `0x0004d87a`–`0x0004de36`.

- `___STRINGTOLD`

## 057: D:\nt\private\fp32st\conv\mantold.c

RVA `0x0004de3a`–`0x0004e0ae`.

- `___addl`
- `___add_12`
- `___shl_12`
- `___shr_12`
- `___mtold12`

## 058: D:\nt\private\fp32st\conv\tenpow.c

RVA `0x0004e0ba`–`0x0004e3aa`.

- `___ld12mul`
- `___multtenpow12`

## 060: D:\nt\private\fp32st\conv\cfout.c

RVA `0x0004e3aa`–`0x0004e41a`.

- `__fltout`

## 061: D:\nt\private\fp32st\conv\x10fout.c

RVA `0x0004e41a`–`0x0004e7c2`.

- `_$I10_OUTPUT`

## 062: D:\nt\private\fp32st\conv\ldtod.c

RVA `0x0004e7ca`–`0x0004ea36`.

- `___dtold`
- `___ldtod`

## 063: D:\nt\private\crt32st\convert\_fptostr.c

RVA `0x0004ea3a`–`0x0004eaca`.

- `__fptostr`

## 064: D:\nt\private\crt32st\startup\crt0fp.c

RVA `0x0004eaca`–`0x0004ead6`.

- `__fptrap`

## 065: D:\nt\private\crt32st\startup\crt0.c

RVA `0x0004eada`–`0x0004ec86`.

- `_mainCRTStartup`
- `inherit`
- `__amsg_exit`

## 066: D:\nt\private\crt32st\startup\crt0msg.c

RVA `0x0004eca8`–`0x0004ed3c`.

- `__FF_MSGBANNER`
- `__NMSG_WRITE`

## 067: D:\nt\private\crt32st\lowio\osfinfo.c

RVA `0x0004ed4e`–`0x0004ef6a`.

- `__alloc_osfhnd`
- `__set_osfhnd`
- `__free_osfhnd`
- `__get_osfhandle`
- `__open_osfhandle`

## 068: D:\nt\private\crt32st\stdio\_getbuf.c

RVA `0x0004ef74`–`0x0004efc4`.

- `__getbuf`

## 069: D:\nt\private\crt32st\stdio\fflush.c

RVA `0x0004efc4`–`0x0004f120`.

- `_fflush`
- `__flush`
- `__flushall`
- `flsall`
- `__endstdio`

## 070: D:\nt\private\crt32st\lowio\commit.c

RVA `0x0004f124`–`0x0004f194`.

- `__commit`

## 071: D:\nt\private\crt32st\stdio\closeall.c

RVA `0x0004f19a`–`0x0004f1ca`.

- `__fcloseall`

## 072: D:\nt\private\crt32st\heap\heapinit.c

RVA `0x0004f1ca`–`0x0004f22a`.

- `__heap_init`
- `__heap_grow_emptylist`

## 073: D:\nt\private\crt32st\heap\hpabort.c

RVA `0x0004f230`–`0x0004f23c`.

- `__heap_abort`

## 075: D:\nt\private\crt32st\lowio\isatty.c

RVA `0x0004f240`–`0x0004f264`.

- `__isatty`

## 076: D:\nt\private\crt32st\lowio\lseek.c

RVA `0x0004f270`–`0x0004f2ec`.

- `__lseek`

## 078: D:\nt\private\crt32st\lowio\read.c

RVA `0x0004f2f6`–`0x0004f52e`.

- `__read`

## 079: D:\nt\private\crt32st\startup\stdargv.c

RVA `0x0004f53c`–`0x0004f754`.

- `__setargv`
- `parse_cmdline`

## 080: D:\nt\private\crt32st\startup\stdenvp.c

RVA `0x0004f762`–`0x0004f866`.

- `__setenvp`

## 081: D:\nt\private\crt32st\string\strdup.c

RVA `0x0004f872`–`0x0004f8ce`.

- `__strdup`

## 082: D:\nt\private\crt32st\string\strupr.c

RVA `0x0004f8d2`–`0x0004f8f6`.

- `__strupr`

## 083: D:\nt\private\crt32st\lowio\write.c

RVA `0x0004f902`–`0x0004fafe`.

- `__write`

## 084: D:\nt\private\crt32st\convert\atof.c

RVA `0x0004fb02`–`0x0004fb46`.

- `_atof`

## 085: D:\nt\private\fp32st\conv\cfin.c

RVA `0x0004fb52`–`0x0004fc22`.

- `__fltin`

## 086: D:\nt\private\crt32st\convert\atox.c

RVA `0x0004fc22`–`0x0004fcaa`.

- `_atol`
- `_atoi`

## 087: compiler_contribution_087 [_tablook, _looktab]

RVA `0x0004fcb2`–`0x0004fd0a`.

- `_tablook`
- `_looktab`

## 088: compiler_contribution_088 [_loop_opt, _only_once, _dom...]

RVA `0x0004fd12`–`0x00055492`.

- `_loop_opt`
- `_only_once`
- `_dom`
- `_iter_dom`
- `_exit_dom`
- `_is_outer`
- `_tree_dom`
- `_jmp_dom`
- `_loop_type`
- `_long_lp_cnt`
- `_invar_chk`
- `_is_invar`
- `_invariants`
- `_inv_tree`
- `_lift_inv`
- `_find_op`
- `_cheap_invar`
- `_induc_chk`
- `_only_assign`
- `_addinduc`
- `_freeinduc`
- `_addreduc`
- `_is_induc`
- `_is_vinduc`
- `_strn_reduce`
- `_find_reduc`
- `_do_reduc`
- `_reduc_filter`
- `_namediff`
- `_make_addop`
- `_can_fold_induc`
- `_addinind`
- `_makeloopcnt`
- `_blkmove`
- `_bm_induc_expr`
- `_chk_depend`
- `_rminduc`
- `_dead_on_exit`
- `_incr_val`
- `_ind_remove`
- `_lftr`
- `_upper_bnd_ok`
- `_cvt_to_lcnt`
- `_dead_loop`
- `_loop_remove`
- `_remove_blk`
- `_remove_blk_flow`
- `_loop_cleanup`
- `_header_cse`
- `_undagify`
- `_undag1`
- `_head_cprop`
- `_tl_of`
- `_bl_of`
- `_ghashdump`
- `_prghbit`
- `_prbbv`
- `_prbdom`
- `_prfg`
- `_prflow`
- `_prinduc`
- `_inddump`
- `_prreduc`
- `_reddump`
- `_prloop`
- `_bvtally`
- `_global_opt`
- `_grstores`
- `_gcprop`
- `_gcse`
- `_gcprop_tr`
- `_gcse1`
- `_gcse2`
- `_find_cp_srcs`
- `_find_init`
- `_last_asg`
- `_addmark`
- `_no_mark`
- `_fixbits`
- `_fixbits1`
- `_clear_visited`
- `_fixbits2`
- `_unfixbits`
- `_gh_enter`
- `_hgh_enter`
- `_gh_fix`
- `_hoist_glob_marks`
- `_bits_of`
- `_nmoptimize`
- `_extend_bvs`
- `_calc_alt`
- `_calc_pant`
- `_p_uminus`
- `_calc_lpant`
- `_lp_uminus`
- `_calc_ss`
- `_ss_uminus`
- `_calc_pcomm`
- `_calc_av`
- `_calc_ant`

## 089: compiler_contribution_089 [_children0, _children]

RVA `0x00055492`–`0x000555f2`.

- `_children0`
- `_children`

## 090: compiler_contribution_090 [_init_NDP, _init_fpcache, _set_fpreg_tolock...]

RVA `0x000555f2`–`0x000579aa`.

- `_init_NDP`
- `_init_fpcache`
- `_set_fpreg_tolock`
- `_set_fpreg_toclr`
- `_find_fp`
- `_find_fp_reg`
- `_kick_NDP`
- `_fld_fpreg`
- `_fld_regvar`
- `_pop_fpreg`
- `_commit_fp`
- `_clearmap_fp`
- `_reflreg`
- `_do_reflreg`
- `_rew_extrmem`
- `_handle_firstreg`
- `_ffree_map`
- `_fxch_map`
- `_ndp_level`
- `_patch_fpregs`
- `_hi_fp`
- `_next_fp`
- `_fixdfpreg`
- `_is_fpreg`
- `_do_fpspill`
- `_newunl`
- `_freeunl`
- `_pushunl`
- `_popunl`
- `_unloadfp`
- `_reloadfp`
- `_spill_enregd_var`
- `_spill_base`
- `_reload_all_enregd_vars`
- `_reload_fpregvar`
- `_sort_fpregs`
- `_enregd_level`
- `_spill_partial`
- `_c_fstp`
- `_c_fldt`
- `_c_fxch`
- `_c_fdup`
- `_c_fld_reg`
- `_c_ffree`
- `_c_fldz`
- `_c_fstp0`
- `_c_fst`
- `_c_soft_fls`
- `_is_inorder`
- `_prfpreg`
- `_dfpreg`
- `_drv`
- `_sanity_check_fpregs`
- `_dunlstack`

## 091: compiler_contribution_091 [_cnstrpush, _cnstrpop, _constr...]

RVA `0x000579b2`–`0x000580e2`.

- `_cnstrpush`
- `_cnstrpop`
- `_constr`
- `_constrdepth`
- `_constrindex`
- `_shorten`
- `_maybereg`
- `_maybeimmed`
- `_doesnt_force`
- `_comma_is`
- `_needs_ax`
- `_wants_ax`
- `_is_mconst`
- `_notemp`
- `_maybe_half`
- `_is_ndreg`
- `_is_anyndreg`
- `_is_ndreg_internal`
- `_colonpush`

## 092: compiler_contribution_092 [_convert, _coerce, _max_type...]

RVA `0x000580e2`–`0x0005934a`.

- `_convert`
- `_coerce`
- `_max_type`
- `_remove_longaddr`
- `_typenode`
- `_typeintrinsicarg`

## 093: compiler_contribution_093 [_reserve_reg, _toocheap, _cheapmode...]

RVA `0x00059352`–`0x00059a26`.

- `_reserve_reg`
- `_toocheap`
- `_cheapmode`
- `_regsize`
- `_constrain`

## 094: compiler_contribution_094 [_sucomp, _order, _ltor...]

RVA `0x00059a32`–`0x0005a3fa`.

- `_sucomp`
- `_order`
- `_ltor`
- `_rtol`
- `_rtol2`
- `_cqdef_update`
- `_cqref_update`
- `_numinregs`
- `_sufuncalc`

## 095: compiler_contribution_095 [_type_args, _node_len, _new_op...]

RVA `0x0005a402`–`0x0005b802`.

- `_type_args`
- `_node_len`
- `_new_op`
- `_freeargs`
- `_find_temp`
- `_build_lentree`
- `_attach_len`
- `_do_intrinsic`
- `_hoist_before_intrinsic`
- `_in_hst`
- `_in_cc`
- `_is_icall`
- `_in_name`

## 096: compiler_contribution_096 [_expandMD, _mcondMD, _leamult...]

RVA `0x0005b802`–`0x0005db3a`.

- `_expandMD`
- `_mcondMD`
- `_leamult`
- `_multcon`
- `_multshift`
- `_lea_or_mov`
- `_sbbtrick`
- `_shifttricks`
- `_helper_size`
- `_generate_vcall_thunk`

## 098: D:\nt\private\crt32st\stdio\fclose.c

RVA `0x0005db42`–`0x0005dc1e`.

- `_fclose`

## 099: D:\nt\private\crt32st\stdio\_freebuf.c

RVA `0x0005dc22`–`0x0005dc52`.

- `__freebuf`

## 100: D:\nt\private\crt32st\convert\xtoa.c

RVA `0x0005dc52`–`0x0005dd32`.

- `xtoa`
- `__itoa`
- `__ltoa`
- `__ultoa`

## 101: D:\nt\private\crt32st\dos\unlink.c

RVA `0x0005dd32`–`0x0005dd7e`.

- `_remove`
- `__unlink`

## 102: D:\nt\private\crt32st\stdio\fopen.c

RVA `0x0005dd88`–`0x0005ddbc`.

- `__fsopen`
- `_fopen`

## 103: D:\nt\private\crt32st\stdio\stream.c

RVA `0x0005ddc8`–`0x0005de08`.

- `__getstream`

## 104: D:\nt\private\crt32st\stdio\_open.c

RVA `0x0005de08`–`0x0005df34`.

- `__openfile`

## 106: D:\nt\private\crt32st\lowio\open.c

RVA `0x0005df38`–`0x0005e240`.

- `__open`
- `__sopen`

## 107: D:\nt\private\crt32st\dos\access.c

RVA `0x0005e25a`–`0x0005e2b2`.

- `__access`

## 108: D:\nt\private\crt32st\lowio\chsize.c

RVA `0x0005e2ba`–`0x0005e406`.

- `__chsize`

## 109: D:\nt\private\crt32st\lowio\setmode.c

RVA `0x0005e40a`–`0x0005e48e`.

- `__setmode`

## 110: D:\nt\private\crt32st\stdio\fprintf.c

RVA `0x0005e49a`–`0x0005e4d6`.

- `_fprintf`

## 111: D:\nt\private\crt32st\stdio\_sftbuf.c

RVA `0x0005e4da`–`0x0005e5c2`.

- `__stbuf`
- `__ftbuf`

## 112: D:\nt\private\crt32st\stdio\output.c

RVA `0x0005e5ca`–`0x0005ee06`.

- `__output`
- `write_char`
- `write_multi_char`
- `write_string`
- `write_wstring`
- `get_int_arg`
- `get_long_arg`

## 113: D:\nt\private\crt32st\stdio\fread.c

RVA `0x0005ee0a`–`0x0005ef26`.

- `_fread`

## 114: D:\nt\private\crt32st\heap\free.c

RVA `0x0005ef2a`–`0x0005ef8e`.

- `_free`

## 115: D:\nt\private\crt32st\stdio\fseek.c

RVA `0x0005ef9a`–`0x0005f01e`.

- `_fseek`

## 116: D:\nt\private\crt32st\stdio\ftell.c

RVA `0x0005f02a`–`0x0005f186`.

- `_ftell`

## 117: D:\nt\private\crt32st\stdio\fwrite.c

RVA `0x0005f18a`–`0x0005f2ce`.

- `_fwrite`

## 118: compiler_contribution_118 [_get_err, _get_msg, _get_message...]

RVA `0x0005f2da`–`0x0005f55e`.

- `_get_err`
- `_get_msg`
- `_get_message`
- `_get_int`
- `_mark_pos`
- `_nearest`

## 119: D:\nt\private\crt32st\stdio\fgets.c

RVA `0x0005f56a`–`0x0005f5ee`.

- `_fgets`

## 120: compiler_contribution_120 [_getattrib, _do_type, _p2type]

RVA `0x0005f5fa`–`0x0005fde2`.

- `_getattrib`
- `_do_type`
- `_p2type`

## 121: D:\nt\private\crt32st\misc\getenv.c

RVA `0x0005fdea`–`0x0005fe62`.

- `_getenv`

## 122: compiler_contribution_122 [_optimize, _walk_canon, _walk_peeps...]

RVA `0x0005fe6a`–`0x0006404e`.

- `_optimize`
- `_walk_canon`
- `_walk_peeps`
- `_walk_fact`
- `_walk_fixup`
- `_opt_canon`
- `_distrib`
- `_push_invert`
- `_neg_const`
- `_push_convert`
- `_pop_convert`
- `_pop_it`
- `_less_precise`
- `_in_range`
- `_opt_vfact`
- `_fact_var`
- `_fact_vmult`
- `_fact_vexp`
- `_exp_build`
- `_opt_cfact`
- `_fact_const`
- `_rem_const`
- `_div_const`
- `_fact_split`
- `_rem_split`
- `_fact_unary`
- `_fact_xor`
- `_zap_var`
- `_zap_vwalk`
- `_opt_peeps`
- `_zap_cwalk`
- `_opt_band`
- `_fold_shift`
- `_band_val`
- `_rep_const`
- `_opt_fixup`
- `_pop_unary`
- `_pop_binary`
- `_fold_name`
- `_local_fold_neg`
- `_fold_neg`
- `_fold_neg_hack`
- `_nice_neg`
- `_fold_compl`
- `_fold_invert`
- `_const_sign`
- `_is_pos`
- `_nop_val`
- `_nop_const`
- `_shrink_val`
- `_int_const`
- `_is_const`
- `_new_const`
- `_StoM`
- `_log2`
- `_pushU`
- `_pushL`
- `_pushR`
- `_pushLR`
- `_popL`
- `_popR`
- `_popLR`
- `_freeL`
- `_freeR`
- `_freeS`
- `_skip1cv`

## 123: D:\nt\private\crt32st\heap\malloc.c

RVA `0x00064060`–`0x00064154`.

- `_malloc`
- `__heap_split_block`

## 124: D:\nt\private\crt32st\heap\heapgrow.c

RVA `0x00064160`–`0x00064388`.

- `__heap_grow`
- `_heap_new_region`
- `__heap_grow_region`
- `__heap_free_region`

## 125: D:\nt\private\crt32st\heap\heapadd.c

RVA `0x00064396`–`0x0006462a`.

- `__heapadd`
- `__heap_addblock`
- `_before`

## 126: D:\nt\private\crt32st\heap\findaddr.c

RVA `0x00064636`–`0x000646aa`.

- `__heap_findaddr`

## 127: D:\nt\private\crt32st\heap\heapsrch.c

RVA `0x000646b6`–`0x000647ce`.

- `__heap_search`

## 128: compiler_contribution_128 [_mem_size]

RVA `0x000647d6`–`0x000647e2`.

- `_mem_size`

## 129: D:\nt\private\crt32st\string\memchr.c

RVA `0x000647e6`–`0x0006481e`.

- `_memchr`

## 130: D:\nt\private\crt32st\string\memcpy.c

RVA `0x00064826`–`0x00064852`.

- `_memcpy`

## 131: D:\nt\private\crt32st\string\memmove.c

RVA `0x00064856`–`0x000648ae`.

- `_memmove`

## 132: D:\nt\private\crt32st\string\memset.c

RVA `0x000648b6`–`0x000648e2`.

- `_memset`

## 133: compiler_contribution_133 [_op_size, _c_size, _ea_size...]

RVA `0x000648e6`–`0x0006560e`.

- `_op_size`
- `_c_size`
- `_ea_size`
- `_imm_size`
- `_sign_extend`

## 134: compiler_contribution_134 [_our_ltoa]

RVA `0x00065616`–`0x0006568a`.

- `_our_ltoa`

## 135: D:\nt\private\crt32st\stdio\printf.c

RVA `0x00065696`–`0x000656d6`.

- `_printf`

## 136: compiler_contribution_136 [_sumaxset, _susumset, _suconflict...]

RVA `0x000656d6`–`0x00065eba`.

- `_sumaxset`
- `_susumset`
- `_suconflict`
- `_suheuristics`
- `_sutovect`
- `_suhoru`
- `_suheld`
- `_suuses`
- `_sufun`
- `_regtosuv`
- `_cnsttovect`
- `_suinit`
- `_setavail`
- `_prsuvect`

## 137: compiler_contribution_137 [_sorttree, _skipcvt, _compute_complexity...]

RVA `0x00065ec6`–`0x000663aa`.

- `_sorttree`
- `_skipcvt`
- `_compute_complexity`
- `_sortassoc`
- `_sortcomm`
- `_sortswap`
- `_relopposite`

## 138: D:\nt\private\crt32st\stdio\setbuf.c

RVA `0x000663b6`–`0x000663da`.

- `_setbuf`

## 139: D:\nt\private\crt32st\stdio\setvbuf.c

RVA `0x000663ec`–`0x000664b0`.

- `_setvbuf`

## 140: D:\nt\private\crt32st\stdio\sprintf.c

RVA `0x000664bc`–`0x00066528`.

- `_sprintf`

## 141: D:\nt\private\crt32st\stdio\sscanf.c

RVA `0x0006652c`–`0x00066574`.

- `_sscanf`

## 142: D:\nt\private\crt32st\stdio\input.c

RVA `0x0006657c`–`0x00066e3c`.

- `__input`
- `_hextodec`
- `_inc`
- `_un_inc`
- `_whiteout`

## 143: D:\nt\private\crt32st\string\strcat.c

RVA `0x00066e3c`–`0x00066e80`.

- `_strcat`
- `_strcpy`

## 144: D:\nt\private\crt32st\string\strcmp.c

RVA `0x00066e8c`–`0x00066ed0`.

- `_strcmp`

## 145: D:\nt\private\crt32st\string\strlen.c

RVA `0x00066edc`–`0x00066ef4`.

- `_strlen`

## 146: D:\nt\private\crt32st\string\strncmp.c

RVA `0x00066efc`–`0x00066f30`.

- `_strncmp`

## 147: compiler_contribution_147 [_caseindex, _cnt_cases, _gencase...]

RVA `0x00066f3c`–`0x00068428`.

- `_caseindex`
- `_cnt_cases`
- `_gencase`
- `_emit_label`
- `_linearsearch`
- `_jumptable`
- `_binsearch`
- `_switch_code`
- `_switches`
- `_num_common`
- `_scale_switch`
- `_split`
- `_divide`
- `_reattach`
- `_num_const_diff`
- `_scale_multi_switch`
- `_determine_scalability`
- `_tweak_multi_arm`
- `_signed_short`
- `_order_on_order`
- `_reorder`
- `_collect_cases`
- `_show`
- `_card`

## 148: compiler_contribution_148 [_emit_jmp, _emit_jumptable, _emit_bcc...]

RVA `0x0006842c`–`0x000693b8`.

- `_emit_jmp`
- `_emit_jumptable`
- `_emit_bcc`
- `_emit_div`
- `_emit_sub`
- `_emit_cmp`
- `_emit_push`
- `_emit_pop`
- `_emit_shift`
- `_init_reg_cond`
- `_switch_use_reg`
- `_switch_free_reg`
- `_switch_choose_reg`
- `_adjust_reg`
- `_emit_mask`

## 150: D:\nt\private\crt32st\stdio\ungetc.c

RVA `0x000693bc`–`0x00069428`.

- `_ungetc`

## 151: D:\nt\private\crt32st\stdio\vprintf.c

RVA `0x0006942c`–`0x0006946c`.

- `_vprintf`

