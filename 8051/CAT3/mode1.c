#include<reg51.h>

sbit ledpin1= P1^7;
sbit ledpin2= P1^6;
sbit ledpin3= P1^5;
sbit ledpin4= P1^4;
sbit sw1= P2^5;
sbit sw2= P2^0;


void delay(){
	int i,j;
	for(i=0;i<200;i++){
		for(j=0;j<200;j++){
			
		}
	}
}

int check(){
	sw1=0;
	if(sw2==0){
		return 1;
	}
	else{
		return 0;
	}
}


void main(){
	while(1){
		int find=check();
		if(find==1){
			ledpin1=1;
			ledpin2=0;
			ledpin3=0;
			ledpin4=0;
			delay();
			ledpin1=0;
			ledpin2=1;
			ledpin3=0;
			ledpin4=0;
			delay();
			ledpin1=0;
			ledpin2=0;
			ledpin3=1;
			ledpin4=0;
			delay();
			ledpin1=0;
			ledpin2=0;
			ledpin3=0;
			ledpin4=1;
			delay();
		}
	}
}

