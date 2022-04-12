###########################################################################
#  Name: Stephaney Chang	
#  NSHE ID: 2001508920	
#  Section: 1003
#  Assignment: MIPS #1
#  Description: This program will calculate the area of each trapezoid in a set of trapexoids
#				It will take in word sized values: aSides, cSides, and heights.

#  CS 218, MIPS Assignment #1
#  Template

###########################################################################
#  data segment

.data

aSides:	.word	   1,    2,    3,    4,    5,    6,    7,    8,    9,   10
	.word	  15,   25,   33,   44,   58,   69,   72,   86,   99,  101
	.word	 107,  121,  137,  141,  157,  167,  177,  181,  191,  199
	.word	 202,  209,  215,  219,  223,  225,  231,  242,  244,  249
	.word	 251,  253,  266,  269,  271,  272,  280,  288,  291,  299
	.word	 369,  374,  377,  379,  382,  384,  386,  388,  392,  393
	.word	1469, 2474, 3477, 4479, 5482, 5484, 6486, 7788, 8492, 1493

cSides:	.word	   1,    2,    3,    4,    5,    6,    7,    8,    9,   10
	.word	  32,   51,   76,   87,   90,  100,  111,  123,  132,  145
	.word	 206,  212,  222,  231,  246,  250,  254,  278,  288,  292
	.word	 332,  351,  376,  387,  390,  400,  411,  423,  432,  445
	.word	 457,  487,  499,  501,  523,  524,  525,  526,  575,  594
	.word	 634,  652,  674,  686,  697,  704,  716,  720,  736,  753
	.word	1782, 2795, 3807, 3812, 4827, 5847, 6867, 7879, 7888, 1894

heights:
	.word	   1,    2,    3,    4,    5,    6,    7,    8,    9,   10
	.word	 102,  113,  122,  139,  144,  151,  161,  178,  186,  197
	.word	 203,  215,  221,  239,  248,  259,  262,  274,  280,  291
	.word	 400,  404,  406,  407,  424,  425,  426,  429,  448,  492
	.word	 501,  513,  524,  536,  540,  556,  575,  587,  590,  596
	.word	 782,  795,  807,  812,  827,  847,  867,  879,  888,  894
	.word	1912, 2925, 3927, 4932, 5447, 5957, 6967, 7979, 7988, 1994

tAreas:	.space	280

len:	.word	70

taMin:	.word	0
taMid:	.word	0
taMax:	.word	0
taSum:	.word	0
taAve:	.word	0

LN_CNTR	= 8

# -----

hdr:	.ascii	"MIPS Assignment #1 \n"
	.ascii	"Program to calculate area of each trapezoid in a series "
	.ascii	"of trapezoids. \n"
	.ascii	"Also finds min, mid, max, sum, and average for the "
	.asciiz	"trapezoid areas. \n\n"

new_ln:	.asciiz	"\n"
blnks:	.asciiz	"  "

a1_st:	.asciiz	"\nTrapezoid min = "
a2_st:	.asciiz	"\nTrapezoid med = "
a3_st:	.asciiz	"\nTrapezoid max = "
a4_st:	.asciiz	"\nTrapezoid sum = "
a5_st:	.asciiz	"\nTrapezoid ave = "


###########################################################
#  text/code segment

.text
.globl main
.ent main
main:

# -----
#  Display header.

	la	$a0, hdr
	li	$v0, 4
	syscall				# print header

# --------------------------------------------------------

# Load in arrays
lw $t0, len				# Length of array
la $t1, aSides			# aSides
la $t2, cSides			# cSides
la $t3, heights			# Heights
la $t4, tAreas			# Array to store tAreas

li $t5, 0 				# Running sum

