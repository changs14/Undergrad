; *****************************************************************
;  Name: Stephaney Chang
;  NSHE ID: 2001508920	
;  Section: 1002
;  Assignment: 12
;  Description: Program that will count the amount of narcissistic numbers
;		in a give list up to a certain limit. The program will
;		use threads in order to improve performance.

; -----
;  Narcissistic Numbers
;	0, 1, 2, 3, 4, 5,
;	6, 7, 8, 9, 153,
;	370, 371, 407, 1634, 8208,
;	9474, 54748, 92727, 93084, 548834,
;	1741725, 4210818, 9800817, 9926315, 24678050,
;	24678051, 88593477, 146511208, 472335975, 534494836,
;	912985153, 4679307774, 32164049650, 32164049651

; ***************************************************************

section	.data

; -----
;  Define standard constants.

LF		equ	10			; line feed
NULL		equ	0			; end of string
ESC		equ	27			; escape key

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; Successful operation
NOSUCCESS	equ	1			; Unsuccessful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; call code for read
SYS_write	equ	1			; call code for write
SYS_open	equ	2			; call code for file open
SYS_close	equ	3			; call code for file close
SYS_fork	equ	57			; call code for fork
SYS_exit	equ	60			; call code for terminate
SYS_creat	equ	85			; call code for file open/create
SYS_time	equ	201			; call code for get time

; -----
;  Globals (used by threads)

currentIndex	dq	0
myLock		dq	0
BLOCK_SIZE	dq	1000

; -----
;  Local variables for thread function(s).

msgThread1	db	" ...Thread starting...", LF, NULL

; -----
;  Local variables for getUserArgs function

LIMITMIN	equ	1000
LIMITMAX	equ	4000000000

errUsage	db	"Usgae: ./narCounter -t <1|2|3|4|5|6> ",
		db	"-l <septNumber>", LF, NULL
errOptions	db	"Error, invalid command line options."
		db	LF, NULL
errLSpec	db	"Error, invalid limit specifier."
		db	LF, NULL
errLValue	db	"Error, limit out of range."
		db	LF, NULL
errTSpec	db	"Error, invalid thread count specifier."
		db	LF, NULL
errTValue	db	"Error, thread count out of range."
		db	LF, NULL
		
; -----
;  Local variables for sept2int function

qSeven		dq	7
tmpNum		dq	0

; ***************************************************************

section	.text

; ******************************************************************
;  Thread function, numberTypeCounter()
;	Detemrine if narcissisticCount for all numbers between
;	1 and userLimit (gloabally available)

; -----
;  Arguments:
;	N/A (global variable accessed)
;  Returns:
;	N/A (global variable accessed)

common	userLimit	1:8
common	narcissisticCount	1:8
common	narcissisticNumbers	100:8

global narcissisticNumberCounter
narcissisticNumberCounter:

push rbp
mov rbp, rsp

push r12
push r13

mov r12, 0
mov r13, qword[userLimit] ;User inputted limit

;Print thread starting message
mov rdi, msgThread1
call printString

;while(true) loop




pop r13
pop r12

mov rsp, rbp
pop rbp

ret



; ******************************************************************
;  Mutex lock
;	checks lock (shared gloabl variable)
;		if unlocked, sets lock
;		if locked, lops to recheck until lock is free

global	spinLock
spinLock:
	mov	rax, 1			; Set the EAX register to 1.

lock	xchg	rax, qword [myLock]	; Atomically swap the RAX register with
					;  the lock variable.
					; This will always store 1 to the lock, leaving
					;  the previous value in the RAX register.

	test	rax, rax	        ; Test RAX with itself. Among other things, this will
					;  set the processor's Zero Flag if RAX is 0.
					; If RAX is 0, then the lock was unlocked and
					;  we just locked it.
					; Otherwise, RAX is 1 and we didn't acquire the lock.

	jnz	spinLock		; Jump back to the MOV instruction if the Zero Flag is
					;  not set; the lock was previously locked, and so
					; we need to spin until it becomes unlocked.
	ret

; ******************************************************************
;  Mutex unlock
;	unlock the lock (shared global variable)

global	spinUnlock
spinUnlock:
	mov	rax, 0			; Set the RAX register to 0.

	xchg	rax, qword [myLock]	; Atomically swap the RAX register with
					;  the lock variable.
	ret

; ******************************************************************
;  Function getUserArgs()
;	Get, check, convert, verify range, and return the
;	sequential/parallel option and the limit.

;  Example HLL call:
;	stat = getUserArgs(argc, argv, &parFlag, &numberLimit)

