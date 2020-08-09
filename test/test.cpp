// // 1:150 RC Car Receiver ATtiny1616 20200509 1700
// #include <avr/io.h>
// #define F_CPU 3333333
// #include <avr/interrupt.h>
// #define pin PORTA.IN
// #define stop TCA0.SINGLE.CMP1L=0;TCA0.SINGLE.CMP2L=0;

// uint8_t ir=0x04,ib,fg,asb=3,str=127,rc=127,cti,ct;
// int8_t dir;
// uint16_t dat;

// //Steering Photo Sensor
// ISR(PORTA_PORT_vect){ 
// 	str+=dir;
// 	if(fg && ((rc>=str && dir==-1)||(rc<=str && dir==1)))	{
// 		stop;
// 		fg=0;
// 		TCD0.CTRLA&=~(1<<0);
// 	}
// 	ct=0; //Timer Reset
// 	PORTA.INTFLAGS|=0b10000000; //PA7:Clear Flag
// }

// void operation(){
// 	PORTA.OUT^=(1<<1); //***
// 	//Steering
// 	if((dat>75)&&(dat<179)){ 
// 		rc=dat;
// 		if((rc<str-asb)||(rc>str+asb)){
// 			//Left
// 			if(rc<str-asb){
// 				TCA0.SINGLE.CMP1L=15;
// 				TCA0.SINGLE.CMP2L=0;
// 				dir=-1;
// 			} 
// 			//Right
// 			if(rc>str+asb){
// 				TCA0.SINGLE.CMP2L=15;
// 				TCA0.SINGLE.CMP1L=0;
// 				dir= 1;
// 			} 
// 			TCD0.CTRLA|=(1<<0);
// 		}
// 		else{
// 			//Left
// 			if(rc<str){
// 				TCA0.SINGLE.CMP1L=10;
// 				TCA0.SINGLE.CMP2L=0;
// 				dir=-1;ct=0;
// 				TCD0.CTRLA|=(1<<0);
// 			} 
// 			//Right
// 			if(rc>str){
// 				TCA0.SINGLE.CMP2L=10;
// 				TCA0.SINGLE.CMP1L=0;
// 				dir=1;
// 				ct=0;
// 				TCD0.CTRLA|=(1<<0);
// 			}
// 		}
// 		fg=1;
// 	}

// 	if((dat>10)&&(dat<31)){ //Forward
// 		TCB1.CCMPH=dat-11;
// 		TCB0.CCMPH=0;
// 	}
// 	if((dat>=0)&&(dat<10)){ //Reverse
// 		TCB1.CCMPH=0;
// 		TCB0.CCMPH=9-dat;
// 	}
// 	if(dat==10){ //Stop
// 		TCB1.CCMPH=0;
// 		TCB0.CCMPH=0;
// 	}
// }

// void infrared(){ //IR Remote Control Receiving

// 	RTC.CNT=0;
// 	while(~pin & ir){} //Leader Check
	
// 	cti=RTC.CNT; //RTC.CNT(1count):0.03msec
// 	if(cti>46 && cti<76){
// 		RTC.CNT=0;
		
// 		while((pin & ir)&&(RTC.CNT<76)){} //Blank Check
		
// 		for(ib=0;ib<16;ib++){
// 			RTC.CNT=0;
			
// 			while(~pin & ir){} //Count Data bit
			
// 			cti=RTC.CNT;
// 			dat<<=1; //dat:Data Code			
// 			if(cti>22){
// 				dat|=1;
// 			}

// 			RTC.CNT=0;
			
// 			while((pin & ir)&&(RTC.CNT<20)){}
// 		}
// 		if((dat>>8)==(0x00FF-(dat & 0x00FF))){
// 			dat>>=8;operation();
// 		} //Data,~Data Check
// 	}
// }

// //Steering Limit Switch
// ISR(TCD0_OVF_vect){ 
// 	ct++;
// 	if(!(ct%23)){
// 		stop;
// 		fg=0;
// 		TCD0.CTRLA&=~(1<<0);

// 		if(dir==-1){str=115;} //Left
// 		if(dir== 1){str=139;} //Right
// 	}
// 	TCD0.INTFLAGS|=0b00000001;
// }

// int main(void){

// 	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB,0b00010001); //Div6, 3333333Hz

// 	PORTA.DIR        =0b00101000; //PA7:Photo Sensor, PA5,3:Drive Motor, PA2:IR
// 	PORTB.DIR        =0b00000110; //PB2,1:Steering Moter
// 	PORTA.PIN7CTRL   =0b00001011; //PA7 Pull up, Falling
// 	PORTA.INTFLAGS   =0b10000000; //PA7 INT Enable

// 	//Steering Motor
// 	TCA0.SINGLE.CTRLA=0b00001111; //Div1024, Enable
// 	TCA0.SINGLE.CTRLB=0b00000110; //Low2,1
// 	TCA0.SINGLE.CTRLD=0b00000001; //Split Mode
// 	TCA0.SINGLE.PERL =81;         // 3333333Hz/Div1024/81=40Hz

// 	//Steering Limit Switch
// 	CPU_CCP          =CCP_IOREG_gc; //Un-protect Protected I/O Registers
// 	TCD0.CMPBCLR     =4000;       // 3333333Hz/Div32/4000=26Hz
// 	while(!(TCD0.STATUS & TCD_ENRDY_bm)){} //Enable Ready
// 	TCD0.CTRLA       =0b01110001; //System Clock, Div32, Enable
// 	TCD0.INTCTRL     =0b00000001; //OVF

// 	//Drive Motor
// 	//Forward(PA3)
// 	TCB1.CTRLA       =0b00000101; //From CLK_TCA, Enable
// 	TCB1.CTRLB       =0b00010111; //CCMPEN, 8bit PWM
// 	TCB1.CCMPL       =40;         // 3333333Hz/Div1024/40=81Hz
// 	//Reverse(PA5)
// 	TCB0.CTRLA       =0b00000101; //From CLK_TCA, Enable
// 	TCB0.CTRLB       =0b00010111; //CCMPEN, 8bit PWM
// 	TCB0.CCMPL       =40;         // 3333333Hz/Div1024/40=81Hz

// 	//Count IR
// 	RTC.CTRLA        =0b00000001; //RTC Enable
// 	RTC.PER          =65535;      //Top Value
// 	sei();

// //--------------------------------------------
// 	while(1){
// 		if(~pin & ir){infrared();}
// 	}
// }//int main