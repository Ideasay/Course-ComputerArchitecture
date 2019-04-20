	.data
VAR0: .ascii "input x:\n\000"
VAR1: .ascii "%d\000"
VAR2: .ascii "the answer is %d\n\000"

	.text
	.global main
	.ent main
main:

addiu $sp,$sp,-64
sw $ra,60($sp)
sw $fp,56($sp)
move $fp,$sp

#a0用来输出
la $a0,VAR0
jal printf

#输入的x放在52($fp)的地方
la $a0,VAR1
addiu $a1,$fp,52
jal __isoc99_scanf

#将输入的x取出来放在a0里面,>=0时候就跑去answer
lw $a0,52($fp)
bge $a0,$zero,answer

sub $a0,$zero,$a0

answer:

move $v0,$a0
la $a0,VAR2
move $a1,$v0
jal printf

move $sp,$fp
lw $fp,56($sp)
lw $ra,60($sp)
addiu $sp,$sp,64
j $ra

	.end main
