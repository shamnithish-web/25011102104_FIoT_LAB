#include<reg51.h> 

sbit ledpin = P1^3;
sbit ledpin2 = P1^4;
void delay();
void delay2();

void delay(){
	int i,j;
	for(i = 0;i<100;i++){
		for(j =0;j<100;j++){
		}
	}
}

void delay2(){
		int i,j;
	for(i = 0;i<400;i++){
		for(j =0;j<400;j++){
		}
	}
}

void main(){
	while(1){
	ledpin = 1;
	delay();
	ledpin = 0;
	delay();
		ledpin2 = 1;
		delay2();
		ledpin2 = 0;
		delay2();
	}
}