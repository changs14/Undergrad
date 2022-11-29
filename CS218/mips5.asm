###########################################################################
#  Name: Stephaney Chang 
#  NSHE ID: 2001508920 
#  Section: 1002
#  Assignment: MIPS #5
#  Description: Using recurdion, determine thenumber of possible paths through a two-dimensional gride. 


###########################################################################
#  data segment

.data

# -----
#  Constants

TRUE = 1
FALSE = 0
COORD_MAX = 100

# -----
#  Variables for main

hdr:		.ascii	"\n**********************************************\n"
		.ascii	"\nMIPS Assignment #5\n"
		.asciiz	"Count Grid Paths Program\n"

startRow:	.word	0
startCol:	.word	0
endRow:		.word	0
endCol:		.word	0

totalCount:	.word	0

endMsg:		.ascii	"\nYou have reached recursive nirvana.\n"
		.asciiz	"Program Terminated.\n"

# -----
#  Local variables for prtResults() function.

cntMsg1:	.asciiz	"\nFrom a start coordinate of ("
cntMsgComma:	.asciiz	","
cntMsg2:	.asciiz	"), to an end coordinate of ("
cntMsg3:	.asciiz	"), \nthere are "
cntMsg4:	.asciiz	" ways traverse the grid.\n"

# -----
#  Local variables for readCoords() function.

strtRowPmt:	.asciiz	"  Enter Start Coordinates ROW: "
strtColPmt:	.asciiz	"  Enter Start Coordinates COL: "

endRowPmt:	.asciiz	"  Enter End Coordinates ROW: "
endColPmt:	.asciiz	"  Enter End Coordinates COL: "

err0:		.ascii	"\nError, invalid coordinate value.\n"
		.asciiz	"Please re-enter.\n"

err1:		.ascii	"\nError, end coordinates must be > then "
		.ascii	"the start coordinates. \n"
		.asciiz	"Please re-enter.\n"

spc:		.asciiz	"   "

# -----
#  Local variables for prtNewline function.

newLine:	.asciiz	"\n"


###########################################################################
#  text/code segment

.text
.globl main
.ent main
main:

# -----
#  Display program header.

	la	$a0, hdr
	li	$v0, 4
	syscall					# print header

# -----
#  Function to read and return initial coordinates.

	la	$a0, startRow
	la	$a1, startCol
	la	$a2, endRow
	la	$a3, endCol
	jal	readCoords

# -----
#  countPaths - determine the number of possible
#		paths through a two-dimensional grid.
#	returns integer answer.

#  HLL Call:
#	totalCount = countPaths(startRow, startCol, endRow, endCol)

	lw	$a0, startRow
	lw	$a1, startCol
	lw	$a2, endRow
	lw	$a3, endCol
	jal	countPaths
	sw	$v0, totalCount

# ----
#  Display results (formatted).

	lw	$a0, startRow
	lw	$a1, startCol
	lw	$a2, endRow
	lw	$a3, endCol
	subu	$sp, $sp, 4
	lw	$t0, totalCount
	sw	$t0, ($sp)
	jal	prtResults
	addu	$sp, $sp, 4

# -----
#  Done, show message and terminate program.

	li	$v0, 4
	la	$a0, endMsg
	syscall

	li	$v0, 10
	syscall					# all done...
.end main

# =========================================================================
#  Very simple function to print a new line.
#	Note, this routine is optional.

.globl	prtNewline
.ent	prtNewline
prtNewline:
	la	$a0, newLine
	li	$v0, 4
	syscall

	jr	$ra
.end	prtNewline

# =========================================================================
#  Function to print final results (formatted).

# -----
#    Arguments:
#	startRow, value a0
#	startCol, value 1
#	endRow, value 2
#	endCol, value 3
#	totalCount, value stack ($fp)
#    Returns:

.globl	prtResults
.ent	prtResults
prtResults:

