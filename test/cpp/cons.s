	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## BB#0:
	pushq	%rbp
Ltmp8:
	.cfi_def_cfa_offset 16
Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp10:
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$24, %rsp
Ltmp11:
	.cfi_offset %rbx, -24
	leaq	-16(%rbp), %rdi
	callq	__ZN2T1C2Ev
Ltmp0:
	leaq	-24(%rbp), %rdi
	movl	$1, %esi
	callq	__ZN2T1C2Ei
Ltmp1:
## BB#1:                                ## %_ZN2T1C1Ei.exit
	movl	-24(%rbp), %eax
	movl	%eax, -16(%rbp)
Ltmp2:
	leaq	-24(%rbp), %rdi
	callq	__ZN2T1D2Ev
Ltmp3:
## BB#2:                                ## %_ZN2T1D1Ev.exit
	leaq	-16(%rbp), %rdi
	callq	__ZN2T1D2Ev
	xorl	%eax, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	retq
LBB0_3:
Ltmp4:
	movq	%rax, %rbx
Ltmp5:
	leaq	-16(%rbp), %rdi
	callq	__ZN2T1D2Ev
Ltmp6:
## BB#4:                                ## %_ZN2T1D1Ev.exit1
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB0_5:
Ltmp7:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table0:
Lexception0:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset0 = Lfunc_begin0-Lfunc_begin0       ## >> Call Site 1 <<
	.long	Lset0
Lset1 = Ltmp0-Lfunc_begin0              ##   Call between Lfunc_begin0 and Ltmp0
	.long	Lset1
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset2 = Ltmp0-Lfunc_begin0              ## >> Call Site 2 <<
	.long	Lset2
Lset3 = Ltmp3-Ltmp0                     ##   Call between Ltmp0 and Ltmp3
	.long	Lset3
Lset4 = Ltmp4-Lfunc_begin0              ##     jumps to Ltmp4
	.long	Lset4
	.byte	0                       ##   On action: cleanup
Lset5 = Ltmp3-Lfunc_begin0              ## >> Call Site 3 <<
	.long	Lset5
Lset6 = Ltmp5-Ltmp3                     ##   Call between Ltmp3 and Ltmp5
	.long	Lset6
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset7 = Ltmp5-Lfunc_begin0              ## >> Call Site 4 <<
	.long	Lset7
Lset8 = Ltmp6-Ltmp5                     ##   Call between Ltmp5 and Ltmp6
	.long	Lset8
Lset9 = Ltmp7-Lfunc_begin0              ##     jumps to Ltmp7
	.long	Lset9
	.byte	1                       ##   On action: 1
Lset10 = Ltmp6-Lfunc_begin0             ## >> Call Site 5 <<
	.long	Lset10
Lset11 = Lfunc_end0-Ltmp6               ##   Call between Ltmp6 and Lfunc_end0
	.long	Lset11
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.private_extern	___clang_call_terminate
	.globl	___clang_call_terminate
	.weak_def_can_be_hidden	___clang_call_terminate
	.align	4, 0x90
___clang_call_terminate:                ## @__clang_call_terminate
## BB#0:
	pushq	%rbp
	movq	%rsp, %rbp
	callq	___cxa_begin_catch
	callq	__ZSt9terminatev

	.globl	__ZN2T1C2Ev
	.weak_def_can_be_hidden	__ZN2T1C2Ev
	.align	4, 0x90
__ZN2T1C2Ev:                            ## @_ZN2T1C2Ev
Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception2
## BB#0:
	pushq	%rbp
Ltmp20:
	.cfi_def_cfa_offset 16
Ltmp21:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp22:
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$16, %rsp
Ltmp23:
	.cfi_offset %rbx, -32
Ltmp24:
	.cfi_offset %r14, -24
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	leaq	L_.str(%rip), %rsi
	movl	$17, %edx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rbx
	movq	(%rbx), %rax
	movq	-24(%rax), %rsi
	addq	%rbx, %rsi
	leaq	-24(%rbp), %r14
	movq	%r14, %rdi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp12:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	movq	%r14, %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp13:
