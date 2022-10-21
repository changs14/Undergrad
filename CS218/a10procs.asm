; *****************************************************************
;  Name: Stephaney Chang	
;  NSHE ID: 2001508920
;  Section: 1002
;  Assignment: 10
;  Description:  This program will work with OpenGL to create a circle image.
;		 The program will get user input of the drawing
;		 speed, colour, and size and check if the input is
;		 valid. Then using the values, use it to draw.

; -----
;  Function: getParams
;	Gets, checks, converts, and returns command line arguments.

;  Function drawWheels()
;	Plots functions

; ---------------------------------------------------------

;	MACROS (if any) GO HERE


; ---------------------------------------------------------

section  .data

; -----
;  Define standard constants.

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; successful operation
NOSUCCESS	equ	1

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; code for read
SYS_write	equ	1			; code for write
SYS_open	equ	2			; code for file open
SYS_close	equ	3			; code for file close
SYS_fork	equ	57			; code for fork
SYS_exit	equ	60			; code for terminate
SYS_creat	equ	85			; code for file open/create
SYS_time	equ	201			; code for get time

LF		equ	10
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  OpenGL constants

GL_COLOR_BUFFER_BIT	equ	16384
GL_POINTS		equ	0
GL_POLYGON		equ	9
GL_PROJECTION		equ	5889

GLUT_RGB		equ	0
GLUT_SINGLE		equ	0

; -----
;  Define program specific constants.

SPD_MIN		equ	1
SPD_MAX		equ	50			; 101(7) = 50

CLR_MIN		equ	0
CLR_MAX		equ	0xFFFFFF		; 0xFFFFFF = 262414110(7)

SIZ_MIN		equ	100			; 202(7) = 100
SIZ_MAX		equ	2000			; 5555(7) = 2000

; -----
;  Local variables for getParams functions.

STR_LENGTH	equ	12

errUsage	db	"Usage: ./wheels -sp <septNumber> -cl <septNumber> "
		db	"-sz <septNumber>"
		db	LF, NULL
errBadCL	db	"Error, invalid or incomplete command line argument."
		db	LF, NULL

errSpdSpec	db	"Error, speed specifier incorrect."
		db	LF, NULL
errSpdValue	db	"Error, speed value must be between 1 and 101(7)."
		db	LF, NULL

errClrSpec	db	"Error, color specifier incorrect."
		db	LF, NULL
errClrValue	db	"Error, color value must be between 0 and 262414110(7)."
		db	LF, NULL

errSizSpec	db	"Error, size specifier incorrect."
		db	LF, NULL
errSizValue	db	"Error, size value must be between 202(7) and 5555(7)."
		db	LF, NULL

; -----
;  Local variables for drawWheels routine.

t		dq	0.0			; loop variable
s		dq	0.0
tStep		dq	0.001			; t step
sStep		dq	0.0
x		dq	0			; current x
y		dq	0			; current y
scale		dq	7500.0			; speed scale

fltZero		dq	0.0
fltOne		dq	1.0
fltTwo		dq	2.0
fltThree	dq	3.0
fltFour		dq	4.0
fltSix		dq	6.0
fltTwoPiS	dq	0.0

pi		dq	3.14159265358

fltTmp1		dq	0.0
fltTmp2		dq	0.0

red		dd	0			; 0-255
green		dd	0			; 0-255
blue		dd	0			; 0-255


newLine db LF, NULL
; ------------------------------------------------------------

section  .text

; -----
; Open GL routines.

extern	glutInit, glutInitDisplayMode, glutInitWindowSize, glutInitWindowPosition
extern	glutCreateWindow, glutMainLoop
extern	glutDisplayFunc, glutIdleFunc, glutReshapeFunc, glutKeyboardFunc
extern	glutSwapBuffers, gluPerspective, glutPostRedisplay
extern	glClearColor, glClearDepth, glDepthFunc, glEnable, glShadeModel
extern	glClear, glLoadIdentity, glMatrixMode, glViewport
extern	glTranslatef, glRotatef, glBegin, glEnd, glVertex3f, glColor3f
extern	glVertex2f, glVertex2i, glColor3ub, glOrtho, glFlush, glVertex2d

extern	cos, sin


; ******************************************************************
;  Function getParams()
;	Gets draw speed, draw color, and screen size
;	from the command line arguments.

;	Performs error checking, converts ASCII/septenary to integer.
;	Command line format (fixed order):
;	  "-sp <septNumber> -cl <septNumber> -sz <septyNumber>"

