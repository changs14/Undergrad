; *****************************************************************
;  Name: Stephaney Chang
;  NSHE ID: 2001508920
;  Section: 1004
;  Assignment: 8
;  Description: This program has four functions that will use an array
;		 of numbers and a length. It will bubble sort the list of
;		 number and the the stats, min/max/median as well as
;		 numbers divisble by 2 and 5. THen it will find
;		 variance and standard deviation

; --------------------------------------------------------------------
;  Write assembly language functions.

;  The function, bubbleSort(), sorts the numbers into descending
;  order (large to small).  Uses the bubble sort algorithm from
;  assignment #7 (modified to sort in descending order).

;  The function, simpleStats(), finds the minimum, median, and maximum
;  count of even values, and count of values evenly divisible by 5
;  for a list of numbers.

;  The function, iAvergae(), computes the integer average for a
;  list of numbers.

;  The function, lstStats(), to compute the variance and
;	standard deviation for a list of numbers.

;  Note, all data is signed!


; ********************************************************************************

section	.data

; -----
;  Define standard constants

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; system call code for read
SYS_write	equ	1			; system call code for write
SYS_open	equ	2			; system call code for file open
SYS_close	equ	3			; system call code for file close
SYS_fork	equ	57			; system call code for fork
SYS_exit	equ	60			; system call code for terminate
SYS_creat	equ	85			; system call code for file open/create
SYS_time	equ	201			; system call code for get time

LF		equ	10
NULL		equ	0
ESC		equ	27

; -----
;  Local variables for bubbleSort() function (if any)

swapped		db	FALSE


; -----
;  Local variables for simpleStats() function (if any)

tmp dd	0


; -----
;  Local variables for iAverage() function (if any)



; -----
;  Local variables for lstStats() function (if any)

tmpVar		dq	0
tmpVar2 dq	0


; ********************************************************************************

section	.text

; ********************************************************************
;  Function to implement bubble sort for an integer array.
;	Note, sorts in desending order

; -----
;  HLL Call:
;	bubbleSort(list, len)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi/esi?

;  Returns:
;	sorted list (list passed by reference)

global bubbleSort
bubbleSort:

	push rbp
	mov rbp, rsi
	push r12
	
	mov rax, rsi
	dec rax
	
	mov r12, rax					;i
	
iLoop:
	;cmp dword[swapped], FALSE
	;je endILoop
	
	mov rdx, rsi					;j
	dec rdx					;j-1
	cmp r12, 1					;i condition
	je endILoop					;end of loop
	
	jLoop:
		mov r10d, dword[rdi+rdx*4]		;Get index[i]
		cmp r10d, dword[rdi+rdx*4-4]		;Get index[i+1]
		jg swapPositions
				
		cmp rdx, 1				;Check j condition
		je iCondition				;Go back to iLoop
		dec rdx				;j--
		jmp jLoop
		
swapPositions:
	;Swap items
	mov r11d, dword[rdi+rdx*4-4]			;store j-1
	mov dword[rdi+rdx*4], r11d			;swap items
	mov dword[rdi+rdx*4-4], r10d
	mov byte[swapped],TRUE	
	
	cmp rdx, 1					;check j
	je iCondition					;end j loop
	dec rdx					;j--
	jmp jLoop	

iCondition:
	dec r12					;i--
	jmp iLoop					
		

endILoop:
	pop r12
	pop rbp
	ret



; ********************************************************************
;  Find simple statistical information of an integer array:
;	minimum, median, maximum, count of even values, and
;	count of values evenly divisible by 5

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  Note, you may assume the list is already sorted.

; -----
;  HLL Call:
;	simpleStats(list, len, min, max, med, evenCnt, fiveCnt)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - esi?
;	3) minimum, addr - rdx
;	4) maximum, addr - rcx
;	5) median, addr - r8
;	6) evenCnt, addr - r9
;	7) fiveCnt, addr - rbp+16

;  Returns:
;	minimum, median, maximum, evenCnt, fiveCnt
;	via pass-by-reference


global simpleStats
simpleStats:
	push rbp
	mov rbp, rsp
	push r12
	push r13
	
	;Get min and max
	mov eax, dword[rdi]		;Get first list item
	mov dword[rcx], eax		;Store maximum
	
	mov r12, rsi
	dec r12
	mov eax, dword[rdi+r12*4]	;Get last item in list
	mov dword[rdx], eax		;Store minimum

	;Find median
	mov rax, rsi
	mov rdx, 0
	mov r12, 2
	idiv r12			;Get middle of list
		
	cmp rdx, 0
	je evenLength
		
	mov r12d, dword[rdi+rax*4]	;Odd length so one middle numbers
	mov dword[r8], r12d		;Store median
	jmp endMedian

