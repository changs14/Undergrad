###########################################################################
#  Name: Stephaney Chang	
#  NSHE ID: 2001508920
#  Section: 1003
#  Assignment: MIPS #2
#  Description: This program will caculate the total surface area of a 3D trapezoid. Each trapezoid dimensions are
#				in an array: aSides, bSides, cSides, dSides, and heights. After the program will calculate the
#				minimum, median, maximum, sum and average of the areas. 

#  CS 218, MIPS Assignment #2
#  Provided Template

###########################################################
#  data segment

.data

aSides:		.word	   10,    14,    13,    37,    54
		.word	   31,    13,    20,    61,    36
		.word	   14,    53,    44,    19,    42
		.word	   27,    41,    53,    62,    10
		.word	   19,    28,    14,    10,    15
		.word	   15,    11,    22,    33,    70
		.word	   15,    23,    15,    63,    26
		.word	   24,    33,    10,    61,    15
		.word	   14,    34,    13,    71,    81
		.word	   38,    73,    29,    17,    93

bSides:		.word	  233,   214,   273,   231,   215
		.word	  264,   273,   274,   223,   256
		.word	  244,   252,   231,   242,   256
		.word	  215,   224,   236,   275,   246
		.word	  213,   223,   253,   267,   235
		.word	  204,   229,   264,   267,   234
		.word	  216,   213,   264,   253,   265
		.word	  226,   212,   257,   267,   234
		.word	  217,   214,   217,   225,   253
		.word	  223,   273,   215,   206,   213

cSides:		.word	  125,   124,   113,   117,   123
		.word	  134,   134,   156,   164,   142
		.word	  206,   212,   112,   131,   246
		.word	  150,   154,   178,   188,   192
		.word	  182,   195,   117,   112,   127
		.word	  117,   167,   179,   188,   194
		.word	  134,   152,   174,   186,   197
		.word	  104,   116,   112,   136,   153
		.word	  132,   151,   136,   187,   190
		.word	  120,   111,   123,   132,   145

dSides:		.word	  157,   187,   199,   111,   123
		.word	  124,   125,   126,   175,   194
		.word	  149,   126,   162,   131,   127
		.word	  177,   199,   197,   175,   114
		.word	  164,   141,   142,   173,   166
		.word	  104,   146,   123,   156,   163
		.word	  121,   118,   177,   143,   178
		.word	  112,   111,   110,   135,   110
		.word	  127,   144,   210,   172,   124
		.word	  125,   116,   162,   128,   192

heights:	.word	  117,   114,   115,   172,   124
		.word	  125,   116,   162,   138,   192
		.word	  111,   183,   133,   130,   127
		.word	  111,   115,   158,   113,   115
		.word	  117,   126,   116,   117,   227
		.word	  177,   199,   177,   175,   114
		.word	  194,   124,   112,   143,   176
		.word	  134,   126,   132,   156,   163
		.word	  124,   119,   122,   183,   110
		.word	  191,   192,   129,   129,   122

lengths:	.word	  135,   226,   162,   137,   127
		.word	  127,   159,   177,   175,   144
		.word	  179,   153,   136,   140,   235
		.word	  112,   154,   128,   113,   132
		.word	  161,   192,   151,   213,   126
		.word	  169,   114,   122,   115,   131
		.word	  194,   124,   114,   143,   176
		.word	  134,   126,   122,   156,   163
		.word	  149,   144,   114,   134,   167
		.word	  143,   129,   161,   165,   136

surfaceAreas:	.space	200

len:		.word	50

saMin:		.word	0 
saMid:		.word	0 
saMax:		.word	0 
saSum:		.word	0 
saAve:		.word	0 


# -----

hdr:	.ascii	"MIPS Assignment #2 \n"
	.ascii	"  3D Trapezoid Total Surface Areas Program:\n"
	.ascii	"  Also finds minimum, middle value, maximum, \n"
	.asciiz	"  sum, and average for the surface areas.\n\n"

a1_st:	.asciiz	"\nSurface Areas Minimum = "
a2_st:	.asciiz	"\nSurface Areas Middle  = "
a3_st:	.asciiz	"\nSurface Areas Maximum = "
a4_st:	.asciiz	"\nSurface Areas Sum     = "
a5_st:	.asciiz	"\nSurface Areas Average = "

newLn:	.asciiz	"\n"
blnks:	.asciiz	"  "


###########################################################
#  text/code segment

# --------------------
#  MIPS Assignment #2, compute total surface areas.
#  Also finds min, middle, max, sum, and average.

.text
.globl main
.ent main
main:

# -----
#  Display header.

	la	$a0, hdr
	li	$v0, 4
	syscall				# print header

##########################################################

# Load in arrays
la $t0, aSides 			# aSides array
la $t1, bSides			# bSides array
la $t2, cSides			# cSides array
la $t3, dSides			# dSides array
la $t4, heights			# heights array
la $t5, lengths			# length array
la $t6, surfaceAreas

# Index registers
lw $t8, len				# Length of arrays
li $t7, 0

calculateLoop:
	# Multiply lengths and heights
	lw $s0,($t4)		# Load in heights
	lw $s1, ($t5)		# Load in length
	lw $s3, ($t0)		# Load in aSides
	lw $s4, ($t1)		# Load in bSides
	lw $s5, ($t2)		# Load in cSides
	lw $s6, ($t3)		# Load in dSides

	mul $s2, $s0, $s1	# t2 = heights x length

	# aSides calulation
	mul $s3, $s3, $s2	# t3 = aSides x (heightsxlenghth)s

	# bSides calculation
	mul $s4, $s4, $s2	# t4 = bSides x (heightsxlengths)

	# cSides calculation
	mul $s5, $s5, $s1	# t5 = cSides * lengths

	# dSides calculation
	mul $s6, $s6, $s1	# t6 = dSides * lengths

	# Add a,b,c,d sides and store in t7
	addu $s7, $s7, $s2
	addu $s7, $s7, $s3
	addu $s7, $s7, $s4
	addu $s7, $s7, $s5
	addu $s7, $s7, $s6

	addu $t7, $t7, $s7
	sw $t7, saSum

	sw $s7, ($t6)

	# Update array addresses
	add $t0, $t0, 4
	add $t1, $t1, 4
	add $t2, $t2, 4
	add $t3, $t2, 4
	add $t4, $t4, 4
	add $t5, $t5, 4
	add $t6, $t6, 4

	sub $t8, $t8, 1

	bnez $t8, calculateLoop

# Find avverage of surfaceAreas
lw $t0, len
lw $t6, saSum
div $t5, $t6, $t0
sw $t5, saAve

# Find median
la $t0, surfaceAreas
lw $t1, len

div $t2, $t1, 2
mul $t3, $t2, 4		# Index offset?
add $t4, $t0, $t3	

lw $t5, ($t4)		#Array[len/2]
sub $t4, $t4, 4

lw $t6, ($t4)		#array[len/(2-1)]
add $t7, $t6, $t5
div $t8, $t7, 2

sw $t8, saMid		# Save median in variable

# Calculate min and max of tAreas
li $s2, 0			# Reset value in s2
la $s2, surfaceAreas
li $t0, 0 			# Index
lw $t1, ($s2)		# Minimum
lw $t2, ($s2)		# Maximum
lw $t3, len

# Find minimum and maximum of surfaceAreas
findMinMaxLoop:
	lw $t4, ($s2)	
	bge $t4, $t1, notMinimum
	sw $t1, saMin
	
notMinimum:
	ble $t4, $t2, notMaximum
	lw $t2, ($s2)

notMaximum:
	add $s2, $s2, 4		# Get next item in tAreas
	add $t0, $t0, 1		# index++

	blt $t0, $t3, findMinMaxLoop	#Loop if index is still in range

	sw $t1, saMin		# Save minimum value
	sw $t2, saMax		# Save max to variable


# Print surfaceArea array
la $s0, surfaceAreas
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

##########################################################
#  Display results.

	la	$a0, newLn		# print a newline
	li	$v0, 4
	syscall

#  Print min message followed by result.

	la	$a0, a1_st
	li	$v0, 4
	syscall				# print "min = "

	lw	$a0, saMin
	li	$v0, 1
	syscall				# print min

# -----
#  Print middle message followed by result.

	la	$a0, a2_st
	li	$v0, 4
	syscall				# print "med = "

	lw	$a0, saMid
	li	$v0, 1
	syscall				# print mid

# -----
#  Print max message followed by result.

	la	$a0, a3_st
	li	$v0, 4
	syscall				# print "max = "

	lw	$a0, saMax
	li	$v0, 1
	syscall				# print max

# -----
#  Print sum message followed by result.

	la	$a0, a4_st
	li	$v0, 4
	syscall				# print "sum = "

	lw	$a0, saSum
	li	$v0, 1
	syscall				# print sum

# -----
#  Print average message followed by result.

	la	$a0, a5_st
	li	$v0, 4
	syscall				# print "ave = "

	lw	$a0, saAve
	li	$v0, 1
	syscall				# print average

# -----
#  Done, terminate program.

endit:
	la	$a0, newLn		# print a newline
	li	$v0, 4
	syscall

	li	$v0, 10
	syscall				# all done!

.end main

