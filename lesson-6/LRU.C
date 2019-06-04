#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ȫ�ֱ���
char stack[5] ={0}; //ջ 
char pages[10] = {'3', '3', '0', '5', '1', '0', '8', '8', '1', '3'}; 

//ʹ�õ��ĺ���
void print_stack();//�����ǰ��stack 
void update_stack(int j, int i);//����ջ 

int main(){
    int i, j, k;
     //ջ��ʼ��Ϊnull 
    for (i=0; i<5; i++) {
        stack[i] = NULL;
    }

    printf("ջ��->ջ��: \n");
    print_stack(); //��ʼջ��ӡ
                                                                                                                                                                                                                                                     
    for (i=0; i<strlen(pages); i++) {//��ȡpages�еļ�¼ 
        for (j=0; j<5; j++) {
            if (stack[j] == NULL) {//ջδ�� ���ͷ���ջ�� 
                stack[j] = pages[i];
                break; 
            }else{//����NULL֮ǰ����������¼��stack֮�� 
            	if (stack[j] == pages[i]) {//ջ������ͬ��¼ 
                	if (j+1 < 5 && stack[j+1] == NULL || j == 4) { //ѭ�������� 
                    	break;
                	}
                	update_stack(j, i); //����ջ 
            	} else if (j == 4 && stack[j] != pages[i]) {//ջ���޷���Ԫ��
                	update_stack(j, i); //����ջ 
            	}
			}
        }
        printf("��ȡ��%cҳ��:\n", pages[i]);
        print_stack();
    }
	return 0;
}

// ��ӡջ 
void print_stack()
{
    int m;
    // ��ӡջԪ��
    for (m=0; m<5; m++) {
        if (stack[m] == NULL) {
            printf("  N");
        } else {
            printf("  %c", stack[m]);
        }
    }
    printf("\n\n");
}

//�ƶ�ջֵ
void update_stack(int j, int i){
    int temp, k;
    temp = stack[j];
    for (k=j; k<4; k++) { //�ƶ�����ջ�����������¼ 
        if (j != 4) {//j==4ʱ��˵��û�ҵ���ͬ�ļ�¼ 
            if (stack[k+1] == NULL) {
                break;
            }
        }
        stack[k] = stack[k+1];
    }
    // ���ֲ�ͬ���ʹ�ò�ͬ��ֵ
    if (j != 4) {
        stack[k] = pages[i]; //�滻����ֵ
    } else {
        stack[4] = pages[i]; //�滻����ֵ
    }
}
