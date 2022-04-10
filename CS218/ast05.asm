;Name: Stephaney Chang
;NSHE ID: 2001508920
;Section: 1003
;Assignment: 5
;Description: The program will take sides of a kite and calculate the area and perimeter.
;			  Sides p and q will be used to calculate the area and sides a and c will calculate the perimeter.
;			  Then the max, min, median, sum, and average will be calculated.

section	.data

; -----
;  Define constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; successful operation
SYS_exit	equ	60			; call code for terminate

; -----
;  Provided Data

aSides		db	   10,    14,    13,    37,    54
		db	   31,    13,    20,    61,    36
		db	   14,    53,    44,    19,    42
		db	   27,    41,    53,    62,    10
		db	   19,    28,    14,    10,    15
		db	   15,    11,    22,    33,    70
		db	   15,    23,    15,    63,    26
		db	   24,    33,    10,    61,    15
		db	   14,    34,    13,    71,    81
		db	   38,    73,    29,    17

cSides		dd	 1145,  1135,  1123,  1123,  1123
		dd	 1254,  1454,  1152,  1164,  1542
		dd	 1353,  1457,  1182,  1142,  1354
		dd	 1364,  1134,  1154,  1344,  1142
		dd	 1173,  1543,  1151,  1352,  1434
		dd	 1355,  1037,  1123,  1024,  1453
		dd	 1134,  2134,  1156,  1134,  1142
		dd	 1267,  1104,  1134,  1246,  1123
		dd	 1134,  1161,  1176,  1157,  1142
		dd	 1153,  1193,  1184,  1142

pSides		dw	  133,   114,   173,   131,   115
		dw	  164,   173,   174,   123,   156
		dw	  144,   152,   131,   142,   156
		dw	  115,   124,   136,   175,   146
		dw	  113,   123,   153,   167,   135
		dw	  114,   129,   164,   167,   134
		dw	  116,   113,   164,   153,   165
		dw	  126,   112,   157,   167,   134
		dw	  117,   114,   117,   125,   153
		dw	  123,   173,   115,   106

qSides		dd	 2183,  2372,  3231,  3121,  2153
		dd	 3254,  1342,  5341,  4158,  1523
		dd	 2125,  3133,  7384,  2274,  2114
		dd	 5645,  1371,  3123,  3317,  1923
		dd	 1634,  2334,  1156,  4164,  2742
		dd	 3453,  4153,  2284,  2142,  3144
		dd	 5345,  5130,  1423,  2113,  4123
		dd	 2434,  1334,  3056,  3184,  1242
		dd	 2353,  2153,  2284,  1142,  2334
		dd	 3145,  1934,  2123,  4113

length		dd	49

;area
aMin		dd	0
aeMed		dd	0
aMax		dd	0
aSum		dd	0
aAve		dd	0

;perimeter
pMin		dd	0
peMed		dd	0
pMax		dd	0
pSum		dd	0
pAve		dd	0


; --------------------------------------------------------------
; Uninitialized data

section	.bss

kiteAreas	resd	49
kitePerims	resd	49

section 	.text
global _start
_start:

;Find min, max, med, sum, and average of the area
mov ecx, dword[length]
mov rsi, 0

;Calculate the area = pSides * qSides / 2
areaLoop:
    movzx eax, word[pSides+rsi*2] 				;Convert current index  of pSides
    mul dword[qSides+rsi*4]						;Multiply by qSides
    mov edx, 0
    mov ecx, 2									
    div ecx
    mov dword[kiteAreas+rsi*4], eax				;Mov to kiteArea list

    cmp rsi, 49									;Check if end of list
    je endAreaLoop								

    inc rsi
    loop areaLoop

endAreaLoop:

;perimetre = 2 * aSides * cSides
;aside byte cside dword
mov rsi, 0
perimLoop:
    movzx eax, byte[aSides+rsi]					;Convert current index of aSides
	mov ecx, 2
    mul ecx
    mul dword[cSides+rsi*4]						;Multiply by cSides
    mov dword[kitePerims+rsi*4], eax			;Move to kitePerims list

    cmp rsi, 49									;Check if end of list
    je endPerimLoop

    inc rsi
    loop perimLoop

endPerimLoop:

mov eax, dword[kiteAreas]	
mov dword[aMin], eax							;Set area min to first index
mov dword[aMax], eax							;Set area max to first index

mov eax, dword[kitePerims]
mov dword[pMin], eax							;Set perim min to first index
mov dword[pMax], eax							;Set perim max to first index

mov ecx, dword[length]
mov rsi, 0

;Find minimum and maximum of area and perimeter
findLoop:
    mov eax, dword[kiteAreas+rsi*4]				;Get current index of area
	add dword[aSum], eax
    cmp eax, dword[aMin]						;Check if current area index is larger than min
    jae notAreaMinimum
    mov dword[aMin], eax						;Current index is min

notAreaMinimum:
    cmp eax, dword[aMax]						;Check if current area index is smaller than max
    jbe notAreaMaximum
    mov dword[aMax], eax						;Current index is max

notAreaMaximum:
    mov eax, dword[kitePerims+rsi*4]			;Get current index of perimeter
   	add dword[pSum], eax
    cmp eax, dword[pMin]						;Check if current perim index is larger than min
    jae notPerimMinimum
    mov dword[pMin], eax						;Current index is min

notPerimMinimum:
	cmp eax, dword[pMax]						;Check if current perim index is smaller than max
	jbe notPerimMaximum
	mov dword[pMax], eax						;Current index is max

notPerimMaximum:
	cmp rsi, 49									;Check if end of list
	je endFindLoop
	inc rsi
	loop findLoop

endFindLoop:

;Calculate medians
;Area median
mov eax, 0
mov edx, 0
mov eax, dword[kiteAreas]						;Index 0
add eax, dword[kiteAreas+96]					;Index 24
add eax, dword[kiteAreas+192]					;Index 49
mov ecx, 3
div ecx
mov dword[aeMed], eax

;Perimeter median
mov eax, 0
mov edx, 0
mov eax, dword[kitePerims]						;Index 0
add eax, dword[kitePerims+96]					;Index 24
add eax, dword[kiteAreas+192]					;Index 49
mov ecx, 3
div ecx
mov dword[peMed], eax

;Calculate averages
;Area average
mov eax, dword[aSum]
mov edx, 0
div dword[length]
mov dword[aAve], eax

;Perimeter average
mov eax, dword[pSum]
mov edx, 0
div dword[length]
mov dword[pAve], eax

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall
