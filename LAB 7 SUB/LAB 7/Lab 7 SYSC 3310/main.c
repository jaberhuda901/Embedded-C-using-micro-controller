#include "msp.h"

int led_mode = 0; // if 0 then red_led, if 1 then rgb
uint8_t RGB_mode = 0x00;

// Timer Intrupt handeler 
void TA0_N_IRQHandler(void) {
	
	//clear interrupt flag
	TA0CTL &= (uint16_t)(~(1<<0));
	P1OUT ^= (uint8_t)(1<<0);
}

void TA1_0_IRQHandler(void) {
	
		TA1CCTL0 &= (uint16_t)(~(1<<0));

			RGB_mode++;
			if (RGB_mode > 7) {
				RGB_mode = 0;
			}
			P2OUT &= 0x1F<<3;
			P2OUT |= (RGB_mode | 0x1F<<3);
}

void TA1_N_IRQHandler(void) {
	
		TA1CTL &= (uint16_t)(~(1<<0));

			RGB_mode++;
			if (RGB_mode > 7) {
				RGB_mode = 0;
			}
			P2OUT &= 0x1F<<3;
			P2OUT |= (RGB_mode | 0x1F<<3);
}
		


int main() {
	
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;  
	
	// GPIO function
	// Config SWITCH P1.1 and P1.4 as GPIO and also LED as GPIO
	P1SEL0 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0))); 
	P1SEL1 &=(uint8_t)(~((1<<4) | (1<<1) | (1<<0)));
	// Config RGB_LED P2.0,P2.1 and P2.2 as GPIO
	P2SEL0 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0) | (1<<4))); 
	P2SEL1 &=(uint8_t)(~((1<<2) | (1<<1) | (1<<0) | (1<<4)));
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
	
	P1IN |= (uint8_t)((1<<4)|(1<<1));
	P1IES |= (uint8_t)((1<<4)|(1<<1));
	P1IFG &= (uint8_t)~((1<<4)|(1<<1));
	P1IE |= (uint8_t)((1<<4)|(1<<1));
	
	P1OUT &=~(uint8_t)(1<<0);
	P2OUT &=~(uint8_t)(((1<<2) | (1<<1) | (1<<0)));

	//TimerA0 configuration
	TA0CTL &= (uint16_t)(~((1<<5) | (1<<4))); //stop timer
	TA0CTL &= ~((uint16_t)((1<<9))); // select clock 32.768kHz ACLK
	TA0CTL |= (uint16_t)((1<<8)); // select clock 32.768kHz ACLK
	TA0CTL &= (uint16_t)(~(1<<0)); //clear interrupt flag (TAIFG) TA0CCR0 = (uint16_t)(99); //100-1
	TA0CCR0 = (uint16_t)(32767); // every 1 second ccr0 = 32768
	TA0CTL |= (uint16_t)((1<<1)); //interrupt enable (TAIE) TA0CTL |= (uint16_t)((1<<4)); //up mode (count to CCR0)	
	TA0CTL |= (uint16_t)((1<<4)); //up mode (count to CCR0)
	
	//TimerA1 configuration
	TA1CTL &= (uint16_t)(~((1<<5) | (1<<4))); //stop timer
	TA1CTL &= ~((uint16_t)((1<<9))); // select clock 32.768kHz ACLK
	TA1CTL |= (uint16_t)((1<<8)); // select clock 32.768kHz ACLK
	TA1CTL &= (uint16_t)(~(1<<0)); //clear interrupt flag for the N handerler
	TA1CCR0 = (uint16_t)(16384); // every 0.5 second ccr0 = 16384
	TA1CTL |= (uint16_t)((1<<1)); //interrupt enable 	
	TA1CCTL0 |= (uint16_t)((1<<4)); // interrupt enable for the 
	TA1CTL |= (uint16_t)((1<<4)); //up/down mode (count to CCR0)
	TA1CTL |= (uint16_t)((1<<5));
	// Not start count from 0
	TA1R = (uint16_t)(13107);

	// enable TimerA interrupt in NVIC
	NVIC_SetPriority(TA0_N_IRQn, 3);
	NVIC_ClearPendingIRQ(TA0_N_IRQn);
	NVIC_EnableIRQ(TA0_N_IRQn);
	
	NVIC_SetPriority(TA1_N_IRQn, 3);
	NVIC_ClearPendingIRQ(TA1_N_IRQn);
	NVIC_EnableIRQ(TA1_N_IRQn);
	
	NVIC_SetPriority(TA1_0_IRQn, 3);
	NVIC_ClearPendingIRQ(TA1_0_IRQn);
	NVIC_EnableIRQ(TA1_0_IRQn);
	
	TA0R = (uint16_t)(32767);
	
	while(1) {
	}
}