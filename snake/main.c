/************************************************************************************/
/* This is the snake program - assignment 4                                         */
/************************************************************************************/
#include "GLCD.h"
#include "LPC17xx.h"
#include "UTILITIES.h"
#include "type.h"
#include "uart.h"
#include "dac.h"
#include <stdlib.h>
#include <stdio.h>


volatile int x0,x1,x2,y0,y1,y2;
volatile int bdirec,direc;
volatile int j ,k;
volatile int life,lifegainer,points;
volatile int kbd_val, a[1000][3],level = 0,randomnumber;
volatile int  i ,t = 5, m = 0, g;
char text[5];
extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];
unsigned char val_Tx;


#define KBD_MASK 0x79


int main (void){
		/* Initialize DAC, LCD, Joystick,Timer*********************************************/
		Initialize(); 														
	
	
		/* The user is first asked to enter the level**************************************/
		GLCD_SetTextColor(Green);                      // Text color
		GLCD_SetBackColor(Black);                      // Background colorlor
		GLCD_DisplayString(5, 3, 1,"ENTER LEVEL 1-9"); // Prompt for level
		while(level == 0){ 												     // Wait for the user to enter level
				randomnumber++;													   // To generate random number
				Keychecklevel();   											   // Check for keys 1 - 9                           
		}
		sprintf(text, "%01X", level);							     // Display the level entered
		GLCD_DisplayString(6, 9, 1, (uint8_t*)text);   // Display 
		for ( i = 0 ; i <1000000 ; i++);					     // Delay
	
	
		/* Provide initial values to variables**********************************************/
		GLCD_Clear(Black); 											     		// Clear graphical LCD display
		lifegainer = 0;                           			// Bonus life on 3 mouse variable
		life = 3;                                 			// Number of lives
		points = 0;                               			// Length of snake
		x0 = 165;	                           						// Staring X corsinate of snake
		y0 = 121;																				// Staring Y corsinate of snake
		x1 = x0;																				// Staring X corsinate of tail
		y1 = y0;																				// Staring Y corsinate of tail
		direc = 3;																			// Direction of snake head
		bdirec = 3;																			// Direction of snake tail
		j=0;                                            // Array index for head
		k=0;                                            // Array index for tail
	
	
		/* Get the screen ready*************************************************************/
		Draw_boundary();                                // Draw boundary
		Topdisplay(); 																	// Display level and life
		Draw_initialmouse();                            // Display moouse at random loc
	
	
		/* Continous loop till the game gets over*******************************************/
		while(!(life == 5 | life == 0)){
				GLCD_SetTextColor(Red);                       
				Draw_element(x0 , y0, t );                  // Draw snake head
				sound(100);                                 // Sound  


				/* Below is the logic for mouse************************************************/
				if ( x0 == x2 & y0 == y2){               	  // If mouse position is head position          
						points++;                               // Increment length of snake
						lifegainer++;                           // Counter for 3 continous mouse 
						i = 0;
						GLCD_SetTextColor(Magenta);
						GLCD_SetBackColor(Black);
						while( i < lifegainer){             	  //Clear display status of life gainer
								Draw_element(154+i*11, 10, t );
								i++;
						}	
			
			
						/*Increment life is lifegainer is 3******************************************/
						if(lifegainer == 3){                         
								life++;
								sound(20000);
								Topdisplay();
								i = 0;
								while( i < lifegainer){
										GLCD_SetTextColor(Black);
										Draw_element(154+i*11, 10, t );
										i++;
								}
						lifegainer = 0;
						}
			
			
						/* Increment the length of the snake tail***************************************/
						if ( bdirec == 1){     									// Tail direction is left
								x1 = x1 + (2*t+1);
						}
						else if ( bdirec == 2){ 								// Tail direction is right
								x1 = x1 - (2*t+1);
						}	
						else if ( bdirec == 3){ 								// Tail direction is up
								y1 = y1 + (2*t+1);
						}
						else if ( bdirec == 4){ 								// Tail direction is down
								y1 = y1 - (2*t+1);
						}		
			
			
						/* Generate new mouse*****************************************************************/
						x2 = (2*t+1)*((rand()+randomnumber)%26+2);
						y2 = (2*t+1)*((rand()+randomnumber)%18+3);	
						GLCD_SetTextColor(Green);
						Draw_element(x2 , y2,t);	
				}
				else{
						GLCD_SetTextColor(Green);
						Draw_element(x2 , y2,t);
				}
	
	
				/* Check if the snake has hit the boundary**************************************/
				if (hitboundary()){
						life--;          											   //Reduce life
						sound(10000);
			
			
						/* Reset various variable****************************************************/
						Draw_boundary();
						GLCD_SetBackColor(Black);
						GLCD_Bargraph (17, 28, 286, 198, 0);
						Topdisplay(); //Display level and life
						Draw_initialmouse();
						x0 = 165;	
						y0 = 121;
						x1 = x0;
						y1 = y0 + (2*t+1)* points;
						j = 0;
						k = 0;
						a[0][0] = 0;
						a[0][1] = 0;
						a[0][2] = 0;
						direc = 3;
						bdirec = 3;
						lifegainer = 0;
						GLCD_SetTextColor(Red);
						Draw_element(x0 , y0, t );	
				}
		
			
				/* Increment the position of the head based on snake direction******************/
				if ( direc == 1){ 													// If head directionleft	
						x0 = x0 - (2*t+1);
				}
				else if ( direc == 2){ 											// If head directionright
						x0 = x0 + (2*t+1);
				}
				else if ( direc == 3){ 											// If head directionup
						y0 = y0 - (2*t+1);
				}
				else if ( direc == 4){ 											// If head direction down
						y0 = y0 + (2*t+1);
				}
		
		
				/* Provide delay corresponding to the level*************************************/
				for ( i = 0 ; i <1000000/(level+1) ; i++);
		
		
				/* Draw the tail block if within boundary lines*********************************/
				if( x1 >= 2*(2*t + 1) & y1 >= 3*(2*t + 1) & x1 <= 27*(2*t + 1) & y1 <= 20 * (2*t + 1)){
						GLCD_SetTextColor(Black);
						Draw_element(x1 , y1,t);
				}				
		
				
				/* Check if the tail has reached the bending of the snake***********************/ 
				if ( x1 == a[j][0] & y1 == a[j][1]){
						bdirec = a[j][2];                           // Change direction accordingly for tail
						j++;
						if ( j == 999){
								j = 0;
						}
				}	
		
		
				/* Increment the tail block corresponding to the direction of the tail**********/
				if ( bdirec == 1){                          // If tail direction is left
						x1 = x1 - (2*t+1);
				}
				else if ( bdirec == 2){ 										// If tail direction is right
						x1 = x1 + (2*t+1);
				}
				else if ( bdirec == 3){ 										// If tail direction is up
						y1 = y1 - (2*t+1);
				}
				else if ( bdirec == 4){ 										// If tail direction is down 
						y1 = y1 + (2*t+1);
				}
		
		
				/* Check if any key from jeyboard to chnage direction of snake has beeen hit****/ 
				Keycheckarrow();
		}	                                          		// End of while loop
	
	
		/* Display that you have lost if life is zero***************************************/
		if ( life == 0) {
				GLCD_Clear(Black); 													// Clear graphical LCD display
				GLCD_SetTextColor(Red);
				GLCD_SetBackColor(Black);
				GLCD_DisplayString(5, 6, 1, "YOU LOSE");
		}
	
	
		/* Display that you have won if life is 5*******************************************/
		else if ( life == 5){
				GLCD_Clear(Black); 													// Clear graphical LCD display
				GLCD_SetTextColor(Green);
				GLCD_SetBackColor(Black);
				GLCD_DisplayString(5, 6, 1, "YOU WIN");
		}
}	                                            			// End of main function


