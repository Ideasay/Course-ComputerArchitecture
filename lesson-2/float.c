/*data 
	positive:
	num_1 = 27.00
    num_1.e = 0x05;
	num_1.m = 0x6C;
	
	num2 = 3.15625
	num_2.e = 0x02;
	num_2.m = 0x65;
	
	negative:
	num_1 = 27.00
    num_1.e = 0x05;
	num_1.m = 0x6C;
	
	num2 = -3.15625
	num_2.e = 0x02;
	num_2.m = 0xE5;
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct tagMyFloat{
	signed char m;
	signed char e;
}MyFloat; 

//求阶码函数 
int conver(signed char e); 
int trans_E(signed char m);
//求尾数函数 
float conver_t(signed char m);
float trans_M(signed char m);
//求比x大的最小2的幂次数 
int nextpow(int x);

int main(){
	float num_1_re= 27.0;
	float num_2_re = -3.15625;
	
	MyFloat num_1,num_2;
	num_1.e = 0x05;
	num_1.m = 0x6C;
	num_2.e = 0x02;
	num_2.m = 0xE5;
	
	int  E_1,E_2;
	float  M_1,M_2;
	
	E_1 = trans_E(num_1.e);
	E_2 = trans_E(num_2.e);
	M_1 = trans_M(num_1.m);
	M_2 = trans_M(num_2.m);
	printf("\nM1:%lf\tE1:%d",M_1,E_1);
	printf("\nM2:%lf\tE2:%d",M_2,E_2);
	//////////////////add///////////////////////////////
	printf("\n***************** add *****************\n");
	float M_add; int E_add;
	M_add = M_1*pow(2,E_1-E_2)+M_2;
	E_add = E_2;
	//进行对阶和规格化
	if(fabs(M_add)<0.5||fabs(M_add)>1){
		int M_a = (int)M_add + 1;
		int pow = nextpow(M_a);
		int E_t=0;
		M_add = M_add/pow;
		for(;pow>1;){
			pow=pow/2;
			E_t = E_t + 1;
		}
		E_add = E_add + E_t; 
	} 
	printf("add:\nmantissa:%f\texponent:%d\n",M_add,E_add);
	printf("最终结果为%f,利用编程语言浮点数计算结果为%f\n",M_add*pow(2,E_add),num_1_re+num_2_re);
	
	////////////////////sub////////////////////////////
	printf("\n***************** sub *****************\n");
	float M_sub; int E_sub;
	M_sub = M_1*pow(2,E_1-E_2)-M_2;
	E_sub = E_2;
	//进行对阶和规格化
	if(fabs(M_sub)<0.5||fabs(M_sub)>1){
		int M_s = (int)M_sub + 1;
		int pow_s = nextpow(M_s);
		int E_ts=0;
		M_sub = M_sub/pow_s;
		for(;pow_s>1;){
			pow_s=pow_s/2;
			E_ts = E_ts + 1;
		}
		E_sub = E_sub + E_ts;
	} 
	printf("sub:\nmantissa:%f\texponent:%d\n",M_sub,E_sub);
	printf("最终结果为%f,利用编程语言浮点数计算结果为%f\n",M_sub*pow(2,E_sub),num_1_re-num_2_re);
	
	/////////////////multi////////////////////////
	printf("\n***************** multi *****************\n");
	float M_mul; int E_mul;
	M_mul = M_1*M_2;
	E_mul = E_1+E_2;
	//进行对阶和规格化
	if(fabs(M_mul)<0.5||fabs(M_mul)>1){
		int M_m = (int)M_mul + 1;
		int pow_m = nextpow(M_m);
		int E_tm=0;
		M_mul = M_mul/pow_m;
		for(;pow_m>1;){
			pow_m=pow_m/2;
			E_tm = E_tm + 1;
		}
		E_mul = E_mul + E_tm;
	} 
	printf("\nmul:\nmantissa:%f\texponent:%d\n",M_mul,E_mul);
	printf("最终结果为%f,利用编程语言浮点数计算结果为%f\n",M_mul*pow(2,E_mul),num_1_re*num_2_re);
	
	///////////////div//////////////////////
	printf("\n***************** div *****************\n");
	float M_div; int E_div;
	M_div = (double)M_1/(double)M_2;
	E_div = E_1-E_2;
	//进行对阶和规格化
	if(fabs(M_div)<0.5||fabs(M_div)>1){
		int M_d = (int)M_div + 1;
		int pow_d = nextpow(M_d);
		int E_td=0;
		M_div = M_div/pow_d;
		for(;pow_d>1;){
			pow_d=pow_d/2;
			E_td = E_td + 1;
		}
		E_div = E_div + E_td;
	} 
	printf("div:\nmantissa:%f\texponent:%d\n",M_div,E_div);
	printf("最终结果为%f,利用编程语言浮点数计算结果为%f\n",M_div*pow(2,E_div),num_1_re/num_2_re);
}



int conver(signed char e){
	char arr[2],arr_t[2];
	itoa(e,arr,16);
	//printf("%s\t",arr);
	strncpy(arr_t, strrev(arr),2);
	//printf("%s",arr_t);
	int i,j=0,sum=0,n=2;
	int num[2];
	for(i=0;i<n;i++)
	{
		switch(arr_t[i])
		{
			case 'a':num[j++]=10;
					 break;
			case 'b':num[j++]=11;
					 break;
			case 'c':num[j++]=12;
					 break;
			case 'd':num[j++]=13;
					 break;
			case 'e':num[j++]=14;
					 break;
			case 'f':num[j++]=15;
					 break;	 
			default:num[j++]=(int)(arr_t[i]-'0');
					break;
		}
	}
	for(i=0;i<n;i++){
		if(num[i]<0){
			num[i] = 0;
		}
	}
	//printf("%d\t%d\n",num[1],num[0]);
	sum = num[1]*16+num[0];
	return sum;
}

int trans_E(signed char e){
	//printf("%d\n",conver(m));
	int e_dec;
	if(conver(e)>=128){
		e_dec = -conver(e)+128;
	}else{
		e_dec = conver(e);		
	}
	return e_dec;
}

float conver_t(signed char m){
	char arr[2],arr_t[2];
	itoa(m,arr,16);
	//printf("%s\t",arr);
	strncpy(arr_t, strrev(arr),2);
	//printf("%s",arr_t);
	int i,j=0,n=2;
	float sum = 0;
	float num[2];
	for(i=0;i<n;i++)
	{
		switch(arr_t[i])
		{
			case 'a':num[j++]=0.625;
					 break;
			case 'b':num[j++]=0.6875;
					 break;
			case 'c':num[j++]=0.75;
					 break;
			case 'd':num[j++]=0.8125;
					 break;
			case 'e':num[j++]=0.875;
					 break;
			case 'f':num[j++]=0.875;
					 break;
			case '1':num[j++]=0.9375;
					break;
			case '2':num[j++]=0.125;
					break;
			case '3':num[j++]=0.1875;
					break;
			case '4':num[j++]=0.25;
					break;
			case '5':num[j++]=0.3125;
					break;
			case '6':num[j++]=0.375;
					break;
			case '7':num[j++]=0.4375;
					break;
			case '8':num[j++]=0.5;
					break;
			case '9':num[j++]=0.5625;
					break;
			default:num[j++]=0;
					break;
		}
	}
	for(i=0;i<n;i++){
		if(num[i]<0){
			num[i] = 0;
		}
	}
	//printf("%d\t%d\n",num[1],num[0]);
	sum = num[1]*2+num[0]/8;
	return sum;
}

float trans_M(signed char m){
	float m_dec;
	if(conver(m)>=128){
		m = m - 0x80;
		m_dec = -conver_t(m);
	}else{
		m_dec = conver_t(m);		
	}
	return m_dec;
}

int h(int x){
    return x >> 1 ? h(x >> 1) << 1 : 1;
}
 
int nextpow(int x){
    int y = h(x);
    return x > y ? y << 1 : y;
}
