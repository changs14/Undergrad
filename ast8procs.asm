; *****************************************************************
;  Name: Stephaney Chang
;  NSHE ID: 20011508920
;  Section: 1002
;  Assignment: 8
;  Description:


; -----------------------------------------------------------------
;  Write some assembly language functions.

;  The function, shellSort(), sorts the numbers into descending
;  order (large to small).  Uses the shell sort algorithm from
;  assignment #7 (modified to sort in descending order).

;  The function, basicStats(), finds the minimum, median, and maximum,
;  sum, and average for a list of numbers.
;  Note, the median is determined after the list is sorted.
;	This function must call the lstSum() and lstAvergae()
;	functions to get the corresponding values.
;	The lstAvergae() function must call the lstSum() function.

;  The function, linearRegression(), computes the linear regression of
;  the two data sets.  Summation and division performed as integer.

; *****************************************************************

section	.data

; -----
;  Define constants.

TRUE		equ	1
FALSE		equ	0

; -----
;  Local variables for shellSort() function (if any).

h		dd	0
i		dd	0
j		dd	0
tmp		dd	0

tmp2		dd	0

; -----
;  Local variables for basicStats() function (if any).

length dq 0
; -----------------------------------------------------------------

section	.bss

; -----
;  Local variables for linearRegression() function (if any).

qSum		resq	1
dSum		resd	1


; *****************************************************************

section	.text

; --------------------------------------------------------
;  Shell sort function (form asst #7).
;	Updated to sort in descending order.

; -----
;  HLL Call:
;	call shellSort(list, len)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi

;  Returns:
;	sorted list (list passed by reference)

global	shellSort
shellSort:

push rbp
mov rbp, rsp
push r11
push r12
push r13
push r14
push r15

;SHELL SORT

mov dword[i], 0
mov dword[tmp], 0
mov dword[j], 0

mov dword[h], 1		;h = 1
mov rcx, rsi

;while(h*3+1) < length
hLoop:
	;h*3+1
	mov eax, dword[h]
	mov ebx, 3
	imul ebx
	add eax, 1
	
	mov dword[h], eax
	
	cmp dword[h], ecx	;Compare if h*3+1 < length
	jg endHLoop		;endHLoop if it is bigger
	
endHLoop:

;Clear registers
mov eax, 0
mov ebx, 0
sub ecx, 2

;Shell sort

whileLoop:
	;set up i = h-1
	mov eax, dword[h]
	sub eax, 1			;h-1
	mov dword[i], eax		;i=h-1
	
	;while h>0
	cmp dword[h], 0
	jg firstForLoop			;h is above 0
	jmp endSort			;h is below 0
	
	firstForLoop:	
		mov r8d, dword[i]
		mov dword[j], r8d		;j=i
		mov dword[tmp2], r8d
		movsxd r8, dword[tmp2]
		
		mov r9d, dword[rdi+r8*4]	;get lst[i]
		mov dword[tmp], r9d		;tmp = lst[i]
		
		jmp secondForLoop
		
		secondForLoop:
			;r10d = j
			mov r10d, dword[j]
			mov dword[tmp2], r10d
			movsxd r10, dword[tmp2]
			
			;r11d = j-h
			mov r11d, dword[j]
			sub r11d, dword[h]
			mov dword[tmp2], r11d
			movsxd r11, dword[tmp2]
			
			;lst[j] = lst[j-h]
			mov r14d, dword[rdi+r11*4]	;lst[j-h]
			mov dword[rdi+r10*4], r14d	;lst[j] = lst[j-h]
			
			
			;Do all the comparisons
			
			mov r12d, dword[h]	;r12d = h
			cmp dword[j], r12d	;j>=h
			jl endFirstForLoop	;jump to the outer for loop
			
			cmp r14d, dword[tmp]		;lst[j-h] > tmp
			jle endFirstForLoop
			
			;j = j-h
			mov dword[j], r11d
			
			jmp secondForLoop

	endFirstForLoop:
		;Do all condition comparisons
		;for(i=h-1, i<length, i++)
		
		movsxd r15, dword[j]
		mov r13d, dword[tmp]
		mov dword[rdi+r15*4], r13d	;lst[j] = tmp

		cmp dword[i], ecx
		jg endWhileLoop
		
		inc dword[i]
		jmp firstForLoop

endWhileLoop:
	mov edx, 0
	mov eax, dword[h]
	mov ebx, 3
	idiv ebx
	mov dword[h], eax
	jmp whileLoop
	
endSort:

pop r15
pop r14
pop r13
pop r12
pop r11
pop rbp

	ret

; --------------------------------------------------------
;  Find basic statistical information for a list of integers:
;	minimum, median, maximum, sum, and average

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  This function must call the lstSum() and lstAvergae() functions
;  to get the corresponding values.

;  Note, assumes the list is already sorted.

; -----
;  Call:
;	call basicStats(list, len, min, med, max, sum, ave)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi
;	3) minimum, addr - rdx
;	4) median, addr - rcx
;	5) maximum, addr - r8
;	6) sum, addr - r9
;	7) ave, addr - stack, rbp+16

