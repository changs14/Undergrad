; *****************************************************************
;  Name: Stephaney Chang
;  NSHE ID: 2001508920
;  Section: 1002
;  Assignment: 7
;  Description:	Sort a list of number using the shell sort
;		algorithm.  Also finds the minimum, median, 
;		maximum, and average of the list.

; -----
; Shell Sort

;	h = 1;
;       while ( (h*3+1) < a.length) {
;	    h = 3 * h + 1;
;	}

;       while( h > 0 ) {
;           for (i = h-1; i < a.length; i++) {
;               tmp = a[i];
;               j = i;
;               for( j = i; (j >= h) && (a[j-h] > B); j -= h) {
;                   a[j] = a[j-h];
;               }
;               a[j] = tmp;
;           }
;           h = h / 3;
;       }

; =====================================================================
;  Macro to convert integer to septenary value in ASCII format.
;  Reads <integer>, converts to ASCII/septenary string including
;	NULL into <string>

;  Note, the macro is calling using RSI, so the macro itself should
;	 NOT use the RSI register until is saved elsewhere.

;  Arguments:
;	%1 -> <integer>, value
;	%2 -> <string>, string address

;  Macro usgae
;	int2aSept	<integer-value>, <string-address>

;  Example usage:
;	int2aSept	dword [diamsArrays+rsi*4], tempString

;  For example, to get value into a local register:
;		mov	eax, %1

%macro	int2aSept	2


;%1 Number to convert
;%2 Converted number

mov r9, 1
mov eax, %1			;Get the number that will be converted
mov ebx, %1

%%convertToStringLoop:
	mov edx, 0
	mov ecx, 7
	div ecx		;eax/7
	
	cmp eax, 0		;Check if number can no longer be / 7
	je %%checkSign	

	add edx, "0"
	mov byte[%2+r9], dl

	inc r9
	jmp %%convertToStringLoop
	
%%checkSign:
	add edx, "0"
	mov byte[%2+r9], dl
	inc r9
	
	mov byte[%2+r9], '+'
	inc r9
	jmp %%addSpace
	
%%addSpace:
	mov byte[%2+r9], 0x20
	
	cmp r9, 12
	je %%endConversion
	
	inc r9
	jmp %%addSpace

%%endConversion:

mov r8, 0
mov r9, 0
mov r10, 11

%%reverseLoop:
	mov al, byte[%2+r8]
	mov bl, byte[%2+r10]
	
	mov byte[%2+r8], bl
	mov byte[%2+r10], al
	
	cmp r9, 5
	je %%endReverse
	inc r8
	inc r9
	dec r10
	jmp %%reverseLoop

%%endReverse:
	mov byte[%2+11], NULL


%endmacro


; =====================================================================
;  Simple macro to display a string to the console.
;  Count characters (excluding NULL).
;  Display string starting at address <stringAddr>

;  Macro usage:
;	printString  <stringAddr>

;  Arguments:
;	%1 -> <stringAddr>, string address

%macro	printString	1
	push	rax			; save altered registers (cautionary)
	push	rdi
	push	rsi
	push	rdx
	push	rcx

	lea	rdi, [%1]		; get address
	mov	rdx, 0			; character count
%%countLoop:
	cmp	byte [rdi], NULL
	je	%%countLoopDone
	inc	rdi
	inc	rdx
	jmp	%%countLoop
%%countLoopDone:

	mov	rax, SYS_write		; system call for write (SYS_write)
	mov	rdi, STDOUT		; standard output
	lea	rsi, [%1]		; address of the string
	syscall				; call the kernel

	pop	rcx			; restore registers to original values
	pop	rdx
	pop	rsi
	pop	rdi
	pop	rax
%endmacro

; =====================================================================
;  Data Declarations.

section	.data

; -----
;  Define constants.

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
;  Provided data

lst	dd	1113, 1232, 2146, 1376, 5120, 2356,  164, 4565, 155, 3157
	dd	 759, 326,  171,  147, 5628, 7527, 7569,  177, 6785, 3514
	dd	1001,  128, 1133, 1105,  327,  101,  115, 1108,    1,  115
	dd	1227, 1226, 5129,  117,  107,  105,  109,  999,  150,  414
	dd	 107, 6103,  245, 6440, 1465, 2311,  254, 4528, 1913, 6722
	dd	1149,  126, 5671, 4647,  628,  327, 2390,  177, 8275,  614
	dd	3121,  415,  615,  122, 7217,    1,  410, 1129,  812, 2134
	dd	 221, 2234,  151,  432,  114, 1629,  114,  522, 2413,  131
	dd	5639,  126, 1162,  441,  127,  877,  199,  679, 1101, 3414
	dd	2101,  133, 1133, 2450,  532, 8619,  115, 1618, 9999,  115
	dd	 219, 3116,  612,  217,  127, 6787, 4569,  679,  675, 4314
	dd	1104,  825, 1184, 2143, 1176,  134, 4626,  100, 4566,  346
	dd	1214, 6786,  617,  183,  512, 7881, 8320, 3467,  559, 1190
	dd	 103,  112,    1, 2186,  191,   86,  134, 1125, 5675,  476
	dd	5527, 1344, 1130, 2172,  224, 7525,  100,    1,  100, 1134   
	dd	 181,  155, 1145,  132,  167,  185,  150,  149,  182,  434
	dd	 581,  625, 6315,    1,  617,  855, 6737,  129, 4512,    1
	dd	 177,  164,  160, 1172,  184,  175,  166, 6762,  158, 4572
	dd	6561,  283, 1133, 1150,  135, 5631, 8185,  178, 1197,  185
	dd	 649, 6366, 1162,  167,  167,  177,  169, 1177,  175, 1169