calculateLoop:
    lw $s1, ($t1)		# Load in aSides
    lw $s2, ($t2)		# Load in cSides
    lw $s3, ($t3)		# Load in heights
    lw $t6, ($t4)		# Load in tAreas

    add $s4, $s1, $s2	# s4=   aSides + cSides
    div $s5, $s4, 2		# s5 = s4/2
    mul $s6, $s5, $s3   # Area saved in s6

    add $t5, $t5, $s6 	# Running sum, store in t5
	sw $t5, taSum

    sw $s6, ($t4)		# Save results in s6 in t4

	# Get next item in arrays
    add $t1, $t1, 4
    add $t2, $t2, 4
    add $t3, $t3, 4
    add $t4, $t4, 4

    sub $t0, $t0, 1		# Decrement counter

    bnez $t0, calculateLoop	# Check if end of array

# ----------------------------------------------------------

# Find the average of tAreas in t5
# Length in t0

# Reset registers?
li $t0, 0
li $t6, 0

lw $t0, len
lw $t6, taSum
div $t5, $t6, $t0	# t5 = running sum / length
sw $t5, taAve		# Store in average variable

# Calculate min and max of tAreas
li $s2, 0			# Reset value in s2
la $s2, tAreas
li $t0, 0 			# Index
lw $t1, ($s2)		# Minimum
lw $t2, ($s2)		# Maximum
lw $t3, len

findMinMaxLoop:
	lw $t4, ($s2)	
	bge $t4, $t1, notMinimum
	sw $t1, taMin
	
notMinimum:
	ble $t4, $t2, notMaximum
	lw $t2, ($s2)

notMaximum:
	add $s2, $s2, 4		# Get next item in tAreas
	add $t0, $t0, 1		# index++

	blt $t0, $t3, findMinMaxLoop	#Loop if index is still in range

	sw $t1, taMin		# Save minimum value
	sw $t2, taMax		# Save max to variable

# Find the median of tAreas
la $t0, tAreas
lw $t1, len

div $t2, $t1, 2
mul $t3, $t2, 4		# Index offset?
add $t4, $t0, $t3	

lw $t5, ($t4)		#Array[len/2]
sub $t4, $t4, 4

lw $t6, ($t4)		#array[len/(2-1)]
add $t7, $t6, $t5
div $t8, $t7, 2

sw $t8, taMid		# Save median in variable

# Print tArea array

la $s0, tAreas
lw $s1, len

printLoop:
    li $v0, 1               # Print current value
    lw $a0, ($s0)
    syscall

    add $s0, $s0, 4
    sub $s1, $s1, 1

    li $v0, 4              #Print formatting blank
    la $a0, blnks
    syscall

    bnez $s1, printLoop

# --------------------------------------------------------
#  Display results.

	la	$a0, new_ln		# print a newline
	li	$v0, 4
	syscall
	la	$a0, new_ln		# print a newline
	li	$v0, 4
	syscall

#  Print min message followed by result.

	la	$a0, a1_st
	li	$v0, 4
	syscall				# print "min = "

	lw	$a0, taMin
	li	$v0, 1
	syscall				# print min

# -----
#  Print middle message followed by result.

	la	$a0, a2_st
	li	$v0, 4
	syscall				# print "med = "

	lw	$a0, taMid
	li	$v0, 1
	syscall				# print mid

# -----
#  Print max message followed by result.

	la	$a0, a3_st
	li	$v0, 4
	syscall				# print "max = "

	lw	$a0, taMax
	li	$v0, 1
	syscall				# print max

# -----
#  Print sum message followed by result.

	la	$a0, a4_st
	li	$v0, 4
	syscall				# print "sum = "

	lw	$a0, taSum
	li	$v0, 1
	syscall				# print sum

# -----
#  Print average message followed by result.

	la	$a0, a5_st
	li	$v0, 4
	syscall				# print "ave = "

	lw	$a0, taAve
	li	$v0, 1
	syscall				# print average

# -----
#  Done, terminate program.

endit:
	la	$a0, new_ln		# print a newline
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall				# all done!

.end main