;  Returns:
;	minimum, median, maximum, sum, and average
;	via pass-by-reference (addresses on stack)

global basicStats
basicStats:


;	YOUR CODE GOES HERE

push rbp
mov rbp, rsp
push r12
push r13

;Get min and max
;min - end of list	max - start of list

mov eax, dword[rdi] 		;Get first item in the list
mov dword[r8], eax		;Store maximum

mov r12, rsi			;Get the length
sub r12, 1

mov r13d, dword[rdi+r12*4]	;Get last item in the list
mov dword[rdx], r13d		;Store minimum

;Find median of the list
mov rax, rsi
mov rdx, 0
mov r12, 2
idiv r12

cmp rdx, 0
je evenLength

mov r12d, dword[rdi+rax*4]
mov dword[rcx], r12d

jmp medianFound

evenLength:
	mov rdx, 0
	mov r12d, dword[rdi+rax*4]	;Get list[i]
	dec rax
	add r12d, dword[rdi+rax*4]	;Add list[i-1]
	mov eax, r12d
	mov ebx, 2
	idiv ebx
	mov dword[rcx], eax		;Store median
	
medianFound:

;Find the sum - call lstSum
;rdi and rsi already established
call lstSum
mov dword[r9], eax

;Find the average - call lstAverage
mov r13, qword[rbp+16]
call lstAve
mov dword[r13], eax

pop r13
pop r12
pop rbp

	ret

; --------------------------------------------------------
;  Function to calculate the sum of a list.

; -----
;  Call:
;	ans = lstSum(lst, len)

;  Arguments Passed:
;	1) list, address - rdi
;	1) length, value - rsi

;  Returns:
;	sum (in eax)


global	lstSum
lstSum:

push rbp
mov rbp, rsp

mov rbx, 0
mov qword[length], rsi
sub qword[length], 1
mov eax, 0

calculateSumLoop:
	add eax, dword[rdi+rbx*4]
	cmp rbx, qword[length]
	je endCalculateSumLoop
	inc rbx
	jmp calculateSumLoop
	
endCalculateSumLoop:	

pop rbp


	ret

; --------------------------------------------------------
;  Function to calculate the average of a list.
;  Note, must call the lstSum() fucntion.

; -----
;  Call:
;	ans = lstAve(lst, len)

;  Arguments Passed:
;	1) list, address - rdi
;	1) length, value - rsi

;  Returns:
;	average (in eax)


global	lstAve
lstAve:

;	YOUR CODE GOES HERE

push rbp
mov rbp, rsp
push r12

mov r12, rsi

call lstSum		;Gets sum in eax

cdq
mov edx, 0
idiv r12d

pop r12
pop rbp

	ret

; --------------------------------------------------------
;  Function to calculate the linear regression
;  between two lists (of equal size).
;  Due to the data sizes, the summation for the dividend (top)
;  MUST be performed as a quad-word.

; -----
;  Call:
;	linearRegression(xList, yList, len, xAve, yAve, b0, b1)

;  Arguments Passed:
;	1) xList, address - rdi
;	2) yList, address - rsi
;	3) length, value - edx
;	4) xList average, value - ecx
;	5) yList average, value - r8d
;	6) b0, address - r9
;	7) b1, address - stack, rpb+16

;  Returns:
;	b0 and b1 via reference

global linearRegression
linearRegression:


;	YOUR CODE GOES HERE

push rbp
mov rbp, rsp
push r12

pop r12
pop rsp

	ret

; ********************************************************************************