; -----
;  Arguments:
;	ARGC, double-word, value	-rdi
;	ARGV, double-word, address	-rsi
;	speed, double-word, address	-rdx
;	color, double-word, address	-rcx
;	size, double-word, address	-r8

;7 arguments

; Returns:
;	speed, color, and size via reference (of all valid)
;	TRUE or FALSE


global getParams
getParams:

push rbp
mov rsp, rbp

push r12
push r13
push r14
push r15
push rbx

mov r12, rdi		;arg count
mov r13,  rsi		;arguments

;Check if enough arguments in command line
cmp r12, 1
je errorUsage

cmp r12, 7
jb errorCL
ja errorCL

;Check values
;Check speed specifier
mov rdi, qword[r13+1*8]
cmp byte[rdi+0], '-'
jne errorSpeedSpec
cmp byte[rdi+1], 's'
jne errorSpeedSpec
cmp byte[rdi+2], 'p'
jne errorSpeedSpec

;Check speed value
mov rdi, qword[r13+2*8]

;Convert speed to integer value
mov rax, 0
mov r14, 0
mov r15, 7

convertSpeedLoop:
	movsx r8, byte[rdi+r14]
	cmp r8, NULL
	je endSpeedConvert
	sub r8, 0x30
	cmp r8, 7
	ja errorSpeedSize
	cmp r8, 0
	jb errorSpeedSize
	mul r15
	add rax, r8
	mov r10, rax
	
	inc r14
	jmp convertSpeedLoop
	
endSpeedConvert:

cmp r10, SPD_MIN
jb errorSpeedSize
cmp r10, SPD_MAX
ja errorSpeedSize


;Store speed in rdx
mov rdx, r10

;Check colour specifier
mov rdi, qword[r13+3*8]
cmp byte[rdi+0], '-'
jne errorColourSpec
cmp byte[rdi+1], 'c'
jne errorColourSpec
cmp byte[rdi+2], 'l'
jne errorColourSpec

;Check colour value
mov rdi, qword[r13+4*8]

;Convert colour to integer value
mov rax, 0
mov r14, 0
mov r15, 7

convertColourLoop:
	movsx r8, byte[rdi+r14]
	cmp r8, NULL
	je endColourConvert
	sub r8, 0x30
	cmp r8, 7
	ja errorColourSize
	cmp r8, 0
	jb errorColourSize
	mul r15
	add rax, r8
	mov r10, rax
	
	inc r14
	jmp convertColourLoop

endColourConvert:

cmp r10, CLR_MIN
jb errorColourSize
cmp r10, CLR_MAX
ja errorColourSize

;Store colour in rcx
mov rcx, r10

;Check size specifier
mov rdi, qword[r13+5*8]
cmp byte[rdi+0], '-'
jne errorSizeSpec
cmp byte[rdi+1], 's'
jne errorSizeSpec
cmp byte[rdi+2], 'z'
jne errorSizeSpec

;Check size value
mov rdi, qword[r13+6*8]

;Convert size to integer value
mov rax, 0
mov r14, 0
mov r15, 7

convertSizeLoop:
	movsx r8, byte[rdi+r14]
	cmp r8, NULL
	je endSizeConvert
	sub r8, 0x30
	cmp r8, 7
	ja errorSizeValue
	cmp r8, 0
	jb errorSizeValue
	mul r15
	add rax, r8
	mov r10, rax
	
	inc r14
	jmp convertSizeLoop

endSizeConvert:

cmp r10, SIZ_MIN
jb errorSizeValue
cmp r10, SIZ_MAX
ja errorSizeValue
	

mov r8, r10

mov rax, TRUE

jmp endGetParams

errorUsage:
	mov rdi, errUsage
	call printString
	mov rax, FALSE
	jmp endGetParams

errorCL:
	mov rdi, errBadCL
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorSpeedSpec:
	mov rdi, errSpdSpec
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorSpeedSize:
	mov rdi, errSpdValue
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorColourSpec:
	mov rdi, errClrSpec
	call printString
	mov rax, FALSE
	jmp endGetParams

errorColourSize:
	mov rdi, errClrValue
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorSizeSpec:
	mov rdi, errSizSpec
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorSizeValue:
	mov rdi, errSizValue
	call printString
	mov rax, FALSE
	jmp endGetParams
	
endGetParams:

pop rbx
pop r15
pop r14
pop r13
pop r12
mov rsp, rbp
pop rbp


ret




; ******************************************************************
;  Draw wheels function.
;	Plot the provided functions (see PDF).

; -----
;  Arguments:
;	none -> accesses global variables.
;	nothing -> is void

; -----
;  Gloabl variables Accessed:

