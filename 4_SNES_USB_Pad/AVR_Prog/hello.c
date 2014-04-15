#include <avr/io.h>

#define F_CPU 16000000UL  // 1 MHz
#include <util/delay.h>

int main(void)
{
    DDRD |= _BV(PD5); //PD2 zum Ausgang machen (=LED ganz links)
   
    //blink, blink:
    while (1){
        PORTD &= ~_BV(PD5);     //PD2 = low -> LED an
        _delay_ms(100);         //250 ms warten
        PORTD |= _BV(PD5);      //PD2 = high -> LED aus
        _delay_ms(100);         //250 ms warten
    }
   
   
return 0;
}