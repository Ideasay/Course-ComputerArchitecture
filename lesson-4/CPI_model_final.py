import random
#初始化以及mips指令所用的指令和寄存器
n = input("输入生成的指令长度：")
print("#####################")
n = int(n)
stall = 0
last_op1,last_op2,last_op3 = '','',''
last_2_op1,last_2_op2,last_2_op3 = '','',''
#codes用来存最后的代码
codes = []
instructions = ['add','addu','sub','subu']
registers = ['$0','$1','$2','$3']

#每一次循环生成前后指令，并计算stall
for i in range(n):
        #随机生成指令
        current_ins = random.choice(instructions)
        op1 = random.choice(registers)
        op2 = random.choice(registers)
        #说明是寄存器指令
        if current_ins == 'add ' or current_ins == 'sub':
                op3 = random.choice(registers)
                current_op = [op1,op2,op3]
        #说明是立即数指令
        else:
                op3 = ''
                current_op = [op1,op2,'1']
        #计算需要的stall
        if last_op1 == op2 or (last_op1 == op3 and op3):
                stall += 2
        if last_2_op1 == op2 or (last_2_op1 == op3 and op3):
                stall += 1
        last_2_op1,last_op1 = last_op1,op1
        last_2_op2,last_op2 = last_op2,op2
        last_2_op3,last_op3 = last_op3,op3

        current_codes = ' '.join([current_ins,','.join(current_op)])
        codes.append(current_codes)
for i in codes:
        print("{0}".format(i))
print("#####################")
print("stall:{0}\tcpi:{1}".format(stall,(stall+n)/n))
        
        