len	dd	200

min	dd	0
med	dd	0
max	dd	0
sum	dd	0
avg	dd	0


; -----
;  Misc. data definitions (if any).

h		dd	0
i		dd	0
j		dd	0
tmp		dd	0

tmp2		dd	0
; -----
;  Provided string definitions.

STR_LENGTH	equ	12			; chars in string, with NULL

newLine		db	LF, NULL

hdr		db	"---------------------------"
		db	"---------------------------"
		db	LF, ESC, "[1m", "CS 218 - Assignment #7", ESC, "[0m"
		db	LF, "Shell Sort", LF, LF, NULL

hdrMin		db	"Minimum:  ", NULL
hdrMed		db	"Median:   ", NULL
hdrMax		db	"Maximum:  ", NULL
hdrSum		db	"Sum:      ", NULL
hdrAve		db	"Average:  ", NULL

; ---------------------------------------------

section .bss

tmpString	resb	STR_LENGTH

; ---------------------------------------------

section	.text
global	_start
_start:

; ******************************
;  Shell Sort.
;  Find sum and compute the average.
;  Get/save min and max.
;  Find median.


;SHELL SORT

mov dword[h], 1		;h = 1

;while(h*3+1) < length
hLoop:
	;h*3+1
	mov eax, dword[h]
	mov ebx, 3
	mul ebx
	add eax, 1
	
	mov dword[h], eax
	
	cmp dword[h], 200	;Compare if h*3+1 < length
	jg endHLoop		;endHLoop if it is bigger
	
endHLoop:

;Clear registers
mov eax, 0
mov ebx, 0

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
		
		mov r9d, dword[lst+r8*4]	;get lst[i]
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
			mov r14d, dword[lst+r11*4]	;lst[j-h]
			mov dword[lst+r10*4], r14d	;lst[j] = lst[j-h]
			
			
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
		mov dword[lst+r15*4], r13d	;lst[j] = tmp

		cmp dword[i], 198
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


;Calculate the sum
mov rsi, 0

calculateSumLoop:
	mov eax, dword[lst+rsi*4]	;Get diameter in the list
	add dword[sum], eax		;Add to the sum
	cmp rsi, 199
	je endCalculateSumLoop
	inc rsi				;i++
	jmp calculateSumLoop		;loop back


endCalculateSumLoop:
	;Sum has been calculated

;Calculate the average
mov eax, dword[sum]			;Get the sum
mov edx, 0
div dword[len]				;sum/length
mov dword[avg], eax			;Store average in var

;Reset counters
mov rsi, 0

mov eax, dword[lst]
mov dword[min], eax

minimumLoop:
	mov eax, dword[lst+rsi*4] ;Get diameter
	cmp dword[min], eax		 ;Compare current min to array item
	jle notMinimum			 ;Curr num is not smaller than min
	mov dword[min], eax		 ;Current number is new min
	cmp rsi, 200
	je endMin
	inc rsi				 ;i++
	jmp minimumLoop

notMinimum:
	cmp rsi, 200
	je endMin
	inc rsi				 ;i++
	jmp minimumLoop

endMin:	
movsxd rcx, dword[len]			;Get the length of the list
mov rsi, 0				;Reset counter

maxLoop:
	mov eax, dword[lst+rsi*4]	;Get item in list
	cmp dword[max], eax		;Check if item is larger than max
	jge notMax			;Current number is not larger
	mov dword[max], eax		;Current item is new max
	cmp rsi, rcx			;Check if end of list
	je endLoop			;End of list
	inc rsi				;i++
	jmp maxLoop
	
notMax:
	cmp rsi, rcx			;Check if end of list
	je endLoop			;End of list
	inc rsi				;i++
	jmp maxLoop

endLoop:
	;Max has been found
	
;Find the medians
mov edx, 0
mov eax, dword[lst+99*4]
add eax, dword[lst+100*4]
mov ecx, 2
div ecx
mov dword[med], eax

; ******************************
;  Display results to screen in septenary.

	printString	hdr

	printString	hdrMin
	int2aSept	dword [min], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrMed
	int2aSept	dword [med], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrMax
	int2aSept	dword [max], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrSum
	int2aSept	dword [sum], tmpString
	printString	tmpString
	printString	newLine

	printString	hdrAve
	int2aSept	dword [avg], tmpString
	printString	tmpString
	printString	newLine
	printString	newLine

; ******************************
;  Done, terminate program.

last:
	mov	rax, SYS_exit
	mov	rdi, EXIT_SUCCESS
	syscall

