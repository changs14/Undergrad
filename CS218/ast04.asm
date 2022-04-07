;  Name: Stephaney Chang
;  NSHE ID: 2001508920	
;  Section: 1003
;  Assignment: 4
;  Description: This program will take a list of signed numbers and calculate the minimum
;               median, maximum, sum, and average of said list.
;               It will alsot take the sum, count, and average of numbers in the list divisible by 6.

section .data

NULL		equ	0			; end of string
TRUE		equ	1
FALSE		equ	0
EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

lst		dd	 4224, -1116,  1542,  1240,  1677
		dd	-1635,  2420,  1820,  1246,  -333 
		dd	 2315,  -215,  2726,  1140,  2565
		dd	 2871,  1614,  2418,  2513,  1422 
		dd	 -119,  1215, -1525,  -712,  1441
		dd	-3622,  -731, -1729,  1615,  2724 
		dd	 1217,  -224,  1580,  1147,  2324
		dd	 1425,  1816,  1262, -2718,  1192 
		dd	-1435,   235,  2764, -1615,  1310
		dd	 1765,  1954,  -967,  1515,  1556 
		dd	 1342,  7321,  1556,  2727,  1227
		dd	-1927,  1382,  1465,  3955,  1435 
		dd	 -225, -2419, -2534, -1345,  2467
		dd	 1615,  1959,  1335,  2856,  2553 
		dd	-1035,  1833,  1464,  1915, -1810
		dd	 1465,  1554,  -267,  1615,  1656 
		dd	 2192,  -825,  1925,  2312,  1725
		dd	-2517,  1498,  -677,  1475,  2034 
		dd	 1223,  1883, -1173,  1350,  2415
		dd	 -335,  1125,  1118,  1713,  3025
length		dd	100
six		dd	6
four 	dd  4

;Total numbers in the list
lstMin		dd	0
estMed		dd	0
lstMax		dd	0
lstSum		dd	0
lstAve		dd	0

;Number of negative numbers in the list
negCnt		dd	0
negSum		dd	0
negAve		dd	0

;Number of numbers divisble by 6
sixCnt		dd	0
sixSum		dd	0
sixAve		dd	0

section .text

;Program start
global _start
_start:

mov ecx, dword[length]
mov rsi, 0

;Find the sum of list
sumLoop:
	mov eax, dword[lst+(rsi*4)]		;Get current index
	add dword[lstSum], eax			;Add to the sum
	cmp rsi, 100					;Check if end of list
	je endSum						;End of the list
	inc rsi
	loop sumLoop
	
endSum:

mov rsi, 0
findMin:
	mov eax, dword[lst+(rsi*4)]		;Get current index
	cmp dword[lstMin], eax			;Compare current value to current min
	jge isMinimum					;eax<lstMin
	
	cmp rsi, 100					;Check if end of list
	je endFindMin					
	inc rsi
	loop findMin
	
isMinimum:
	mov dword[lstMin], eax			;Assign new min
	cmp rsi, 100					;Check if end of list
	je endFindMin					
	inc rsi
	loop findMin

endFindMin:

mov rsi, 0
findMax:
	mov eax, dword[lst+(rsi*4)]		;Get current index
	cmp dword[lstMax], eax			;Compare current val to current max
	jle isMaximum					;eax>lstMax
	
	cmp rsi, 100					;Check if end of list
	je endFindMax					
	inc rsi
	loop findMax

isMaximum:
	mov dword[lstMax], eax			;Assign new max
	cmp rsi, 100					;Check if end of list
	je endFindMax					
	inc rsi
	loop findMax
	
endFindMax:

;Calculate the median of list
;Index 49 and Index 50 then find average between the two

mov eax, dword[lst+0]			;Index 0
add eax, dword[lst+196]			;Index 49
add eax, dword[lst+200] 		;Index50
add eax, dword[lst+396]		;Index 99
idiv dword[four]							;Divide two sums by 4
mov dword[estMed], eax				;Store median value

;Calculate the average of list
mov eax, dword[lstSum]
mov edx, 0
idiv dword[length]					;Divide the sum by num of values
mov dword[lstAve], eax				;Store in lstAve
    
;Find the number of negatives in list
mov rsi, 0
findNegativeLoop:
	mov eax, dword[lst+rsi*4]		;Get current index
	cmp eax, 0						;Check if below 0
	jle isNegative					;Is below 0
	jae notNegative					;Is not below 0
	
isNegative:
	add dword[negCnt], 1		;Increment number of negatives
	add dword[negSum], eax		;Add to the sum
		
	cmp rsi, 100				;Check if end of list
	je loopEnd					
	
	inc rsi
	loop findNegativeLoop
			
notNegative:
	cmp rsi, 100				;Check if end of list
	je loopEnd
		
	inc rsi
	loop findNegativeLoop
	
loopEnd:

;Calculate the average of all negatives in the list
mov eax, dword[negSum] 
mov edx, 0
cdq
idiv dword[negCnt]               ;Divide sum of negs by count
mov dword[negAve], eax          ;Store value in negAve

;Find the number of numbers divisible by 6
mov rsi, 0
findSixLoop:
	mov eax, dword[lst + (rsi* 4)]	;Get current value
	mov edx, 0
	idiv dword[six]					;Divide curr value by 6
	cmp edx, 0						;Check if there is remainder
	je sixFound						;No remainder, divisible by 6

	cmp rsi, 100
	je endSix
	inc rsi
	loop findSixLoop
    
sixFound:
	add dword[sixCnt], 1		;Increment count
	mov eax, dword[lst+(rsi*4)]
	add dword[sixSum], eax      ;Add current number to the sum
	cmp rsi, 100				;Check if end of list
	je endSix
	inc rsi
	loop findSixLoop
	    
endSix:
    
;Find the average of numbers divisible by 6
mov eax, dword[sixSum]
mov edx, 0
idiv dword[sixCnt]              ;Divide sum by number of values
mov dword[sixAve], eax          ;Store average in sixAve

;Program end
last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall
