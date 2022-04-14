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
lw $t6, len				# Length of arrays
li $t7, 0				# Array index

calculateLoop:
	# Multiply lengths and heights


# aSides calulation

# bSides calculation

# cSides calculation

# dSides calculation

# Add a,b,c,d sides

# Find sum

# Find average

# Find median

# Find min and max

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