common	speed		1:4			; draw speed, dword, integer value
common	color		1:4			; draw color, dword, integer value
common	size		1:4			; screen size, dword, integer value

global drawWheels
drawWheels:
	push	rbp

; do NOT push any additional registers.
; If needed, save regitser to quad variable...

; -----
;  Set draw speed step
;	sStep = speed / scale

cvtsi2sd xmm0, dword[speed]
divsd xmm0, qword[scale]
movsd qword[sStep], xmm0

; -----
;  Prepare for drawing
	; glClear(GL_COLOR_BUFFER_BIT);
	mov	rdi, GL_COLOR_BUFFER_BIT
	call	glClear

	; glBegin();
	mov	rdi, GL_POINTS
	call	glBegin

; -----
;  Set draw color(r,g,b)
;	uses glColor3ub(r,g,b)

mov eax, dword[color]
mov byte[blue], al

shr eax, 8
mov byte[green], al

shr eax, 8
mov byte[red],al

mov rdi, red
mov rsi, green
mov rdx, blue
call glColor3ub

; -----
;  main plot loop
;	iterate t from 0.0 to 2*pi by tStep
;	uses glVertex2d(x,y) for each formula


;	YOUR CODE GOES HERE

;fltTwoPiS
movsd xmm1, qword[fltTwo]
mulsd xmm1, qword[pi]
movsd qword[fltTwoPiS], xmm1

movsd xmm2, qword[fltZero]

firstFunctionLoop:
	movsd qword[t], xmm2
	
	movsd xmm0, qword[t]
	call sin
	movsd qword[y], xmm0	;y =sin(t)

	call cos
	movsd qword[x], xmm0	;x=cos(t)
	
	movsd xmm0, qword[x]
	movsd xmm1, qword[y]
	
	call glVertex2d
	
	ucomisd xmm2, qword[fltTwoPiS]
	je endFirstFunction
	
	addsd xmm2, qword[tStep]
	
	jmp firstFunctionLoop
	
endFirstFunction:

movsd xmm0, qword[s]
addsd xmm0, qword[sStep]
movsd qword[s], xmm0

movsd xmm0, qword[fltZero]
movsd qword[t], xmm0

secondFunction:
	;Get x2
	;cos(t)/3 + 2cos(2pis)/3
	movsd xmm0, qword[t]
	call cos
	divsd xmm0, qword[fltThree]
	movsd qword[x], xmm0
	
	;2cos(2pis)/3
	mulsd xmm0, qword[fltTwo]
	mulsd xmm0, qword[fltTwoPiS]
	mulsd xmm0, qword[s]
	call cos
	mulsd xmm0, qword[fltTwo]
	divsd xmm0, qword[fltThree]
	movsd qword[fltTmp1], xmm0
	
	movsd xmm1, qword[x]
	addsd xmm1, xmm0
	movsd qword[x], xmm1
	
	;sin(t)/3
	movsd xmm0, qword[t]
	call sin
	divsd xmm0, qword[fltThree]
	movsd qword[y], xmm0
	
	;2sin(2pis)/3
	mulsd xmm0, qword[fltTwo]
	mulsd xmm0, qword[fltTwoPiS]
	mulsd xmm0, qword[s]
	call sin
	mulsd xmm0, qword[fltTwo]
	divsd xmm0, qword[fltThree]
	
	movsd qword[fltTmp2], xmm0
	
	movsd xmm1, qword[y]
	addsd xmm1, xmm0
	movsd qword[y], xmm1
	
	movsd xmm0, qword[x]
	movsd xmm1, qword[y]
	
	call glVertex2d

	ucomisd xmm2, qword[fltTwoPiS]
	je endFirstFunction
	
	addsd xmm2, qword[tStep]
	jmp secondFunction

endSecondFunction:

movsd xmm0, qword[s]
addsd xmm0, qword[sStep]
movsd qword[s], xmm0
	
movsd xmm0, qword[fltZero]
movsd qword[t], xmm0

