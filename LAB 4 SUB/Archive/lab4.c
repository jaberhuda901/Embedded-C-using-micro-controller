// NAME: JAEBR-UL HUDA STUDENT ID: 101137524
// TEAM MEMBER: HASAN AL-HASOO STUDENT ID: 101196381
// TEAM MEMBER: KAIF ALI STUDENT ID: 101180909

#include "msp.h"

int main(void)
{
    volatile uint32_t i;
		uint8_t sw1;
		uint8_t sw2;
		int led_mode = 0; // if 0 then red_led, if 1 then rgb
		uint8_t RGB_mode = 0x00;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;  // Stop watchdog timer

    // GPIO function
		// Config SWITCH P1.1 and P1.4 as GPIO and also LED as GPIO
		P1SEL0 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0))); 
		P1SEL1 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0)));
		// Config RGB_LED P2.0,P2.1 and P2.2 as GPIO
		P2SEL0 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0))); 
		P2SEL1 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0)));
		// GPIO function
			
		// Set SWITCH P1.1 and P1.4 as input
		P1DIR &=(uint8_t)(~((1<<4) | (1<<1)));
			
		// Set LED P1.0 as output and P2.0,P2.1,P2.2 as output
		P1DIR |=(uint8_t)(((1<<0)));
		P2DIR |=(uint8_t)(((1<<2) | (1<<1) | (1<<0)));
				
		// Configure switches P1.1 and P1.4 as pull-up resistor
		P1REN |=(uint8_t)(~((1<<4) | (1<<1)));

		// P1OUT must be 1 if active low, 0 if active high
		// Setting the LEDs as active high
		P1OUT &=~(uint8_t)(1<<0);
		P2OUT &=~(uint8_t)(((1<<2) | (1<<1) | (1<<0)));

		// Setting switches P1.1 and P1.4 as inputs with pull-up resistors.
		P1OUT |=(uint8_t)((1<<4) | (1<<1));

		// P1REN must be 1 to enable corresponding resistor.
		P1REN |=(uint8_t)((1<<4) | (1<<1));

    while(1)
    {
       //Getting switch values with masking
			sw1 = P1IN & (1<<1);
			sw2 = P1IN & (1<<4);

			if (sw1 == 0) {
				//debouncing

				int t1 = 75000;
				while (t1 > 0) {
					t1--;
				}

				sw1 = P1IN & (1<<1);
				//toggle the red LED if switch is pressed
				if (sw1 == 0) {
					led_mode ^= 1;
				}
			}
		
			// -----------------------------------------

			//debouncing
			if (sw2 == 0) {
	   
				// Delay / debouncing
				int t2 = 75000;
				while (t2 > 0) {
					t2--;
				}
			
				sw2 = P1IN & (1<<4);

				/*
				RGB modes: 000, 001, 010, 011, 100, 101, 110, 111
				Each mode is accessed via RGB_modes integer
				RGB_mode is incremented each pass to switch modes and P2OUT is set to RGB mode
				*/


				if (sw2 == 0) {
					switch (led_mode) {
						case 0:
							P1OUT ^= (1<<0);
							break;
						case 1:
							RGB_mode++;
							if (RGB_mode > 7) {
								RGB_mode = 0;
							}
							P2OUT &= 0x1F<<3;
							P2OUT |= (RGB_mode | 0x1F<<3);
							break;
					
					}
				}
			}
		}
}
