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



;SHELL SORT

mov dword[h], 1		;h = 1
mov r13, rsi

;while(h*3+1) < length
hLoop:
	;h*3+1
	mov eax, dword[h]
	mov ebx, 3
	mul ebx
	add eax, 1
	
	mov dword[h], eax
	
	cmp dword[h], r13d	;Compare if h*3+1 < length
	jg endHLoop		;endHLoop if it is bigger
	
endHLoop:

;Clear registers
mov eax, 0
mov ebx, 0
sub r13d, 2

;Shell sort

whileLoop:
	;set up i = h-1
	mov eax, dword[h]
	sub eax, 1			;h-1
	mov dword[i], eax		;i=h-1
	
	;while h>0
	cmp dword[h], 0
	ja firstForLoop			;h is above 0
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
			jb endFirstForLoop	;jump to the outer for loop
			
			cmp r14d, dword[tmp]		;lst[j-h] > tmp
			jbe endFirstForLoop
			
			;j = j-h
			mov dword[j], r11d
			
			jmp secondForLoop

	endFirstForLoop:
		;Do all condition comparisons
		;for(i=h-1, i<length, i++)
		
		movsxd r15, dword[j]
		mov r13d, dword[tmp]
		mov dword[rdi+r15*4], r13d	;lst[j] = tmp

		cmp dword[i], r13d
		ja endWhileLoop
		
		inc dword[i]
		jmp firstForLoop

endWhileLoop:
	mov edx, 0
	mov eax, dword[h]
	mov ebx, 3
	div ebx
	mov dword[h], eax
	jmp whileLoop
	
endSort:



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


;	YOUR CODE GOES HERE



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


	ret

; ********************************************************************************