## BB#1:
	movq	(%rax), %rcx
	movq	56(%rcx), %rcx
Ltmp14:
	movl	$10, %esi
	movq	%rax, %rdi
	callq	*%rcx
	movb	%al, %r14b
Ltmp15:
## BB#2:                                ## %_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc.exit
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movsbl	%r14b, %esi
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv
	addq	$16, %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
LBB2_3:
Ltmp16:
	movq	%rax, %rbx
Ltmp17:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp18:
## BB#4:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB2_5:
Ltmp19:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end2:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table2:
Lexception2:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset12 = Lfunc_begin2-Lfunc_begin2      ## >> Call Site 1 <<
	.long	Lset12
Lset13 = Ltmp12-Lfunc_begin2            ##   Call between Lfunc_begin2 and Ltmp12
	.long	Lset13
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset14 = Ltmp12-Lfunc_begin2            ## >> Call Site 2 <<
	.long	Lset14
Lset15 = Ltmp15-Ltmp12                  ##   Call between Ltmp12 and Ltmp15
	.long	Lset15
Lset16 = Ltmp16-Lfunc_begin2            ##     jumps to Ltmp16
	.long	Lset16
	.byte	0                       ##   On action: cleanup
Lset17 = Ltmp15-Lfunc_begin2            ## >> Call Site 3 <<
	.long	Lset17
Lset18 = Ltmp17-Ltmp15                  ##   Call between Ltmp15 and Ltmp17
	.long	Lset18
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset19 = Ltmp17-Lfunc_begin2            ## >> Call Site 4 <<
	.long	Lset19
Lset20 = Ltmp18-Ltmp17                  ##   Call between Ltmp17 and Ltmp18
	.long	Lset20
Lset21 = Ltmp19-Lfunc_begin2            ##     jumps to Ltmp19
	.long	Lset21
	.byte	1                       ##   On action: 1
Lset22 = Ltmp18-Lfunc_begin2            ## >> Call Site 5 <<
	.long	Lset22
Lset23 = Lfunc_end2-Ltmp18              ##   Call between Ltmp18 and Lfunc_end2
	.long	Lset23
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.globl	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.weak_def_can_be_hidden	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	.align	4, 0x90
__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m: ## @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
Lfunc_begin3:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception3
## BB#0:
	pushq	%rbp
Ltmp55:
	.cfi_def_cfa_offset 16
Ltmp56:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp57:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$56, %rsp
Ltmp58:
	.cfi_offset %rbx, -56
Ltmp59:
	.cfi_offset %r12, -48
Ltmp60:
	.cfi_offset %r13, -40
Ltmp61:
	.cfi_offset %r14, -32
Ltmp62:
	.cfi_offset %r15, -24
	movq	%rdx, %r14
	movq	%rsi, %r15
	movq	%rdi, %rbx
Ltmp25:
	leaq	-64(%rbp), %rdi
	movq	%rbx, %rsi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_
Ltmp26:
## BB#1:
	cmpb	$0, -64(%rbp)
	je	LBB3_13
## BB#2:
	movq	(%rbx), %rax
	movq	-24(%rax), %r12
	movq	40(%r12,%rbx), %rdi
	movl	$176, %eax
	andl	8(%r12,%rbx), %eax
	cmpl	$32, %eax
	movq	%r15, %r13
	jne	LBB3_4
## BB#3:
	leaq	(%r15,%r14), %r13
LBB3_4:
	leaq	(%rbx,%r12), %r8
	movl	144(%rbx,%r12), %eax
	cmpl	$-1, %eax
	jne	LBB3_10
## BB#5:
Ltmp27:
	movq	%rdi, -72(%rbp)         ## 8-byte Spill
	leaq	-48(%rbp), %rdi
	movq	%r8, %rsi
	movq	%r8, -80(%rbp)          ## 8-byte Spill
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp28:
## BB#6:                                ## %.noexc
Ltmp29:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	leaq	-48(%rbp), %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp30:
## BB#7:
	movq	(%rax), %rcx
	movq	56(%rcx), %rcx
