;  Name: Stephaney Chang
;  NSHE ID: 2001508920	
;  Section: 1003
;  Assignment: 2
;  Description: Program performing basic arithmetic of addition
;		 and subtraction.


; *****************************************************************
;  Static Data Declarations (initialized)

section	.data

; -----
;  Define standard constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

; -----
;  Initialized Static Data Declarations.

;	Place data declarations here...

bVar1		db	30
bVar2		db	19
bAns1		db	0
bAns2		db	0
wVar1		dw	4813
wVar2		dw	2189
wAns1		dw	0
wAns2		dw	0
dVar1		dd	185752666
dVar2		dd	101789321
dVar3		dd	-57142
dAns1		dd	0
dAns2		dd	0
flt1		dd	-17.75
flt2		dd	7.125
tao		dd	6.28318
qVar1		dq	123169427153
myClass		db	"CS 218", NULL
edName		db	"Ed Jorgensen", NULL
myName		db	"your name goes here", NULL


; ----------------------------------------------
;  Uninitialized Static Data Declarations.

section	.bss

;	Place data declarations for uninitialized data here...
;	(i.e., large arrays that are not initialized)


; *****************************************************************

section	.text
global _start
_start:

;bAns1 = bVar1 + bVar2
mov al, byte[bVar1]
add al, byte[bVar2]
mov byte[bAns1], al

;Reset al
mov al, 0

;bAns2 = bVar1 - bVar2
mov al, byte[bVar1]
sub al, byte[bVar2]
mov byte[bAns2], al

;wAns1 = wVar1 + wVar2
mov ax, word[wVar1]
add ax, word[wVar2]
mov word[wAns1], ax

;Reset ax
mov ax, 0

;wAns2 = wVar1 - wVar2
mov ax, word[wVar1]
sub ax, word[wVar2]
mov word[wAns2], ax

;dAns1 = dVar1 + dVar2
mov eax, dword[dVar1]
add eax, dword[dVar2]
mov dword[dAns1], eax

;Reset eax
mov eax, 0

;dAns2 = dVar1 - dVar2
mov eax, dword[dVar1]
sub eax, dword[dVar2]
mov dword[dAns2], eax

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall
