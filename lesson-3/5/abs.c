#include<stdio.h>

int main(){
	int x;
	printf("input x:\n"); 
	scanf("%d",&x);
	if(x >= 0){
	}else{
		x = -x;
	}
	printf("the answer is %d",x);
} 
