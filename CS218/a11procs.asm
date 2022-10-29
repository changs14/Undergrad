;  CS 218 - Assignment #11
;  Functions Template

; ***********************************************************************
;  Data declarations
;	Note, the error message strings should NOT be changed.
;	All other variables may changed or ignored...

section	.data

; -----
;  Define standard constants.

LF		equ	10			; line feed
NULL		equ	0			; end of string
SPACE		equ	0x20			; space

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; Successful operation
NOSUCCESS	equ	1			; Unsuccessful operation

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

O_CREAT		equ	0x40
O_TRUNC		equ	0x200
O_APPEND	equ	0x400

O_RDONLY	equ	000000q			; file permission - read only
O_WRONLY	equ	000001q			; file permission - write only
O_RDWR		equ	000002q			; file permission - read and write

S_IRUSR		equ	00400q
S_IWUSR		equ	00200q
S_IXUSR		equ	00100q

; -----
;  Define program specific constants.

MIN_FILE_LEN	equ	5

; buffer size (part A) - DO NOT CHANGE THE NEXT LINE.
BUFF_SIZE	equ	750000

; -----
;  Variables for getImageFileName() function.

eof		db	FALSE

usageMsg	db	"Usage: ./makeThumb <inputFile.bmp> "
		db	"<outputFile.bmp>", LF, NULL
errIncomplete	db	"Error, incomplete command line arguments.", LF, NULL
errExtra	db	"Error, too many command line arguments.", LF, NULL
errReadName	db	"Error, invalid source file name.  Must be '.bmp' file.", LF, NULL
errWriteName	db	"Error, invalid output file name.  Must be '.bmp' file.", LF, NULL
errReadFile	db	"Error, unable to open input file.", LF, NULL
errWriteFile	db	"Error, unable to open output file.", LF, NULL

; -----
;  Variables for setImageInfo() function.

HEADER_SIZE	equ	138

errReadHdr	db	"Error, unable to read header from source image file."
		db	LF, NULL
errFileType	db	"Error, invalid file signature.", LF, NULL
errDepth	db	"Error, unsupported color depth.  Must be 24-bit color."
		db	LF, NULL
errCompType	db	"Error, only non-compressed images are supported."
		db	LF, NULL
errSize		db	"Error, bitmap block size inconsistent.", LF, NULL
errWriteHdr	db	"Error, unable to write header to output image file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Variables for readRow() function.

buffMax		dq	BUFF_SIZE
curr		dq	BUFF_SIZE
wasEOF		db	FALSE
pixelCount	dq	0

errRead		db	"Error, reading from source image file.", LF,
		db	"Program terminated.", LF, NULL

; -----
;  Variables for writeRow() function.

errWrite	db	"Error, writting to output image file.", LF,
		db	"Program terminated.", LF, NULL

; ------------------------------------------------------------------------
;  Unitialized data

section	.bss

buffer		resb	BUFF_SIZE
header		resb	HEADER_SIZE

; ############################################################################

section	.text

; ***************************************************************
;  Routine to get image file names (from command line)
;	Verify files by atemptting to open the files (to make
;	sure they are valid and available).

;  Command Line format:
;	./makeThumb <inputFileName> <outputFileName>

; -----
;  Arguments:
;	- argc (value) - rdi
;	- argv table (address) - rsi
;	- read file descriptor (address) -rdx
;	- write file descriptor (address) - rcx
;  Returns:
;	read file descriptor (via reference)
;	write file descriptor (via reference)
;	TRUE or FALSE


global getImageFileNames
getImageFileNames:

push rbp
mov rsp, rbp

push r12
push r13

mov r12, rdi
mov r13, rsi

cmp r12, 1
je errorUsage

cmp r12, 3
jl fewArguments
jg tooManyArguments

;Check for bmp of the first file
mov r8, qword[r13+1*8]
mov r9, 0

checkFirst:
	mov al, byte[r8+r9]
	cmp al, '.'
	je checkAfter
	
	cmp r9, NULL
	je endFirst
	
	inc r9
	jmp checkFirst
	
checkAfter:
	mov al, byte[r8+r9]
	cmp al, 'b'
	jne invalidFileType
	inc r9
	mov al, byte[r8+r9]
	cmp al, 'm'
	jne invalidFileType
	inc r9
	cmp al, 'p'
	jne invalidFileType
	jmp endFirst
	
invalidFileType:
	mov rdi, errReadName
	call printString
	mov rax, FALSE
	jmp endGetParams
	
endFirst:

;Attempt to open the first file
mov rax, SYS_open
mov rdi, qword[r13+1*8]
mov rsi, O_RDONLY
syscall
cmp rax, 0
jl errorOnOpen

mov qword[rdx], rax

;Check bmp of second file
mov r8, qword[r13+2*8]
mov r9, 0

checkSecond:
	mov al, byte[r8+r9]
	cmp al, '.'
	je checkAfter2
	
	cmp r9, NULL
	je endSecond
	
	inc r9
	jmp checkFirst
	
