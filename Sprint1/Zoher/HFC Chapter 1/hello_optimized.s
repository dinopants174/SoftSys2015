##This is the assembly language output when compiled hello.c -S -O2
##The assembly code no longer stores the value of 5 and just "Hello World"

	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	leaq	L_str(%rip), %rdi
	callq	_puts
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_str:                                  ## @str
	.asciz	"Hello World"


.subsections_via_symbols
