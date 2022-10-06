; *****************************************************************
;  Name: Stephaney Chang
;  NSHE ID: 2001508920
;  Section: 1002
;  Assignment: 9
;  Description: 

; -----------------------------------------------------------------------------
;  Write assembly language functions.

;  Function, shellSort(), sorts the numbers into ascending
;  order (small to large).  Uses the shell sort algorithm
;  modified to sort in ascending order.

;  Function lstSum() to return the sum of a list.

;  Function lstAverage() to return the average of a list.
;  Must call the lstSum() function.

;  Fucntion basicStats() finds the minimum, median, and maximum,
;  sum, and average for a list of numbers.
;  The median is determined after the list is sorted.
;  Must call the lstSum() and lstAverage() functions.

;  Function linearRegression() computes the linear regression.
;  for the two data sets.  Must call the lstAverage() function.

;  Function readSeptNum() should read a septenary number
;  from the user (STDIN) and perform apprpriate error checking.


; ******************************************************************************

section	.data

; -----
;  Define standard constants.

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
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  Define program specific constants.

SUCCESS 	equ	0
NOSUCCESS	equ	1
OUTOFRANGEMIN	equ	2
OUTOFRANGEMAX	equ	3
INPUTOVERFLOW	equ	4
ENDOFINPUT	equ	5

LIMIT		equ	1510

MIN		equ	-100000
MAX		equ	100000

BUFFSIZE	equ	50			; 50 chars including NULL

; -----
;  NO static local variables allowed...


; ******************************************************************************

section	.text

; -----------------------------------------------------------------------------
;  Read an ASCII septenary number from the user.

;  Return codes:
;	SUCCESS			Successful conversion
;	NOSUCCESS		Invalid input entered
;	OUTOFRANGEMIN		Input below minimum value
;	OUTOFRANGEMAX		Input above maximum value
;	INPUTOVERFLOW		User entry character count exceeds maximum length
;	ENDOFINPUT		End of the input

; -----
;  Call:
;	status = readSeptNum(&numberRead);

;  Arguments Passed:
;	1) numberRead, addr - rdi

;  Returns:
;	number read (via reference)
;	status code (as above)


;	YOUR CODE GOES HERE


; -----------------------------------------------------------------------------
;  Shell sort function.

; -----
;  HLL Call:
;	call shellSort(list, len)

;  Arguments Passed:
;	1) list, addr
;	2) length, value

;  Returns:
;	sorted list (list passed by reference)

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
			jge endFirstForLoop
			
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


; -----------------------------------------------------------------------------
;  Find basic statistical information for a list of integers:
;	minimum, median, maximum, sum, and average

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  This function must call the lstSum() and lstAvergae() functions
;  to get the corresponding values.

;  Note, assumes the list is already sorted.

; -----
;  HLL Call:
;	call basicStats(list, len, min, med, max, sum, ave)

;  Returns:
;	minimum, median, maximum, sum, and average
;	via pass-by-reference (addresses on stack)

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


; -----------------------------------------------------------------------------
;  Function to calculate the sum of a list.

; -----
;  Call:
;	ans = lstSum(lst, len)

;  Arguments Passed:
;	1) list, address
;	2) length, value

;  Returns:
;	sum (in eax)

push rbp
mov rbp, rsp

mov rbx, 0
mov qword[length], rsi
sub qword[length], 1
mov eax, 0

calculateSumLoop:
	add eax, dword[rdi+rbx*4]		;add lst[i] to sum
	cmp rbx, qword[length]			;check end of list
	je endCalculateSumLoop
	inc rbx					;i++
	jmp calculateSumLoop
	
endCalculateSumLoop:	

pop rbp



; -----------------------------------------------------------------------------
;  Function to calculate the average of a list.
;  Note, must call the lstSum() fucntion.

; -----
;  Call:
;	ans = lstAve(lst, len)

;  Arguments Passed:
;	1) list, address
;	2) length, value

;  Returns:
;	average (in eax)



push rbp
mov rbp, rsp
push r12

mov r12, rsi

call lstSum		;Gets sum in eax

cdq
mov edx, 0
idiv r12d		;sum/length

pop r12
pop rbp


; -----------------------------------------------------------------------------
;  Function to calculate the linear regression
;  between two lists (of equal size).

; -----
;  Call:
;	linearRegression(xList, yList, len, xAve, yAve, b0, b1)

;  Arguments Passed:
;	1) xList, address
;	2) yList, address
;	3) length, value
;	4) xList average, value
;	5) yList average, value
;	6) b0, address
;	7) b1, address

;  Returns:
;	b0 and b1 via reference



push rbp
mov rbp, rsp
push r12
push r13
push r14
push r15

mov r14, qword[rbp+16]

mov r12, 0
mov r15, rdx
dec r15

mov qword[qSum], 0
mov dword[dSum], 0

;calculate the linear regression - b1 first
multiplyLoop:
	;get (x[i]-xavg) * (y[i]-yavg)
	movsxd r13, dword[rdi+r12*4]
	sub r13, rcx				;x[i] - xavg
	
	movsxd rax, dword[rsi+r12*4]		;get y[i]
	sub rax, r8				;y[i] - avg y
	
	;(x[i]*xavg) * (y[i]*yavg)
	imul r13
	add qword[qSum], rax		
	
	cmp r12, r15				;check end of list
	je endMultiplyLoop
	
	inc r12					;i++
	jmp multiplyLoop
	
endMultiplyLoop:

mov r12, 0

squareLoop:	
	mov r13d, dword[rdi+r12*4]
	sub r13d, ecx				;x[i] - xavg
	
	;(x[i]-xavg)^2
	mov eax, r13d
	imul eax
	
	add dword[dSum], eax			;add to the sum
	
	cmp r12, r15				;check end of list
	je endSquareLoop
	
	inc r12					;i++
	jmp squareLoop
	
endSquareLoop:

;(x[i]*xavg) * (y[i]*yavg) / (x[i]-xavg)^2
cdq
mov eax, dword[qSum]
mov edx, dword[qSum+4]
idiv dword[dSum]
	
mov dword[r14], eax

mov ebx, r8d
imul ecx
sub ebx, eax

mov dword[r9], ebx

pop r15
pop r14
pop r13
pop r12
pop rbp



; -----------------------------------------------------------------------------
