/*
 * AVR_SPI.cpp
 *
 * Created: 1/16/2020 8:15:19 AM
 * Author : MCLEANS
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MOSI_PORT_DIRECTION DDRB
#define SCLK_PORT_DIRECTION DDRB
#define MOSI_PIN PINB5
#define SCLK_PIN PINB3
#define SS_PORT_DIRECTION DDRB
#define SS_PORT PORTB
#define SS_PIN PINB6

void init_spi_master(){
	
	//set MOSI AND SCK to output
	MOSI_PORT_DIRECTION |= (1<<MOSI_PIN);
	SCLK_PORT_DIRECTION |= (1<<SCLK_PIN);
	//Enable master mode
	//set clock frequency to fosc/16
	//Enable the SPI
	SPCR |= (1<<MSTR)|(1<<SPR0)|(1<<SPE);
	
}


int main(void)
{
    /* Replace with your application code */
	init_spi_master();
	DDRD = 0b11111111;
	DDRC = 0b11111111;
	SS_PORT_DIRECTION |= (1<<SS_PIN);
	
	char sent_bytes[5] = {0b10000000,
							0b00110011,
							0b00000000,
							0b11111111,
							0b11100011};
	
	int i = 0;	
	while (1)
	{
		SS_PORT &= ~(1<<SS_PIN);
		PORTD = SPDR = sent_bytes[i];
		while(!(SPSR & (1<< SPIF)));
		SS_PORT |=(1<<SS_PIN);
		i++;
		if(i > 4) i=0;
		_delay_ms(1000);
			
	}
		

}