/***************************************************************************************/
/* Is used to change the level of the game real time                                   */
/***************************************************************************************/
void TIMER0_IRQHandler(void){

	
		// IR is "Interrupt Register".
    if ( (LPC_TIM0->IR & 0x01) == 0x01 ){ 				// If MR0 interrupt 
				LPC_TIM0->IR |= 1 << 0; 									// Clear MR0 interrupt flag 
				kbd_val = ~(LPC_GPIO1->FIOPIN >> 20) & KBD_MASK;
				if ( kbd_val == 0x10){  									// Check if joystick right button is hit
						if ( level < 9){
								level++;
								Topdisplay();
						}
						kbd_val = 0;													// Reset 
				}
				if ( kbd_val == 0x40){  									// Check if joystick left button is hit
						if ( level > 1){
								level--;
								Topdisplay();
						}
						kbd_val = 0;													// Reset 
				}
		}
}


/***************************************************************************************/
/* Returns 1 if the boundary has been hit                                              */
/***************************************************************************************/
int hitboundary(){
		if ( x0 < 2*(2*t + 1) | y0 < 3*(2*t + 1) | x0 > 27*(2*t + 1) | y0 > 20 * (2*t + 1)){
				return 1;
		}
		else return 0;
}

/***************************************************************************************/
/* Draw the boundaries for the snake                                                   */
/***************************************************************************************/
void Draw_boundary(){
		GLCD_SetTextColor(Blue);
		GLCD_SetBackColor(Black);
		
	
		/* Draw the horizontal lines********************************************************/
		Draw_straightlineX( 6, 17, 313);
		Draw_straightlineX( 6, 18, 313);
		Draw_straightlineX( 6, 19, 313);
		Draw_straightlineX( 6, 20, 313);
		Draw_straightlineX( 6, 21, 313);
		Draw_straightlineX( 6, 22, 313);
		Draw_straightlineX( 6, 23, 313);
		Draw_straightlineX( 6, 24, 313);
		Draw_straightlineX( 6, 25, 313);
		Draw_straightlineX( 6, 26, 313);
		Draw_straightlineX( 6, 27, 313);
	

		/* Draw the horizontal lines********************************************************/
		Draw_straightlineX( 6, 226, 313);
		Draw_straightlineX( 6, 227, 313);
		Draw_straightlineX( 6, 228, 313);
		Draw_straightlineX( 6, 229, 313);
		Draw_straightlineX( 6, 230, 313);
		Draw_straightlineX( 6, 231, 313);
		Draw_straightlineX( 6, 232, 313);
		Draw_straightlineX( 6, 233, 313);
		Draw_straightlineX( 6, 234, 313);
		Draw_straightlineX( 6, 235, 313);
		Draw_straightlineX( 6, 236, 313);
		Draw_straightlineX( 6, 237, 313);
	

		/* Draw the vertical lines*************************************************************/
		Draw_straightlineY( 6, 17, 237);
		Draw_straightlineY( 7, 17, 237);
		Draw_straightlineY( 8, 17, 237);
		Draw_straightlineY( 9, 17, 237);
		Draw_straightlineY( 10, 17, 237);
		Draw_straightlineY( 11, 17, 237);
		Draw_straightlineY( 12, 17, 237);
		Draw_straightlineY( 13, 17, 237);
		Draw_straightlineY( 14, 17, 237);
		Draw_straightlineY( 15, 17, 237);
		Draw_straightlineY( 16, 17, 237);


		/* Draw the vertical lines*************************************************************/
		Draw_straightlineY( 303, 17, 237);
		Draw_straightlineY( 304, 17, 237);
		Draw_straightlineY( 305, 17, 237);
		Draw_straightlineY( 306, 17, 237);
		Draw_straightlineY( 307, 17, 237);
		Draw_straightlineY( 308, 17, 237);
		Draw_straightlineY( 309, 17, 237);
		Draw_straightlineY( 310, 17, 237);
		Draw_straightlineY( 311, 17, 237);
		Draw_straightlineY( 312, 17, 237);
		Draw_straightlineY( 313, 17, 237);

	
		GLCD_SetTextColor(Black);
		i = 0;
		while( i < lifegainer){
				Draw_element(154+i*11, 10, t );
				i++;
		}	
}