Ltmp31:
	movl	$32, %esi
	movq	%rax, %rdi
	callq	*%rcx
	movb	%al, -81(%rbp)          ## 1-byte Spill
Ltmp32:
## BB#8:                                ## %_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc.exit.i
Ltmp37:
	leaq	-48(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp38:
## BB#9:                                ## %.noexc1
	movsbl	-81(%rbp), %eax         ## 1-byte Folded Reload
	movl	%eax, 144(%rbx,%r12)
	movq	-72(%rbp), %rdi         ## 8-byte Reload
	movq	-80(%rbp), %r8          ## 8-byte Reload
LBB3_10:
	addq	%r15, %r14
Ltmp39:
	movsbl	%al, %r9d
	movq	%r15, %rsi
	movq	%r13, %rdx
	movq	%r14, %rcx
	callq	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Ltmp40:
## BB#11:
	testq	%rax, %rax
	jne	LBB3_13
## BB#12:
	movq	(%rbx), %rax
	movq	-24(%rax), %rax
	leaq	(%rbx,%rax), %rdi
	movl	32(%rbx,%rax), %esi
	orl	$5, %esi
Ltmp41:
	callq	__ZNSt3__18ios_base5clearEj
Ltmp42:
LBB3_13:                                ## %_ZNSt3__19basic_iosIcNS_11char_traitsIcEEE8setstateEj.exit
Ltmp46:
	leaq	-64(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp47:
LBB3_21:
	movq	%rbx, %rax
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB3_18:
Ltmp48:
	movq	%rax, %r14
	jmp	LBB3_19
LBB3_16:
Ltmp43:
	movq	%rax, %r14
	jmp	LBB3_17
LBB3_14:
Ltmp33:
	movq	%rax, %r14
Ltmp34:
	leaq	-48(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp35:
LBB3_17:                                ## %.body
Ltmp44:
	leaq	-64(%rbp), %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev
Ltmp45:
LBB3_19:
	movq	%r14, %rdi
	callq	___cxa_begin_catch
	movq	(%rbx), %rax
	movq	%rbx, %rdi
	addq	-24(%rax), %rdi
Ltmp49:
	callq	__ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv
Ltmp50:
## BB#20:
	callq	___cxa_end_catch
	jmp	LBB3_21
LBB3_22:
Ltmp51:
	movq	%rax, %rbx
Ltmp52:
	callq	___cxa_end_catch
Ltmp53:
## BB#23:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB3_24:
Ltmp54:
	movq	%rax, %rdi
	callq	___clang_call_terminate
LBB3_15:
Ltmp36:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end3:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table3:
Lexception3:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.asciz	"\245\201\200\200"      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.ascii	"\234\001"              ## Call site table length
Lset24 = Ltmp25-Lfunc_begin3            ## >> Call Site 1 <<
	.long	Lset24
Lset25 = Ltmp26-Ltmp25                  ##   Call between Ltmp25 and Ltmp26
	.long	Lset25
Lset26 = Ltmp48-Lfunc_begin3            ##     jumps to Ltmp48
	.long	Lset26
	.byte	1                       ##   On action: 1
Lset27 = Ltmp27-Lfunc_begin3            ## >> Call Site 2 <<
	.long	Lset27
Lset28 = Ltmp28-Ltmp27                  ##   Call between Ltmp27 and Ltmp28
	.long	Lset28
Lset29 = Ltmp43-Lfunc_begin3            ##     jumps to Ltmp43
	.long	Lset29
	.byte	1                       ##   On action: 1
Lset30 = Ltmp29-Lfunc_begin3            ## >> Call Site 3 <<
	.long	Lset30
Lset31 = Ltmp32-Ltmp29                  ##   Call between Ltmp29 and Ltmp32
	.long	Lset31
Lset32 = Ltmp33-Lfunc_begin3            ##     jumps to Ltmp33
	.long	Lset32
	.byte	1                       ##   On action: 1
Lset33 = Ltmp37-Lfunc_begin3            ## >> Call Site 4 <<
	.long	Lset33
Lset34 = Ltmp42-Ltmp37                  ##   Call between Ltmp37 and Ltmp42
	.long	Lset34
Lset35 = Ltmp43-Lfunc_begin3            ##     jumps to Ltmp43
	.long	Lset35
	.byte	1                       ##   On action: 1
Lset36 = Ltmp46-Lfunc_begin3            ## >> Call Site 5 <<
	.long	Lset36
Lset37 = Ltmp47-Ltmp46                  ##   Call between Ltmp46 and Ltmp47
	.long	Lset37
Lset38 = Ltmp48-Lfunc_begin3            ##     jumps to Ltmp48
	.long	Lset38
	.byte	1                       ##   On action: 1
Lset39 = Ltmp34-Lfunc_begin3            ## >> Call Site 6 <<
	.long	Lset39
Lset40 = Ltmp35-Ltmp34                  ##   Call between Ltmp34 and Ltmp35
	.long	Lset40
Lset41 = Ltmp36-Lfunc_begin3            ##     jumps to Ltmp36
	.long	Lset41
	.byte	1                       ##   On action: 1
Lset42 = Ltmp44-Lfunc_begin3            ## >> Call Site 7 <<
	.long	Lset42
Lset43 = Ltmp45-Ltmp44                  ##   Call between Ltmp44 and Ltmp45
	.long	Lset43
Lset44 = Ltmp54-Lfunc_begin3            ##     jumps to Ltmp54
	.long	Lset44
	.byte	1                       ##   On action: 1
Lset45 = Ltmp45-Lfunc_begin3            ## >> Call Site 8 <<
	.long	Lset45
Lset46 = Ltmp49-Ltmp45                  ##   Call between Ltmp45 and Ltmp49
	.long	Lset46
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset47 = Ltmp49-Lfunc_begin3            ## >> Call Site 9 <<
	.long	Lset47
Lset48 = Ltmp50-Ltmp49                  ##   Call between Ltmp49 and Ltmp50
	.long	Lset48
Lset49 = Ltmp51-Lfunc_begin3            ##     jumps to Ltmp51
	.long	Lset49
	.byte	0                       ##   On action: cleanup
Lset50 = Ltmp50-Lfunc_begin3            ## >> Call Site 10 <<
	.long	Lset50
Lset51 = Ltmp52-Ltmp50                  ##   Call between Ltmp50 and Ltmp52
	.long	Lset51
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset52 = Ltmp52-Lfunc_begin3            ## >> Call Site 11 <<
	.long	Lset52
Lset53 = Ltmp53-Ltmp52                  ##   Call between Ltmp52 and Ltmp53
	.long	Lset53
Lset54 = Ltmp54-Lfunc_begin3            ##     jumps to Ltmp54
	.long	Lset54
	.byte	1                       ##   On action: 1
Lset55 = Ltmp53-Lfunc_begin3            ## >> Call Site 12 <<
	.long	Lset55
Lset56 = Lfunc_end3-Ltmp53              ##   Call between Ltmp53 and Lfunc_end3
	.long	Lset56
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.private_extern	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.globl	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.weak_def_can_be_hidden	__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
	.align	4, 0x90
__ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_: ## @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_
Lfunc_begin4:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception4
## BB#0:
	pushq	%rbp
Ltmp69:
	.cfi_def_cfa_offset 16
Ltmp70:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp71:
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
Ltmp72:
	.cfi_offset %rbx, -56
Ltmp73:
	.cfi_offset %r12, -48
Ltmp74:
	.cfi_offset %r13, -40
Ltmp75:
	.cfi_offset %r14, -32
Ltmp76:
	.cfi_offset %r15, -24
	movq	%r8, %r14
	movq	%rcx, %r13
	movq	%rdi, %rbx
	xorl	%eax, %eax
	testq	%rbx, %rbx
	je	LBB4_12
## BB#1:
	movq	%r13, %rax
	subq	%rsi, %rax
	movq	24(%r14), %rcx
	xorl	%r15d, %r15d
	subq	%rax, %rcx
	cmovgq	%rcx, %r15
	movq	%rdx, %r12
	subq	%rsi, %r12
	testq	%r12, %r12
	jle	LBB4_3
## BB#2:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
	movq	%r13, -80(%rbp)         ## 8-byte Spill
	movq	%rdx, -72(%rbp)         ## 8-byte Spill
	movq	%r12, %rdx
	movl	%r9d, %r13d
	callq	*96(%rax)
	movl	%r13d, %r9d
	movq	-72(%rbp), %rdx         ## 8-byte Reload
	movq	-80(%rbp), %r13         ## 8-byte Reload
	movq	%rax, %rcx
	xorl	%eax, %eax
	cmpq	%r12, %rcx
	jne	LBB4_12
LBB4_3:
	testq	%r15, %r15
	jle	LBB4_9
## BB#4:
	movq	%rdx, -72(%rbp)         ## 8-byte Spill
	movq	%r14, %r12
	movsbl	%r9b, %edx
	leaq	-64(%rbp), %rdi
	movq	%r15, %rsi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc
	testb	$1, -64(%rbp)
	jne	LBB4_5
## BB#6:
	leaq	-63(%rbp), %rsi
	jmp	LBB4_7
LBB4_5:
	movq	-48(%rbp), %rsi
LBB4_7:                                 ## %_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE4dataEv.exit
	movq	(%rbx), %rax
	movq	96(%rax), %rax
Ltmp63:
	movq	%rbx, %rdi
	movq	%r15, %rdx
	callq	*%rax
	movq	%rax, %r14
Ltmp64:
## BB#8:                                ## %_ZNSt3__115basic_streambufIcNS_11char_traitsIcEEE5sputnEPKcl.exit
	leaq	-64(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
	xorl	%eax, %eax
	cmpq	%r15, %r14
	movq	%r12, %r14
	movq	-72(%rbp), %rdx         ## 8-byte Reload
	jne	LBB4_12
LBB4_9:                                 ## %.thread
	subq	%rdx, %r13
	testq	%r13, %r13
	jle	LBB4_11
## BB#10:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
	movq	%rdx, %rsi
	movq	%r13, %rdx
	callq	*96(%rax)
	movq	%rax, %rcx
	xorl	%eax, %eax
	cmpq	%r13, %rcx
	jne	LBB4_12
LBB4_11:
	movq	$0, 24(%r14)
	movq	%rbx, %rax
LBB4_12:
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB4_13:
Ltmp65:
	movq	%rax, %rbx
Ltmp66:
	leaq	-64(%rbp), %rdi
	callq	__ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev
Ltmp67:
## BB#14:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB4_15:
Ltmp68:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end4:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table4:
Lexception4:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset57 = Lfunc_begin4-Lfunc_begin4      ## >> Call Site 1 <<
	.long	Lset57
Lset58 = Ltmp63-Lfunc_begin4            ##   Call between Lfunc_begin4 and Ltmp63
	.long	Lset58
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset59 = Ltmp63-Lfunc_begin4            ## >> Call Site 2 <<
	.long	Lset59
Lset60 = Ltmp64-Ltmp63                  ##   Call between Ltmp63 and Ltmp64
	.long	Lset60
Lset61 = Ltmp65-Lfunc_begin4            ##     jumps to Ltmp65
	.long	Lset61
	.byte	0                       ##   On action: cleanup
Lset62 = Ltmp64-Lfunc_begin4            ## >> Call Site 3 <<
	.long	Lset62
Lset63 = Ltmp66-Ltmp64                  ##   Call between Ltmp64 and Ltmp66
	.long	Lset63
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset64 = Ltmp66-Lfunc_begin4            ## >> Call Site 4 <<
	.long	Lset64
Lset65 = Ltmp67-Ltmp66                  ##   Call between Ltmp66 and Ltmp67
	.long	Lset65
Lset66 = Ltmp68-Lfunc_begin4            ##     jumps to Ltmp68
	.long	Lset66
	.byte	1                       ##   On action: 1
Lset67 = Ltmp67-Lfunc_begin4            ## >> Call Site 5 <<
	.long	Lset67
Lset68 = Lfunc_end4-Ltmp67              ##   Call between Ltmp67 and Lfunc_end4
	.long	Lset68
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.globl	__ZN2T1C2Ei
	.weak_def_can_be_hidden	__ZN2T1C2Ei
	.align	4, 0x90
__ZN2T1C2Ei:                            ## @_ZN2T1C2Ei
Lfunc_begin5:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception5
## BB#0:
	pushq	%rbp
Ltmp85:
	.cfi_def_cfa_offset 16
Ltmp86:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp87:
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$16, %rsp
Ltmp88:
	.cfi_offset %rbx, -32
Ltmp89:
	.cfi_offset %r14, -24
	movl	%esi, (%rdi)
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	leaq	L_.str1(%rip), %rsi
	movl	$9, %edx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rbx
	movq	(%rbx), %rax
	movq	-24(%rax), %rsi
	addq	%rbx, %rsi
	leaq	-24(%rbp), %r14
	movq	%r14, %rdi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp77:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	movq	%r14, %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp78:
## BB#1:
	movq	(%rax), %rcx
	movq	56(%rcx), %rcx
Ltmp79:
	movl	$10, %esi
	movq	%rax, %rdi
	callq	*%rcx
	movb	%al, %r14b
Ltmp80:
## BB#2:                                ## %_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc.exit
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movsbl	%r14b, %esi
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv
	addq	$16, %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
LBB5_3:
Ltmp81:
	movq	%rax, %rbx
Ltmp82:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp83:
## BB#4:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB5_5:
Ltmp84:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end5:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table5:
Lexception5:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset69 = Lfunc_begin5-Lfunc_begin5      ## >> Call Site 1 <<
	.long	Lset69
Lset70 = Ltmp77-Lfunc_begin5            ##   Call between Lfunc_begin5 and Ltmp77
	.long	Lset70
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset71 = Ltmp77-Lfunc_begin5            ## >> Call Site 2 <<
	.long	Lset71
Lset72 = Ltmp80-Ltmp77                  ##   Call between Ltmp77 and Ltmp80
	.long	Lset72
Lset73 = Ltmp81-Lfunc_begin5            ##     jumps to Ltmp81
	.long	Lset73
	.byte	0                       ##   On action: cleanup
Lset74 = Ltmp80-Lfunc_begin5            ## >> Call Site 3 <<
	.long	Lset74
Lset75 = Ltmp82-Ltmp80                  ##   Call between Ltmp80 and Ltmp82
	.long	Lset75
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset76 = Ltmp82-Lfunc_begin5            ## >> Call Site 4 <<
	.long	Lset76
Lset77 = Ltmp83-Ltmp82                  ##   Call between Ltmp82 and Ltmp83
	.long	Lset77
Lset78 = Ltmp84-Lfunc_begin5            ##     jumps to Ltmp84
	.long	Lset78
	.byte	1                       ##   On action: 1
Lset79 = Ltmp83-Lfunc_begin5            ## >> Call Site 5 <<
	.long	Lset79
Lset80 = Lfunc_end5-Ltmp83              ##   Call between Ltmp83 and Lfunc_end5
	.long	Lset80
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__textcoal_nt,coalesced,pure_instructions
	.globl	__ZN2T1D2Ev
	.weak_def_can_be_hidden	__ZN2T1D2Ev
	.align	4, 0x90
__ZN2T1D2Ev:                            ## @_ZN2T1D2Ev
Lfunc_begin6:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception6
## BB#0:
	pushq	%rbp
Ltmp98:
	.cfi_def_cfa_offset 16
Ltmp99:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp100:
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$16, %rsp
Ltmp101:
	.cfi_offset %rbx, -32
Ltmp102:
	.cfi_offset %r14, -24
	movq	__ZNSt3__14coutE@GOTPCREL(%rip), %rdi
	leaq	L_.str2(%rip), %rsi
	movl	$8, %edx
	callq	__ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m
	movq	%rax, %rbx
	movq	(%rbx), %rax
	movq	-24(%rax), %rsi
	addq	%rbx, %rsi
	leaq	-24(%rbp), %r14
	movq	%r14, %rdi
	callq	__ZNKSt3__18ios_base6getlocEv
Ltmp90:
	movq	__ZNSt3__15ctypeIcE2idE@GOTPCREL(%rip), %rsi
	movq	%r14, %rdi
	callq	__ZNKSt3__16locale9use_facetERNS0_2idE
Ltmp91:
## BB#1:
	movq	(%rax), %rcx
	movq	56(%rcx), %rcx
Ltmp92:
	movl	$10, %esi
	movq	%rax, %rdi
	callq	*%rcx
	movb	%al, %r14b
Ltmp93:
## BB#2:                                ## %_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc.exit
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
	movsbl	%r14b, %esi
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE3putEc
	movq	%rbx, %rdi
	callq	__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE5flushEv
	addq	$16, %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
LBB6_3:
Ltmp94:
	movq	%rax, %rbx
Ltmp95:
	leaq	-24(%rbp), %rdi
	callq	__ZNSt3__16localeD1Ev
Ltmp96:
## BB#4:
	movq	%rbx, %rdi
	callq	__Unwind_Resume
LBB6_5:
Ltmp97:
	movq	%rax, %rdi
	callq	___clang_call_terminate
Lfunc_end6:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.align	2
GCC_except_table6:
Lexception6:
	.byte	255                     ## @LPStart Encoding = omit
	.byte	155                     ## @TType Encoding = indirect pcrel sdata4
	.byte	73                      ## @TType base offset
	.byte	3                       ## Call site Encoding = udata4
	.byte	65                      ## Call site table length
Lset81 = Lfunc_begin6-Lfunc_begin6      ## >> Call Site 1 <<
	.long	Lset81
Lset82 = Ltmp90-Lfunc_begin6            ##   Call between Lfunc_begin6 and Ltmp90
	.long	Lset82
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset83 = Ltmp90-Lfunc_begin6            ## >> Call Site 2 <<
	.long	Lset83
Lset84 = Ltmp93-Ltmp90                  ##   Call between Ltmp90 and Ltmp93
	.long	Lset84
Lset85 = Ltmp94-Lfunc_begin6            ##     jumps to Ltmp94
	.long	Lset85
	.byte	0                       ##   On action: cleanup
Lset86 = Ltmp93-Lfunc_begin6            ## >> Call Site 3 <<
	.long	Lset86
Lset87 = Ltmp95-Ltmp93                  ##   Call between Ltmp93 and Ltmp95
	.long	Lset87
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
Lset88 = Ltmp95-Lfunc_begin6            ## >> Call Site 4 <<
	.long	Lset88
Lset89 = Ltmp96-Ltmp95                  ##   Call between Ltmp95 and Ltmp96
	.long	Lset89
Lset90 = Ltmp97-Lfunc_begin6            ##     jumps to Ltmp97
	.long	Lset90
	.byte	1                       ##   On action: 1
Lset91 = Ltmp96-Lfunc_begin6            ## >> Call Site 5 <<
	.long	Lset91
Lset92 = Lfunc_end6-Ltmp96              ##   Call between Ltmp96 and Lfunc_end6
	.long	Lset92
	.long	0                       ##     has no landing pad
	.byte	0                       ##   On action: cleanup
	.byte	1                       ## >> Action Record 1 <<
                                        ##   Catch TypeInfo 1
	.byte	0                       ##   No further actions
                                        ## >> Catch TypeInfos <<
	.long	0                       ## TypeInfo 1
	.align	2

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Default Construct"

L_.str1:                                ## @.str1
	.asciz	"Construct"

L_.str2:                                ## @.str2
	.asciz	"Destruct"


.subsections_via_symbols