checkAfter2:
	mov al, byte[r8+r9]
	cmp al, 'b'
	jne invalidFileType2
	inc r9
	mov al, byte[r8+r9]
	cmp al, 'm'
	jne invalidFileType2
	inc r9
	cmp al, 'p'
	jne invalidFileType2
	jmp endSecond
	
invalidFileType2:
	mov rdi, errWriteName
	call printString
	mov rax, FALSE
	jmp endGetParams
	
endSecond:

;Open the second file
mov rax, SYS_creat
mov rdi, qword[r13+2*8]
mov rsi, S_IRUSR | S_IWUSR
syscall
cmp rax, 0
jl errorCreate

mov qword[rcx], rax

jmp validArguments

fewArguments:
	mov rdi, errIncomplete
	call printString
	mov rax, FALSE
	jmp endGetParams
	
tooManyArguments:
	mov rdi, errExtra
	call printString
	mov rax, FALSE
	jmp endGetParams


errorUsage:
	mov rdi, usageMsg
	call printString
	mov rax, FALSE
	jmp endGetParams
	
validArguments:
	mov rax, TRUE
	jmp endGetParams
	
errorOnOpen:
	mov rdi, errReadFile
	call printString
	mov rax, FALSE
	jmp endGetParams
	
errorCreate:
	mov rdi, errWriteFile
	call printString
	mov rax, FALSE
	jmp endGetParams
	
endGetParams:

mov rdi, r12
mov rsi, r13

pop r13
pop r12
mov rbp, rsp
pop rbp

ret




; ***************************************************************
;  Read, verify, and set header information

;  HLL Call:
;	bool = setImageInfo(readFileDesc, writeFileDesc,
;		&picWidth, &picHeight, thumbWidth, thumbHeight)

;  If correct, also modifies header information and writes modified
;  header information to output file (i.e., thumbnail file).

; -----
;  2 -> BM				(+0)
;  4 file size				(+2)
;  4 skip				(+6)
;  4 header size			(+10)
;  4 skip				(+14)
;  4 width				(+18)
;  4 height				(+22)
;  2 skip				(+26)
;  2 depth (16/24/32)			(+28)
;  4 compression method code		(+30)
;  4 bytes of pixel data		(+34)
;  skip remaing header entries

; -----
;   Arguments:
;	- read file descriptor (value) - rdi
;	- write file descriptor (value) - rsi
;	- old image width (address) - rdx
;	- old image height (address) -rcx
;	- new image width (value) - r8
;	- new image height (value) - r9

;  Returns:
;	file size (via reference)
;	old image width (via reference)
;	old image height (via reference)
;	TRUE or FALSE


;	YOUR CODE GOES HERE

global setImageInfo
setImageInfo:

push rbp
mov rsp, rbp

push r12
push r13
push r14

mov r12, rdi
mov r13, rsi

mov rax, SYS_read
mov rsi, header
mov rdx, BUFF_SIZE
syscall

;Check bm
cmp byte[header], 'B'
jne errorSignature
cmp byte[header+1], 'M'
jne errorSignature

;Get the width of the original picture
;  4 width				(+18)

mov r11d, dword[header+18*4]
movsxd r10, r11d
mov qword[rdx], r10

;Get the height of the original picture

mov r11d, dword[header+22*4]
movsxd r10, r11d
mov qword[rcx], r10

;Update the file size
;  4 file size				(+2)
mov r11d, dword[header+2*4]


jmp endReadFile
	


errorSignature:
	mov rdi, errFileType
	call printString
	mov rax, FALSE
	jmp endReadFile

endReadFile:

pop r14
pop r13
pop r12

mov rbp, rsp
pop rbp

ret



; ***************************************************************
;  Return a row from read buffer
;	This routine performs all buffer management

; ----
;  HLL Call:
;	bool = readRow(readFileDesc, picWidth, rowBuffer[]);

;   Arguments:
;	- read file descriptor (value)
;	- image width (value)
;	- row buffer (address)
;  Returns:
;	TRUE or FALSE

; -----
;  This routine returns TRUE when row has been returned
;	and returns FALSE if there is no more data to
;	return (i.e., all data has been read) or if there
;	is an error on read (which would not normally occur).

;  The read buffer itself and some misc. variables are used
;  ONLY by this routine and as such are not passed.


;	YOUR CODE GOES HERE
global readRow
readRow:

ret


; ***************************************************************
;  Write image row to output file.
;	Writes exactly (width*3) bytes to file.
;	No requirement to buffer here.

; -----
;  HLL Call:
;	bool = writeRow(writeFileDesc, picWidth, rowBuffer);

;  Arguments are:
;	- write file descriptor (value)
;	- image width (value)
;	- row buffer (address)

;  Returns:
;	N/A

; -----
;  This routine returns TRUE when row has been written
;	and returns FALSE only if there is an
;	error on write (which would not normally occur).

;  The read buffer itself and some misc. variables are used
;  ONLY by this routine and as such are not passed.


;	YOUR CODE GOES HERE
global writeRow
writeRow:

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