/***************************************************************************************/
/* Draw mouse at a random position                                                     */
/***************************************************************************************/
void Draw_initialmouse(){
		x2 = (2*t+1)*((rand()+randomnumber)%26+2);
		y2 = (2*t+1)*((rand()+randomnumber)%18+3);	
		GLCD_SetTextColor(Green);
		Draw_element(x2 , y2,t);
}


/***************************************************************************************/
/* The function is used to generate sound using DAC                                    */
/***************************************************************************************/
void sound (int x){
		i = 0;
		while(x){
				x--;
				LPC_DAC->CR = (i << 6) | DAC_BIAS; // Digital value to be converted
				i++;
				for(g = 10000; m > 1; m--);
				if ( i == DATA_LENGTH ){
						i = 0;
				}	
		}	
}


/***************************************************************************************/
/* Check if keys 1 to 9 are hit with keyboard                                          */
/***************************************************************************************/
void Keychecklevel (void){
	  /* UART0****************************************************************************/
		if ( UART0Count != 0 ){
				LPC_UART0->IER = IER_THRE | IER_RLS;			
				UARTSend( 0, (uint8_t *)(UART0Buffer), UART0Count );
				val_Tx = UART0Buffer[0];
				if ( val_Tx == 0x31){
						level = 1;
				}
				if ( val_Tx == 0x32){
						level = 2;
				}
				if ( val_Tx == 0x33){
						level = 3;
				}
				if ( val_Tx == 0x34){
						level = 4;
				}
				if ( val_Tx == 0x35){
						level = 5;
				}
				if ( val_Tx == 0x36){
						level = 6;
				}
				if ( val_Tx == 0x37){
						level = 7;
				}
				if ( val_Tx == 0x38){
						level = 8;
				}
				if ( val_Tx == 0x39){
						level = 9;
				}
				val_Tx = 0;
				UART0Count = 0;
				LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	
		}
	
		/* UART1****************************************************************************/
		if ( UART1Count != 0 ){
				LPC_UART1->IER = IER_THRE | IER_RLS;			
				UARTSend( 1, (uint8_t *)UART1Buffer, UART1Count );
				val_Tx = UART1Buffer[0];	
				if ( val_Tx == 0x31){
						level = 1;
				}
				if ( val_Tx == 0x32){
						level = 2;
				}
				if ( val_Tx == 0x33){
						level = 3;
				}
				if ( val_Tx == 0x34){
						level = 4;
				}
				if ( val_Tx == 0x35){
						level = 5;
				}
				if ( val_Tx == 0x36){
						level = 6;
				}
				if ( val_Tx == 0x37){
						level = 7;
				}
				if ( val_Tx == 0x38){
						level = 8;
				}
				if ( val_Tx == 0x39){
						level = 9;
				}
				val_Tx = 0;
				UART1Count = 0;
				LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;	
		}
}