thirdFunction:
	;tcos(4pis)/6pi
	movsd xmm1, qword[fltSix]
	mulsd xmm1, qword[pi]
	
	movsd xmm0, qword[fltFour]
	mulsd xmm0, qword[pi]
	mulsd xmm0, qword[s]
	call cos
	mulsd xmm0, qword[2]
	
	divsd xmm0, xmm1
	addsd xmm0, qword[fltTmp1]
	
	movsd qword[x], xmm0
	
	;2sin(2pis)/3
	mulsd xmm0, qword[fltTwo]
	mulsd xmm0, qword[fltTwoPiS]
	mulsd xmm0, qword[s]
	call cos
	mulsd xmm0, qword[fltTwo]
	divsd xmm0, qword[fltThree]
	
	movsd xmm2, xmm0
	
	;tsin(4pis)/(6pi)
	
	movsd xmm1, qword[fltFour]
	mulsd xmm1, qword[pi]
	mulsd xmm1, qword[s]
	movsd xmm0, xmm1
	call sin
	mulsd xmm0, qword[t]
	
	movsd xmm2, qword[fltSix]
	mulsd xmm2, qword[pi]
	
	divsd xmm0, xmm2
	
	movsd xmm3, qword[fltTmp2]
	subsd xmm3, xmm0
	
	movsd qword[y], xmm3
	
	movsd xmm0, qword[x]
	movsd xmm1, qword[y]
	
	call glVertex2d

	ucomisd xmm2, qword[fltTwoPiS]
	je endThirdFunction
	
	addsd xmm2, qword[tStep]
	jmp thirdFunction 

endThirdFunction:

movsd xmm0, qword[s]
addsd xmm0, qword[sStep]
movsd qword[s], xmm0

movsd xmm0, qword[fltZero]
movsd qword[t], xmm0

fourthFunction:
	;2cos... -fltTmp1
	
	movsd xmm0, qword[fltFour]
	mulsd xmm0, qword[pi]
	mulsd xmm0, qword[s]
	
	movsd xmm1, qword[fltTwo]
	mulsd xmm1, qword[pi]
	divsd xmm1, qword[fltThree]
	
	addsd xmm0, xmm1
	movsd xmm4, xmm0
	call cos
	
	movsd xmm2, qword[fltSix]
	mulsd xmm2, qword[pi]
	divsd xmm0, xmm2
	
	movsd xmm3, qword[fltTmp1]
	addsd xmm3, xmm0
	movsd qword[x], xmm3
	
	;tsin...
	movsd xmm0, xmm4
	call sin
	mulsd xmm0, qword[t]
	divsd xmm0, xmm2
	
	movsd xmm3, qword[fltTmp2]
	addsd xmm3, xmm0
	movsd qword[y], xmm3
	
	movsd xmm0, qword[x]
	movsd xmm1, qword[y]
	
	call glVertex2d

	ucomisd xmm2, qword[fltTwoPiS]
	je endFourthFunction
	
	addsd xmm2, qword[tStep]
	jmp fourthFunction 
	

endFourthFunction:

movsd xmm0, qword[s]
addsd xmm0, qword[sStep]
movsd qword[s], xmm0

movsd xmm0, qword[fltZero]
movsd qword[t], xmm0

fifthFunction:
	;2cos... -fltTmp1
	
	movsd xmm0, qword[fltFour]
	mulsd xmm0, qword[pi]
	mulsd xmm0, qword[s]
	
	movsd xmm1, qword[fltTwo]
	mulsd xmm1, qword[pi]
	divsd xmm1, qword[fltThree]
	
	addsd xmm0, xmm1
	movsd xmm4, xmm0
	call cos
	
	movsd xmm2, qword[fltSix]
	mulsd xmm2, qword[pi]
	divsd xmm0, xmm2
	
	movsd xmm3, qword[fltTmp1]
	addsd xmm3, xmm0
	movsd qword[x], xmm3
	
	;tsin...
	movsd xmm0, xmm4
	call sin
	mulsd xmm0, qword[t]
	divsd xmm0, xmm2
	
	movsd xmm3, qword[fltTmp2]
	addsd xmm3, xmm0
	movsd qword[y], xmm3
	
	movsd xmm0, qword[x]
	movsd xmm1, qword[y]
	
	call glVertex2d

	ucomisd xmm2, qword[fltTwoPiS]
	je endFifthFunction
	
	addsd xmm2, qword[tStep]
	jmp fifthFunction 
	
endFifthFunction:

; -----
;  Display image

	call	glEnd
	call	glFlush

; -----
;  Update s, s += sStep;
;  if (s > 1.0)
;	s = 0.0;

	movsd	xmm0, qword [s]			; s+= sStep
	addsd	xmm0, qword [sStep]
	movsd	qword [s], xmm0

	movsd	xmm0, qword [s]
	movsd	xmm1, qword [fltOne]
	ucomisd	xmm0, xmm1			; if (s > 1.0)
	jbe	resetDone

	movsd	xmm0, qword [fltZero]
	movsd	qword [sStep], xmm0
resetDone:

	call	glutPostRedisplay

; -----

	pop	rbp
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

