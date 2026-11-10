#include<reg51.h>

sbit led = P1^1;
int count = 0;
void main(){
	TMOD = 0x01;
	TH0 = 0xEA;
	TL0 = 0x66;
	TR0 = 1;
	while(1){
		if(TF0 == 1){
			TH0 = 0xEA;
			TL0 = 0x66;
			TF0 = 0;
			count++;
			if(count>133){
				led = !led;
				count = 0;
			}
		}
	}
}