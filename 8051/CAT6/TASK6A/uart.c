#include<reg51.h>

void main(void){
	char ch;
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	
	while(1){
		while(RI==0);
		ch=SBUF;
		RI=0;
		
		while(TI==0);
		SBUF=ch;
		TI=0;
	}
}