/***************************************************************************************/
/* The function is used to Initialize                                                  */
/***************************************************************************************/
void Initialize (void){
		//UART Iniializaion
		SystemClockUpdate();											// Updates the SystemFrequency 
		UARTInit(0, 57600);												// Baud rate setting 
		UARTInit(1, 57600);												// Baud rate setting 
	
		//LCD 
		GLCD_Init();                          		// Initialize graphical LCD
		GLCD_Clear(Black); 												// Clear graphical LCD display
	
		//Timer0 configuration
		LPC_SC->PCONP |= 1 << 1; 									// Power up Timer 0
		LPC_SC->PCLKSEL0 |= 1 << 2; 							// Clock for timer = CPU Clock
		LPC_TIM0->MR0 = 1 << 24 ;
		LPC_TIM0->MCR |= 1 << 0;									// Interrupt on Match 0 compare
		LPC_TIM0->MCR |= 1 << 1; 									// Reset timer on Match 0
		LPC_TIM0->TCR |= 1 << 1; 									// Manually Reset Timer 0 
		LPC_TIM0->TCR &= ~(1 << 1); 							// Stop resetting the timer
		NVIC_EnableIRQ(TIMER0_IRQn); 							// Enable timer interrupt;
		LPC_TIM0->TCR |= 1 << 0; 									// Start timer
	
		// DAC iniializaion
		DACInit();																// For sound
	
		// Joystick
		LPC_PINCON->PINSEL3 &= ~((3<< 8)|(3<<14)|(3<<16)|(3<<18)|(3<<20));
		// P1.20, P1.23, …, P1.26 are GPIO (Joystick)
		LPC_GPIO1->FIODIR &= ~((1<<20)|(1<<23)|(1<<24)|(1<<25)|(1<<26));
		// P1.20, P1.23, ..., P1.26 are input (Joystick)
}


