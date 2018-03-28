	.file	"2_signal_gestionnaire_normes_ok.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"debut du gestionnaire de signal %d\n"
.LC1:
	.string	"%d\n"
	.align 8
.LC2:
	.string	"fin du gestionnaire de signal %d\n"
	.text
	.globl	gestionnaire
	.type	gestionnaire, @function
gestionnaire:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	$gestionnaire, %esi
	movl	%eax, %edi
	call	signal
	movq	stdout(%rip), %rax
	movl	-20(%rbp), %edx
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, -4(%rbp)
	jmp	.L2
.L3:
	movq	stdout(%rip), %rax
	movl	-4(%rbp), %edx
	movl	$.LC1, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, %edi
	call	sleep
	addl	$1, -4(%rbp)
.L2:
	cmpl	$3, -4(%rbp)
	jle	.L3
	movq	stdout(%rip), %rax
	movl	-20(%rbp), %edx
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	gestionnaire, .-gestionnaire
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$gestionnaire, %esi
	movl	$10, %edi
	call	signal
	call	fork
	testl	%eax, %eax
	jne	.L5
	call	getppid
	movl	$10, %esi
	movl	%eax, %edi
	call	kill
	movl	$1, %edi
	call	sleep
	call	getppid
	movl	$10, %esi
	movl	%eax, %edi
	call	kill
	jmp	.L8
.L5:
	call	pause
	jmp	.L5
.L8:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