evenLength:
	mov rdx, 0
	mov r12d, dword[rdi+rax*4]	;Get list[i]
	dec rax
	add r12d, dword[rdi+rax*4]	;add with list[i-1]
	mov eax, r12d		
	mov ebx, 2
	idiv ebx
	mov dword[r8], eax		;Store median

endMedian:
	mov r12, 0
	mov rax, 0
	
;Find even numbers
dec rsi 

evenLoop:
	mov eax, dword[rdi+r12*4]	;Get list item
	cdq
	mov ebx, 2
	div ebx
	
	cmp edx, 0			;Check remainder
	je isEven
	
	cmp r12, rsi			;Check end of list
	je endEvenLoop
	inc r12			;i++
	jmp evenLoop

isEven:
	inc dword[r9]			;inc number of even numbers
	cmp r12, rsi			;Check end of list
	je endEvenLoop
	inc r12			;i++
	jmp evenLoop
	
endEvenLoop:
	mov r12, 0
	mov rax, 0

;Find numbers divisible by 5
mov r13, qword[rbp+16]			;Get list
mov ecx, 0

fiveLoop:
	mov eax, dword[rdi+r12*4]	;Get list[i]
	mov edx, 0
	mov ebx, 5
	div ebx
	
	cmp edx, 0			;Check remainder
	je isDivisible
	
	cmp r12, rsi			;Check end of list
	je endFiveLoop
	inc r12			;i++
	jmp fiveLoop

isDivisible:
	inc ecx			;inc fiveCount
	cmp r12, rsi			;Check end of list
	je endFiveLoop
	inc r12			;i++
	jmp fiveLoop
	
endFiveLoop:
	mov dword[r13], ecx		;Save fiveCount
	pop r13
	pop r12
	pop rbp

	ret





; ********************************************************************
;  Function to calculate the integer average of an integer array.

; -----
;  Call:
;	ave = iAverage(list, len)

;  Arguments Passed:
;	1) list, addr - 8 - rdi
;	2) length, value - 12 -esi

;  Returns:
;	integer average - value (in eax)


global iAverage
iAverage:
	push rbp
	mov rbp, rsp
	push r12
	
	mov r12, 0
	mov rax, 0
	
sumLoop:
	add eax, dword[rdi+r12*4]		;Add item to running sum
	inc r12				;Index++
	cmp r12, rsi
	jl sumLoop
	
;Calculate the average
cdq
idiv rsi					;sum/length

	pop r12
	pop rbp

	ret





; ********************************************************************
;  Function to calculate the variance and standard deviation
;  of an integer array.
;  Must use iAverage() function to find average.
;  Must use the stdDev() function to find the standard deviation.
;	Note, stdDev() is a real function, which returns values in xmm0.

;  Must use MOVSD to store result from XMM0 to a memory location.
;  For example:
;	movsd	qword [someVar], xmm0

; -----
;  Call:
;	lstStats(list, len, &var, &std)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi
;	3) variance, addr - rdx
;	4) standard deviation, addr - rcx

;  Returns:
;	variance - value (quad)


global lstStats
lstStats:
	push rbx
	push r12
	push r13
	push r14
	
	;Preserve arguments
	mov rbx, rdi		;list
	mov r12, rsi		;length
	mov r13, rdx		;variance
	mov r14, rcx		;standard div
	
	call iAverage		;stored in eax
	mov r11d, eax

	mov qword[tmpVar], 0
	mov rcx, r12
	mov r10, 0
	
varianceLoop:
	mov eax, dword[rdi+r10*4]		;Get lst[i]
	sub eax, r11d				;lst[i] - avg
	imul eax				;(lst[i] - avg) ^2
	
	add dword[tmpVar], eax			;add to temp variable
	adc dword[tmpVar+4], edx
	
	cmp r10, r12				;check if end of loop
	je endVariance
	inc r10				;i++
	loop varianceLoop

endVariance:	
	mov r10, qword[tmpVar]			;Store variance sum
	mov qword[r13], r10

mov rdi, qword[tmpVar]
mov rsi, r12
call stdDeviation
movsd qword[r14], xmm0
	
pop r14
pop r13
pop r12
pop rbp
ret





; ********************************************************************
;  Function to compute standard deviation as a real value.
;  Uses floating point instructions.
;  Returns result in xmm0

;  Algorithm:
;	std = sqrt(var/n)

; -----
;  HLL Call:
;	stdDev(var, len)

;  Arguments:
;	1) variance, value
;	2) length, value

;  Returns:
;	standard deviation in xmm0

global	stdDeviation
stdDeviation:

	; convert integers to floats
	cvtsi2sd	xmm0, rdi
	cvtsi2sd	xmm1, rsi

	divsd		xmm0, xmm1
	sqrtsd		xmm0, xmm0

	ret

; ********************************************************************