subu $sp, $sp, 24
sw $fp, ($sp)
sw $s0, 0($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $s4, 16($sp)
sw $ra, 20($sp)

addu $fp, $sp, 24

# Save values
move $s0, $a0
move $s1, $a1
move $s2, $a2
move $s3, $a3
lw $s4, ($fp)

li $v0, 4
la $a0, cntMsg1
syscall

li $v0, 1
move $a0, $s0
syscall

li $v0, 4
la $a0, cntMsgComma
syscall

li $v0, 1
move $a0, $s1
syscall

li $v0, 4
la $a0, cntMsg2
syscall

li $v0, 1
move $a0, $s2
syscall

li $v0, 4
la $a0, cntMsgComma
syscall

li $v0, 1
move $a0, $s3
syscall

li $v0, 4
la $a0, cntMsg3
syscall

li $v0, 1
move $a0, $s4
syscall

li $v0, 4
la  $a0, cntMsg4
syscall

lw $fp, ($sp)
addu $sp, $sp, 24
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $s4, 15($sp)
lw $ra, 20($sp)


	jr	$ra
.end	prtResults

# =========================================================================
#  Prompt for and read start and end coordinates.
#  Also, must ensure that:
#	each value is between 0 and COORD_MAX
#	start coordinates are < end coordinates

# -----
#    Arguments:
#	startRow, address		a0
#	startCol, address		a1
#	endRow, address			a2
#	endCol, address			a3
#    Returns:
#	startRow, startCol, endRow, endCol via reference

.globl	readCoords
.ent	readCoords
readCoords:

subu $sp, $sp, 20
sw $s0, 0($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $ra, 16($sp)

getUserInput:
	# Print the start row prompt
	li $v0, 4
	la $a0, strtRowPmt
	syscall

	# Get startRow
	li $v0, 5
	syscall
	move $s0, $v0
	bltz $s0, errorSize2

	# Print the start column prompt
	li $v0, 4
	la $a0, strtColPmt
	syscall

	# Get startCol
	li $v0, 5
	syscall
	move $s1, $v0
	bltz $s1, errorSize2

	# Print end row pmt
	li $v0, 4
	la $a0, endRowPmt
	syscall

	# Get end row
	li $v0, 5
	syscall
	move $s2, $v0

	# End col prompt
	li $v0, 4
	la $a0, endColPmt
	syscall

	li $v0, 5
	syscall
	move $s3, $v0

# Compare the rows
# a1 < a2
bgt $s0, $s2, errorSize
bgt $s1, $s3, errorSize

b skipError

errorSize:
	li $v0, 4
	la $a0, err1 
	syscall

	b getUserInput

errorSize2:
	li $v0, 4
	la  $a0, err0
	syscall

	b getUserInput

skipError:

# All error checking passed, save values
move $a0, $s0
move $a1, $s1
move $a2, $s2
move $a3, $s3

addu $sp, $sp, 20
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $ra, 16($sp)

	jr	$ra
.end	readCoords

#####################################################################
#  Function to recursivly determine the number of possible
#  paths through a two-dimensional grid.
#  Only allowed moves are one step to the right or one step down.  

#  HLL Call:
#	totalCount = countPaths(startRow, startCol, endRow, endCol)

# -----
#  Arguments:
#	startRow, value - a0
#	startCol, value a1
#	endRow, value a2
#	endCol, value a3

#  Returns:
#	$v0 - paths count

.globl	countPaths
.ent	countPaths
countPaths:

subu $sp, $sp, 24
sw $fp, ($sp)
sw $s0, 0($sp)
sw $s1, 4($sp)
sw $s2, 8($sp)
sw $s3, 12($sp)
sw $s4, 16($sp)
sw $ra, 20($sp)

# Save values
move $s0, $a0	# start row
move $s1, $a1	# start col
move $s2, $a2	# end row
move $s3, $a3	# end col

bgt $s0, $s2, returnZero	# Compare row > end row
bgt $s1, $s3, returnZero		# Compare col > end col

beq $s0, $s2, returnOne
beq $s1, $s3, returnOne

# (c + 1)
add $t0, $s1, 1

move $a0, $s0
move $a1, $t0
move $a2, $s2
move $a3, $s3
jal countPaths

# Save returned value
move $s4, $v0

# r+1
add $t0, $s0, 1

move $a0, $t0
move $a1, $s1
move $a2, $s2
move $a3, $a3
jal countPaths

add $v0, $v0, $s4

b end

returnZero:
	li $v0, 0
	b end

returnOne:
	li $v0, 1
	b end

end:

lw $fp, ($sp)
addu $sp, $sp, 24
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $s2, 8($sp)
lw $s3, 12($sp)
lw $s4, 15($sp)
lw $ra, 20($sp)


	jr	$ra
.end countPaths

#####################################################################

