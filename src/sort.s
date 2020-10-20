	.file	"sort.c"
	.text
	.globl	BubbleSort
	.type	BubbleSort, @function
BubbleSort:
.LFB0:
	.cfi_startproc
	leal	-1(%rsi), %r8d
	xorl	%ecx, %ecx
.L2:
	cmpl	%esi, %ecx
	jge	.L8
	xorl	%eax, %eax
.L5:
	cmpl	%eax, %r8d
	jle	.L9
	movq	(%rdi,%rax,8), %rdx
	movq	8(%rdi,%rax,8), %r9
	cmpq	%r9, %rdx
	jle	.L3
	movslq	%edx, %rdx
	movq	%r9, (%rdi,%rax,8)
	movq	%rdx, 8(%rdi,%rax,8)
.L3:
	incq	%rax
	jmp	.L5
.L9:
	incl	%ecx
	decl	%r8d
	jmp	.L2
.L8:
	ret
	.cfi_endproc
.LFE0:
	.size	BubbleSort, .-BubbleSort
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