;  This routine performs all error checking, conversion of ASCII/septenary
;  to integer, verifies legal range.
;  For errors, applicable message is displayed and FALSE is returned.
;  For good data, all values are returned via addresses with TRUE returned.

;  Command line format (fixed order):
;	-t <1|2|3|4|5|6> -l <septNumber>

; -----
;  Arguments:
;	1) ARGC, value -rdi
;	2) ARGV, address -rsi
;	3) thread count (dword), address - rdx
;	4) user limit (qword), address - rcx

global getUserArgs
getUserArgs:

push rbp
mov rbp, rsp

push r12
push r13

mov r12, rdi	;Store arg count
mov r13, rsi	;Store arg values

;Check valid amount of arguments
cmp r12, 1
je errorUsage

cmp r12, 5
jb errorArgCount
ja errorArgCount

;Check thread specifier
mov r10, qword[r13+1*8]
cmp byte[r10+0], '-'
jne errorThreadSpec
cmp byte[r10+1], 't'
jne errorThreadSpec
cmp byte[r10+2], NULL
jne errorThreadSpec

;Check thread count value
mov al, byte[r13+2*8]
sub al, 0x30			;Convert string to int

cmp al, 6
ja errorThreadCount
cmp al, 0
jbe errorThreadCount

mov dword[rdx], eax

;Check limit specifier
mov r10, qword[r13+3*8]		;Get specifer string
cmp byte[r10+0], '-'
jne errorLSpec
cmp byte[r10+1], 'l'
jne errorLSpec
cmp byte[r10+2], NULL
jne errorLSpec

;Check the number value

mov r10, qword[r13+4*8]

mov rdi, r10
call aSept2int

;return value in rsi
cmp qword[rsi], LIMITMIN
jb errorLSize
cmp qword[rsi], LIMITMAX
ja errorLSize

mov qword[rcx], rsi
mov rax, TRUE
jmp endRead

errorLSize:
	mov rdi, errLValue
	call printString
	mov rax, FALSE
	jmp endRead
	

errorLSpec:
	mov rdi, errLSpec
	call printString
	mov rax, FALSE
	jmp endRead

errorThreadCount:
	mov rdi, errTValue
	call printString
	mov rax, FALSE
	jmp endRead

errorThreadSpec:
	mov rdi, errTSpec
	call printString
	mov rax, FALSE
	jmp endRead

errorArgCount:
	mov rdi, errOptions
	call printString
	mov rax, FALSE
	jmp endRead

errorUsage:
	mov rdi, errUsage
	call printString
	mov rax, FALSE
	jmp endRead
	
endRead:

pop r13
pop r12

mov rsp, rbp
pop rbp

ret





; ******************************************************************
;  Function: Check and convert ASCII/septenary to integer.

;  Example HLL Call:
;	bool = aSept2int(septStr, &num);

;sept string - rdi
;num -rsi
;rax - bool

global aSept2int
aSept2int:

push rbp
mov rbp, rsp

push r12
push r13

mov rax, 0
mov r10, 0
mov rcx, 0

convertIntLoop:
	movsx r8, byte[rdi+r10]		;Get char to convert
	
	cmp r8, NULL
	je endIntConvert		;Check if end of string
	
	sub r8, 0x30			;Convert string to int
	mov qword[tmpNum], r8
	mul rcx
	add rax, qword[tmpNum]
	mov qword[rsi], rax
	
	inc r10
	jmp convertIntLoop
	
endIntConvert:
	mov qword[rsi], rax
	mov rax, TRUE

pop r13
pop r12

mov rsp, rbp
pop rbp

ret






; ******************************************************************
;  Generic function to display a string to the screen.
;  String must be NULL terminated.
;  Algorithm:
;	Count characters in string (excluding NULL)
;	Use syscall to output characters

;  Arguments:
;	1) address, string
;  Returns:
;	nothing

global	printString
printString:
	push	rbx

; -----
;  Count characters in string.

	mov	rbx, rdi			; str addr
	mov	rdx, 0
strCountLoop:
	cmp	byte [rbx], NULL
	je	strCountDone
	inc	rbx
	inc	rdx
	jmp	strCountLoop
strCountDone:

	cmp	rdx, 0
	je	prtDone

; -----
;  Call OS to output string.

	mov	rax, SYS_write			; system code for write()
	mov	rsi, rdi			; address of characters to write
	mov	rdi, STDOUT			; file descriptor for standard in
						; EDX=count to write, set above
	syscall					; system call

; -----
;  String printed, return to calling routine.

prtDone:
	pop	rbx
	ret

; ******************************************************************

