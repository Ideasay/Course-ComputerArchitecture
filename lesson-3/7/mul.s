	.data
#�������ʱ�����õ��ַ�
#���������5A286752H��6E12BA98��˽��в���#
$VAR0:	.ascii 	"5A286752H*6E12BA98=\000"
$VAR1:	.ascii	"%x\n\000"
	
	.text
	.globl main
	.ent main
main:
	#��ջ����	
	addiu	$sp,$sp,-32
	sw	$ra,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	#�����"5A286752H*6E12BA98=��
	la	$a0,$VAR0
	jal	printf

	#װ����Ե�����
	li 	$a0,0x5a286752
	li   	$a1,0x6e12ba98
	
	#�����ʼ����ʼ
	#t2������¼��ǰλ����ų�ʼΪ��0λ
	#t3����������ȡ����ǰλ��t1
	#t6��ѭ������������Ϊ32
	move	$t0,$a0
	move	$t1,$a1
	li 	$t2,0
	li 	$t3,31
	li	$t6,32

L2:	move 	$t1,$a1
	subu	$t4,$t3,$t2
	#ȡ��a1��ǰ��t2λ�������ƣ�������.���λΪ1����
	sll	$t1,$t1,$t4
	srl	$t1,$t1,$t3
	#ע�ⶼҪ������Ϊ���ֻ������32λ
	srl	$t5,$t5,1
	beq 	$t1,$0,L3
	#ֻҪȡ���Ľ����Ϊ0�������
	addu	$t5,$t0,$t5

L3:	
	#һ����32λҪ����ֻҪt2������δ��32�ͼ���L2��
	addiu 	$t2,$t2,1
	bltu	$t2,$t6,L2
	#���ڽ�ȡ��32λ������0���൱���ڽ��t5ǰ�Ӹ�0
	srl	$t5,$t5,1
	#�������v0
        move 	$v0,$t5

	#������
	move	$a1,$v0
	la	$a0,$VAR1
	jal	printf
	
	#��ջ�ָ�
	move	$sp,$fp
	lw	$ra,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,40
	j	$ra

	.end	main
