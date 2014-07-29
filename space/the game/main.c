/******************************************************************************/
/* This is an application on the MCB1700 board. The UFO is at the bottom      */
/* center of the screen and is moved using the joystick using the left right  */
/* buttons. The UFO can shoot grenades a maximum of three at a time. The INT0 */
/* button is used for the same. The timer0 is used to capture movements.			*/
/******************************************************************************/
#include "GLCD.h"
#include "LPC17xx.h"
#include "KEN_UTILS.h"
#include "type.h"
#include "dac.h"
#include "dma.h"

extern volatile uint32_t DACDMA0Done, DACDMA1Done;
volatile int i, k,x,y,z,l = 0,m = 0,n = 0,q,r,left = 0, right = 0,d,e,f,g ;
int kbd_val;


#define KBD_MASK 0x79

int main (void)
{
		// DAC configuration
		SystemClockUpdate(); 											// updates the SystemFrequency 
		DACInit();

		//Timer0 configuration
		LPC_SC->PCONP |= 1 << 1; 									// Power up Timer 0
		LPC_SC->PCLKSEL0 |= 1 << 2; 							// Clock for timer = CPU Clock
		LPC_TIM0->MR0 = 1 << 22;
		LPC_TIM0->MCR |= 1 << 0;									// Interrupt on Match 0 compare
		LPC_TIM0->MCR |= 1 << 1; 									// Reset timer on Match 0
		LPC_TIM0->TCR |= 1 << 1; 									// Manually Reset Timer 0 
		LPC_TIM0->TCR &= ~(1 << 1); 							// Stop resetting the timer
		NVIC_EnableIRQ(TIMER0_IRQn); 							// Enable timer interrupt;
		LPC_TIM0->TCR |= 1 << 0; 									// Start timer
	
		//GPIO
		LPC_SC->PCONP |= ( 1 << 15 ); 						// Power up GPIO
	
		//INT0
		LPC_PINCON->PINSEL4 = 0x00100000;					// set P2.10 as EINT0 and
		LPC_GPIOINT->IO2IntEnF = 0x200;						// Port2.10 is falling edge.
		LPC_SC->EXTMODE = 0x00000001;							// INT0 edge trigger
		LPC_SC->EXTPOLAR = 0;											// INT0 is falling edge 
		NVIC_EnableIRQ(EINT0_IRQn); 							// Enable sourcesof interrupt

		//LCD
		GLCD_Init();                             	// Initialize graphical LCD
		GLCD_Clear(Black); 												// Clear graphical LCD display

		//Joystick
		LPC_PINCON->PINSEL3 &= ~((3<< 8)|(3<<14)|(3<<16)|(3<<18)|(3<<20));
		// P1.20, P1.23, …, P1.26 are GPIO (Joystick)
		LPC_GPIO1->FIODIR &= ~((1<<20)|(1<<23)|(1<<24)|(1<<25)|(1<<26));
		// P1.20, P1.23, ..., P1.26 are input (Joystick)

		// Initial UFO drawn
		q = 160;  																// X coordinate
		r = 210; 																	// Y coordinate
		KEN_draw_UFO( q, r);
		
		/**************************************************************************************/
		/* Inside the while we will check for all the flags corresponding to the joystick 		*/
		/* buttons and grenades. When the UFO position has to be changed we call the UFO right*/ 
		/* and UFO left function and reset the flag and change the global variable which store*/
		/* the central coordinate for the UFO.																								*/
		/* The grenades are moved inside the while loop. Each pass of the while loop changes 	*/
		/* the position of all the grenades which are active by one which is by 5 pixels.     */
		/* The three grenades have 3 vertical movement coordinates which are reset once the   */
		/* grenade moves to the top.  Also once the grenade moves to the top we reset grenade	*/ 
		/* flag and the captured UFO horizontal position.                                   	*/
		/**************************************************************************************/
		while (1){																// Infinite loop
			
				//check if anything needs to be done at all
				while( l == 1 | m == 1 | n == 1 | left == 1 | right == 1){			
					
						if ( right == 1){										// if the joystick right button 
								right = 0;                      // Reset the right flag
								if ( q <= 310){             		// reached right most point
										KEN_draw_UFORIGHT( q, r);		// Move UFO by one position
										q = q + 5;                 	// Update the position
								}
						}	
							
						if ( left == 1){										// if the joystick left button 
								left = 0;                       // Reset the left flag
								if( q >= 5){                		// reached  most left point
										KEN_draw_UFOLEFT( q, r);		// Move UFO by one position
										q = q - 5;                	// Update the position
								}
						}
						
						if ( l == 1){												// if grenade L is active
								KEN_draw_grenadeM(d,190-y);    	// Redraw one instance of grenade
								y+= 5;                         	// Update the position
						}
						
						if ( m == 1){												// if grenade M is active
								KEN_draw_grenadeM(e,190-z);   	// Redraw one instance of grenade
								z+= 5;                        	// Update the position
						}
						
						if ( n == 1){												// if grenade N is active
								KEN_draw_grenadeM(f,190-x);   	// Redraw one instance of grenade
								x+= 5;                        	// Update the position
						}
						
						if( y >= 190 | z >= 190 | x >= 190){// check if grenades reached the top
								if( y >= 190 ){									// if grenade L has reached the top
										GLCD_SetTextColor(Black); 	// Clear the grenade
										KEN_draw_grenade(d,0);      // with colour black
										y = 0;                    	// reset the vertical counter
										l = 0;                    	// Reset the grenade flag
										d = 0;                    	// reset UFO position capture
								}
								
								if( z >= 190 ){									// if grenade M has reached the top
										GLCD_SetTextColor(Black); 	// Clear the grenade
										KEN_draw_grenade(e,0);			// with colour black
										z = 0;                    	// reset the vertical counter
										m = 0;                    	// Reset the grenade flag
										e = 0;                  		// reset UFO position capture
								}
								
								if( x >= 190 ){									// if grenade N has reached the top
										GLCD_SetTextColor(Black);		// Clear the grenade
										KEN_draw_grenade(f,0);			// with colour black
										x = 0;                  		// reset the vertical counter
										n = 0;                   		// Reset the grenade flag
										f = 0;          						// reset UFO position capture
								}
						}	
				}
		}
}
/************************************************************************************/
/* The joystick button is checked in the timer 0 interrupt function. First the 			*/
/* timer is reset. Next we check the FIOPIN register to check the value of pins 		*/
/* corresponding to the right and left of joystick. If right button is pressed 			*/
/* we set the right flag and if left button is pressed we set the left flag.  			*/
/* The sound function is also called.																								*/
/************************************************************************************/
void TIMER0_IRQHandler(void){

		// IR is "Interrupt Register".
    if ( (LPC_TIM0->IR & 0x01) == 0x01 ){ 	// if MR0 interrupt 
				LPC_TIM0->IR |= 1 << 0; 						// Clear MR0 interrupt flag 
        LPC_GPIO1->FIOPIN ^= 1 << 29; 			// Toggle the LED 
			kbd_val = ~(LPC_GPIO1->FIOPIN >> 20) & KBD_MASK;

					if ( kbd_val == 0x10	){  					// check if joystick right button is hit
							right = 1 ;         						// right movement flag
							sound(1000);        						// sound function
							kbd_val = 0;										// reset 
					}
					if ( kbd_val == 0x40	){  					// check if joystick left button is hit
							left = 1;           						// left movement flag
							sound(1000);        						// sound function
							kbd_val = 0;										// reset 
					}
    }
}	
/****************************************************************************************/ 
/*When the INT0 external interrupt occurs because of the pressing of INT0 button    		*/
/*the function EINT0_IRQHandler (void) is called. 																			*/
/*First we clear the interrupt by making LPC_SC->EXTINT = 1.														*/
/*Here we check the current status of grenades. We have three grenades and they have a	*/ 
/*corresponding flag "L","M","N". For example if L = 1 means that L grenade is currently*/
/*active.																																								*/
/*We decide to launch a new grenade based on the logic table below.   									*/
/*L	M	N	Launch																																					*/
/*0	0	0	L																																								*/
/*0	0	1	L																																								*/
/*0	1	0	N																																								*/
/*0	1	1	L																																								*/
/*1	0	0	M																																								*/
/*1	0	1	M																																								*/
/*1	1	0	N																																								*/
/*1	1	1	NO launch																																				*/
/*Here for example if L = 1 and M = 1 and N = 0 . It means that grenade L and M are 		*/
/*currently active and grenade N is not. Hence we launce grenade N be making the flag 	*/
/*N = 1. If all the grenades L,M and N are active then no grenade is launched.					*/
/*At the same time we capture the X coordinate of the UFO and pass it on to a variable	*/
/*corresponding to the grenade L,M and N depending on which grenade is being launched. 	*/
/*The sound function is also called when we a grenade is launched.  The grenade is 			*/
/*initially drawn using the function KEN_draw_grenade(int x, int y);  									*/  
/****************************************************************************************/
void EINT0_IRQHandler (void)
{
		LPC_SC->EXTINT = 1;											/* clear interrupt */
		if ( l == 0 & m == 0 & n == 0){
        l = 1;                      				// launch grenade by making flag =1
        d = q;                      				// save the UFO x coordinate  for grenade
        sound(10000);               				// sound function
			GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(d,190);    				// Draw grenade initially
			
		}

    else if ( l == 0 & m == 0 & n == 1){
        l = 1;                      				// launch grenade by making flag =1
        d = q;                      				// save the UFO x coordinate  for grenade
        sound(10000);               				// sound function
		GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(d,190);    				// Draw grenade initially
		}

    else if ( l == 0 & m == 1 & n == 0){
        n = 1;                      				// launch grenade by making flag =1
        f = q;                      				// save the UFO x coordinate  for grenade
        KEN_draw_grenade(f,190);    				// Draw grenade initially
		GLCD_SetTextColor(Magenta);
        sound(10000);               				// sound function
		}

    else if ( l == 0 & m == 1 & n == 1){
        l = 1;                      				// launch grenade by making flag =1
        d = q;                      				// save the UFO x coordinate e for grenade
		GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(d,190);    				// Draw grenade initially
        sound(10000);               				// sound function
    }

    else if ( l == 1 & m == 0 & n == 0){
        m =  1;                     				// launch grenade by making flag =1
        e = q;                      				// save the UFO x coordinate  for grenade
		GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(e,190);    				// Draw grenade initially
        sound(10000);               				// sound function
    }

    else if ( l == 1 & m == 0 & n == 1){
        m =  1;                     				// launch grenade by making flag =1
        e = q;                      				// save the UFO x coordinate for grenade
		GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(e,190);    				// Draw grenade initially
        sound(10000);               				// sound function
		}

    else if ( l == 1 & m == 1 & n == 0){
        n = 1;                      				// launch grenade by making flag =1
        f = q;                      				// save the UFO x coordinate for grenade
        sound(10000);               				// sound function
		GLCD_SetTextColor(Magenta);
        KEN_draw_grenade(f,190);    				// Draw grenade initially
		}

    else if ( l == 1 & m == 1 & n == 1){
        // since all the grenades are active no new grenade to be launched
    }
}
/************************************************************************************/
/* The function is used to generate sound using DAC                                 */
/************************************************************************************/
void sound (int x0){
		while(x0){
        x0--;
        LPC_DAC->DACR = (i << 6) | DAC_BIAS; // Digital value to be converted
        i++;
        for(g = 10000; m > 1; m--);
        if ( i == DATA_LENGTH ){
            i = 0;
        }
		}	
}
