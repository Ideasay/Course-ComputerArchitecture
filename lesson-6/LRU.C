#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局变量
char stack[5] ={0}; //栈 
char pages[10] = {'3', '3', '0', '5', '1', '0', '8', '8', '1', '3'}; 

//使用到的函数
void print_stack();//输出当前的stack 
void update_stack(int j, int i);//更新栈 

int main(){
    int i, j, k;
     //栈初始化为null 
    for (i=0; i<5; i++) {
        stack[i] = NULL;
    }

    printf("栈底->栈顶: \n");
    print_stack(); //初始栈打印
                                                                                                                                                                                                                                                     
    for (i=0; i<strlen(pages); i++) {//读取pages中的记录 
        for (j=0; j<5; j++) {
            if (stack[j] == NULL) {//栈未满 ，就放入栈中 
                stack[j] = pages[i];
                break; 
            }else{//遇到NULL之前，有其他记录在stack之中 
            	if (stack[j] == pages[i]) {//栈内有相同记录 
                	if (j+1 < 5 && stack[j+1] == NULL || j == 4) { //循环到顶部 
                    	break;
                	}
                	update_stack(j, i); //更新栈 
            	} else if (j == 4 && stack[j] != pages[i]) {//栈内无访问元素
                	update_stack(j, i); //更新栈 
            	}
			}
        }
        printf("调取第%c页面:\n", pages[i]);
        print_stack();
    }
	return 0;
}

// 打印栈 
void print_stack()
{
    int m;
    // 打印栈元素
    for (m=0; m<5; m++) {
        if (stack[m] == NULL) {
            printf("  N");
        } else {
            printf("  %c", stack[m]);
        }
    }
    printf("\n\n");
}

//移动栈值
void update_stack(int j, int i){
    int temp, k;
    temp = stack[j];
    for (k=j; k<4; k++) { //移动除了栈顶外的其他记录 
        if (j != 4) {//j==4时，说明没找到相同的记录 
            if (stack[k+1] == NULL) {
                break;
            }
        }
        stack[k] = stack[k+1];
    }
    // 两种不同情况使用不同赋值
    if (j != 4) {
        stack[k] = pages[i]; //替换顶部值
    } else {
        stack[4] = pages[i]; //替换顶部值
    }
}

