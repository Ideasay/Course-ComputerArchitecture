	.text
	.globl	gcd
	.ent	gcd
	#===========gcd����===========#
gcd:
	#��ջ����
	addiu	$sp,$sp,-32
	sw	$ra,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	
	#a0��a,a1��b
	sw	$a0,32($fp)
	sw	$a1,36($fp)
	lw	$v0,36($fp)
	#��b������0ʱ��,��ת��L2��ע�⿼���ӳٲ�
	bne	$v0,$0,$L2
	nop
	#����v0����a,����gcd����v0����
	lw	$v0,32($fp)
	b	$L3

$L2:
	#b!=0,b�ŵ�v0
	lw	$v1,32($fp)
	lw	$v0,36($fp)
	teq	$v0,$0,7
	#��mod
	div	$0,$v1,$v0
	mfhi	$v0
	#b��a0,mod��a1
	move	$a1,$v0
	lw	$a0,36($fp)
	#�ݹ����gcd
	jal	gcd

$L3:	#�ָ��ֳ�
	move	$sp,$fp
	lw	$ra,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$ra
	.end	gcd
	#===========main��������===========#
	.data
#�������������õ�ascii
$VAR0:	.ascii	"%d%d\000"
$VAR1:	.ascii	"%d\n\000"
	
	.text
	.globl	main
	.ent	main
	
main:
	#��ջ����
	addiu	$sp,$sp,-40
	sw	$ra,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	
	#����
	addiu	$v0,$fp,28
	move	$a2,$v0
	addiu	$v0,$fp,24
	move	$a1,$v0
	la	$a0,$VAR0
	jal	__isoc99_scanf

	#����ɹ������gcd����
	lw	$v0,24($fp)
	lw	$v1,28($fp)
	move	$a1,$v1
	move	$a0,$v0
	jal	gcd

	#���
	move	$a1,$v0
	la	$a0,$VAR1
	jal	printf
	
	#��ջ����
	move	$sp,$fp
	lw	$ra,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$ra
	
	.end	main
