  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.
#.global delay  
#.global	time2string 
  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.data
.global hexacs, delay, time2string,enable_interrupt

.text
hexasc:
	andi $a0, $a0, 0x000000f
	
	slti $t1,$a0, 10
	
	beq $t1, 1, numbers
	nop
	beq $t1, 0, letters
	nop
	
	numbers:
		addi $v0, $a0, 0x30
		jr $ra
		nop
		
	letters:
		addi $v0, $a0, 0x37
		jr $ra
		nop

delay:
PUSH $s0

#PUSH $ra

#addi $a0, $0, 10
addi $s0, $a0, 0 #in adressen
addi $t1, $zero, 0 #initialze t?
addi $t4, $zero, 1 #sätt bara t4 = 1 för slti sen
addi $t5, $zero, 4511 #talet vi sätter i for loopen

	while:
	#addi $s0, $s0, -1 # i - 1
	beq $s0, $zero, slut
	nop
	
	slti $t1, $s0, 0 # if s0 is less than 0 set t1 to 1 else t1 to 0
	beq $t1, $t4, slut
	nop
	
	addi $s0, $s0, -1 # i - 1
	
	
		
		for:
		beq $t1, $t5, while #gör större för processorn men inte för lab3
		nop
		addi $t1,$t1, 1
		j for
		nop
	
	j while
	nop
slut:
 POP $s0
 jr $ra
 nop

 		
time2string:
PUSH $s0
PUSH $s1
PUSH $ra


move $s0, $a0 #adress där vi sprar print time
move $s1, $a1 # adress for my time

#första nummret
andi $t1, $s1, 0xf000 #ta första digiten
srl  $a0, $t1, 0x0c # shift 12 steg
jal hexasc
nop
sb $v0, 0($s0)


#andra nummret
andi $t1, $s1,0x0f00
srl  $a0, $t1, 0x8 # shift 8 steg
jal hexasc
nop
sb $v0, 1($s0)

li $t1, 0x3A
sb $t1, 2($s0)

#tredje nummret
andi $t1, $s1, 0x00f0 #denna
srl $a0, $t1, 0x4
jal hexasc
nop
sb $v0, 3($s0)



#fjärde nummret
andi $t1, $s1, 0x000f 
srl $a0, $t1, 0x0
jal hexasc
nop
sb $v0, 4($s0) 


li	$t1, 0x00 #null
sb	$t1, 5($s0) 

 
POP $ra
POP $s1
POP $s0

jr $ra
nop


enable_interrupt:
	ei
	jr $ra
	nop