/***************************************************************************************/
/* The function is used to display life and level at the top                           */
/***************************************************************************************/
void Topdisplay (void){
		GLCD_SetTextColor(Cyan);
		GLCD_SetBackColor(Black);
		GLCD_DisplayString(0, 0, 1, "LIVES:");
		sprintf(text, "%01X", life);
		GLCD_DisplayString(0, 6, 1, (uint8_t*)text);
		GLCD_DisplayString(0, 13, 1, "LEVEL:");
		sprintf(text, "%01X", level);
		GLCD_DisplayString(0, 19, 1, (uint8_t*)text);
}


/***************************************************************************************/
/* The function is used to check array key hit                                         */
/***************************************************************************************/
void Keycheckarrow(void){
		if ( UART0Count != 0 ){
				LPC_UART0->IER = IER_THRE | IER_RLS;			
				UARTSend( 0, (uint8_t *)(UART0Buffer), UART0Count );
				val_Tx = UART0Buffer[2];
				if ( val_Tx == 0x41 | val_Tx == 0x42 | val_Tx == 0x43 | val_Tx == 0x44){
						if ( val_Tx == 0x44 & direc != 2 ){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 1;
								direc = 1;
								k++;
						}
						if ( val_Tx == 0x43 & direc != 1){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 2;
								direc = 2;
								k++;
						}
						if ( val_Tx == 0x41 & direc != 4){
								a[k][0] = x0;
								a[k][1] = y0;	
								a[k][2] = 3;
								direc = 3;
								k++;
						}
						if ( val_Tx == 0x42 & direc != 3){
								a[k][0] = x0;
								a[k][1] = y0;	
								a[k][2] = 4;
								direc = 4;
								k++;
						}	
						if ( k == 999){
								k = 0;
						}
						val_Tx = 0;
				}
				UART0Count = 0;
				LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	
		}
		if ( UART1Count != 0 ){
				LPC_UART1->IER = IER_THRE | IER_RLS;			
				UARTSend( 1, (uint8_t *)UART1Buffer, UART1Count );
				val_Tx = UART1Buffer[2];		
				if ( val_Tx == 0x41 | val_Tx == 0x42 | val_Tx == 0x43 | val_Tx == 0x44){	
						if ( val_Tx == 0x44 & direc != 2 ){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 1;
								direc = 1;
								k++;
						}
						if ( val_Tx == 0x43 & direc != 1 ){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 2;
								direc = 2;
								k++;
						}
						if ( val_Tx == 0x41 & direc != 4 ){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 3;
								direc = 3;
								k++;
						}
						if ( val_Tx == 0x42 & direc != 3){
								a[k][0] = x0;
								a[k][1] = y0;
								a[k][2] = 4;
								direc = 4;
								k++;
						}	
						if ( k == 999){
								k = 0;
						}
						val_Tx = 0;
				}
				UART1Count = 0;
				LPC_UART1->IER = IER_THRE | IER_RLS | IER_RBR;	
		}
}


