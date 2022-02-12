#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>


#define F_CPU 16000000UL




volatile int edge = 0;
volatile int period = 0;

void ini(){
	cli();  // Disable Global Interrupts
	
	DDRB |=(1<<DDB5);
	
	DDRB &= ~(1<<DDB0); // input pin

	TCCR1B &= ~(1<<CS10); //SETTING THE TIMER
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS12);

	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);


	
	TCCR1B &= ~(1<<ICES1);


	//CLEAR INTERUPT FLAG
	TIFR1 |= (1<<ICF1);

	//ENABLE INPUT CAPTURE

	TIMSK1 |= (1<<ICIE1);

	

	sei(); // Enable Global Interrupts

	
	
	
}



ISR(TIMER1_CAPT_vect){
	
	PORTB ^= (1<<PORTB5);
	_delay_ms(40); //debounce
	TCCR1B ^= (1<<ICES1);
	return;

}




int main (void)
{

	ini();

	while(1){

	}


}