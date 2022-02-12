/*
 * GccApplication1.c
 *
 * Created: 2/11/2022 11:02:51 PM
 * Author : Jared
 */ 
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>


char str[5] = "";
int d = 0;
int cc = 0;
int b = 0;
int dot = 30;
int dash = 200;
int space = 400;
volatile int c = 0;


void ini(){
	cli();  // Disable Global Interrupts


	DDRB |= (1<<DDB1); // output pin
	DDRB |= (1<<DDB2); // output pin
	
	DDRB |=(1<<DDB5);
	
	DDRB &= ~(1<<DDB0); // input pin

	TCCR1B |= (1<<CS10); //SETTING THE TIMER
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS12);

	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);


	//LOOKING FOR RISING EDGE
	TCCR1B |= (1<<ICES1);


	//CLEAR INTERUPT FLAG
	TIFR1 |= (1<<ICF1);

	//ENABLE INPUT CAPTURE

	TIMSK1 |= (1<<ICIE1);
	TIMSK1 |= (1<<TOIE1);

	

	sei(); // Enable Global Interrupts

	//Serial.begin(4800);
	
	
}



ISR(TIMER1_CAPT_vect){
	if(b==0){ c=0; b=1;}
	else{b=0;}
	//UART_putstringln(" button click");
	cc=c;
	//UART_putstring(cc);

	TCCR1B ^= (1<<ICES1);
	return;
}

ISR(TIMER1_OVF_vect){ c=c+1; d=d+1; return;}


int main (void)
{
	ini();
	UART_init(BAUD_PRESCALER); 

	while(1){
		if( 12 < d){d=0; PORTB &= ~(1<<PORTB1); PORTB &= ~(1<<PORTB2);}
		if( 7 < cc && cc < 50){PORTB |= (1<<PORTB1); cc = 0; strcat(str,".");}
		else if( 50 < cc && cc< 100){ PORTB |= (1<<PORTB2);cc = 0;strcat(str,"-");}
		if(cc > 100){cc = 0;
			if(strcmp(str,".-") == 0){UART_putstring("A"); str[5]="";}
			if(strcmp(str,"-...") == 0){UART_putstring("B");str[5]="";}
			if(strcmp(str,"-.-.") == 0){UART_putstring("C");str[5]="";}
			if(strcmp(str,"-..") == 0){UART_putstring("D");str[5]="";}
			if(strcmp(str,".") == 0){UART_putstring("E");str[5]="";}
			if(strcmp(str,"..-.") == 0){UART_putstring("F");str[5]="";}
			if(strcmp(str,"--.") == 0){UART_putstring("G");str[5]="";}
			if(strcmp(str,"....") == 0){UART_putstring("H");str[5]="";}
			if(strcmp(str,"..") == 0){UART_putstring("I");str[5]="";}
			if(strcmp(str,".---") == 0){UART_putstring("J");str[5]="";}
			if(strcmp(str,"-.-") == 0){UART_putstring("K");str[5]="";}
			if(strcmp(str,".-..") == 0){UART_putstring("L");str[5]="";}
			if(strcmp(str,"--") == 0){UART_putstring("M");str[5]="";}
			if(strcmp(str,"-.") == 0){UART_putstring("N");str[5]="";}
			if(strcmp(str,"---") == 0){UART_putstring("O");str[5]="";}
			if(strcmp(str,".--.") == 0){UART_putstring("P");str[5]="";}
			if(strcmp(str,"--.-") == 0){UART_putstring("Q");str[5]="";}
			if(strcmp(str,".-.") == 0){UART_putstring("R");str[5]="";}
			if(strcmp(str,"...") == 0){UART_putstring("S");str[5]="";}
			if(strcmp(str,"-") == 0){UART_putstring("T");str[5]="";}
			if(strcmp(str,"..-") == 0){UART_putstring("U");str[5]="";}
			if(strcmp(str,"...-") == 0){UART_putstring("V");str[5]="";}
			if(strcmp(str,".--") == 0){UART_putstring("W");str[5]="";}
			if(strcmp(str,"-..-") == 0){UART_putstring("X");str[5]="";}
			if(strcmp(str,"-.--") == 0){UART_putstring("Y");str[5]="";}
			if(strcmp(str,"--..") == 0){UART_putstring("Z");str[5]="";}
			strcpy(str, "");
			
			if(strlen(str) > 5){strcpy(str, "");}
		}
	}

}



