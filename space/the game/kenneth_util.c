/******************************************************************************/
/*Functions to draw the UFO and the grenade 																	*/
/******************************************************************************/

#include <stdio.h>
#include "LPC17xx.H"                    // LPC17xx definitions         
#include "GLCD.h"
#include "KEN_UTILS.h"

#define __FI        1                   // Font index 16x24               
/******************************************************************************/
/*draws a starting line in x direction 																				*/
/******************************************************************************/

void KEN_draw_straightlineX( int x0, int y0, int x1){
		// first obtain absolute distance
		int dx = x0<x1 ? (x1-x0) : (x0-x1); // basically dx=abs(x1-x0)
		int k = dx/2+1;                 		// Get k value to get distance by 2.
    while(k>0) {
        // call of GCLD function;
        GLCD_PutPixel(x0,y0);   				// Put pixels from one direction
        GLCD_PutPixel(x1,y0);   				// Put pixels from opposite direction
        x1--;                   				// decrement in one direction
        x0++;                   				// increment on other direction
        k--;
    }
}
/******************************************************************************/
/*draws a starting line in y direction 																				*/
/******************************************************************************/
void KEN_draw_straightlineY( int x0, int y0, int y1){
    // first obtain absolute distance
		int dy = y0<y1 ? (y1-y0) : (y0-y1); // basically dx=abs(y1-y0)
		int k = dy/2+1;                     // Get k value to get distance by 2.
    while(k>0) {
        GLCD_PutPixel(x0,y0);       		// Put pixels from one direction
        GLCD_PutPixel(x0,y1);       		// Put pixels from opposite direction
        y1--;                       		// decrement in one direction
        y0++;                       		// increment on other direction
        k--;
    }
}

/******************************************************************************/
/* Draw the UFO using the lines. Divided the UFO into blocks of 5*5 pixels.   */
/* All the blocks are drawn simultaneously. In each pass of the loop one line */
/* corresponding to each block is drawn using the KEN_draw_straightlineY 			*/
/******************************************************************************/

void KEN_draw_UFO( int x0, int y0){
    int k = 0 ;
		while (k < 5){
        // Draw the first set of blue blocks
        GLCD_SetTextColor(Blue);
        KEN_draw_straightlineY( x0-15,y0,y0+4);
        KEN_draw_straightlineY( x0-10,y0,y0+4);
        KEN_draw_straightlineY( x0-5,y0,y0+4);
        KEN_draw_straightlineY( x0,y0,y0+4);
        KEN_draw_straightlineY( x0+4,y0,y0+4);
        KEN_draw_straightlineY( x0+9,y0,y0+4);
			
        // Draw the second set of blue blocks
        GLCD_SetTextColor(Blue);
        KEN_draw_straightlineY( x0-25,y0+5,y0+9);
        KEN_draw_straightlineY( x0-20,y0+5,y0+9);
        KEN_draw_straightlineY( x0-15,y0+5,y0+9);
        KEN_draw_straightlineY( x0-10,y0+5,y0+9);
        KEN_draw_straightlineY( x0-5,y0+5,y0+9);
        KEN_draw_straightlineY( x0,y0+5,y0+9);
        KEN_draw_straightlineY( x0+4,y0+5,y0+9);
        KEN_draw_straightlineY( x0+9,y0+5,y0+9);
        KEN_draw_straightlineY( x0+14,y0+5,y0+9);
        KEN_draw_straightlineY( x0+19,y0+5,y0+9);
				
        // Draw the tthird set of consecutive red and blue blocks
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-35,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-30,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-25,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-20,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-15,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-10,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+4,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+9,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+14,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+19,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+24,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+29,y0+10,y0+14);
				
        // Draw the fourth set of blue blocks
        GLCD_SetTextColor(Blue);
        KEN_draw_straightlineY( x0-25,y0+15,y0+19);
        KEN_draw_straightlineY( x0-20,y0+15,y0+19);
        KEN_draw_straightlineY( x0-15,y0+15,y0+19);
        KEN_draw_straightlineY( x0-10,y0+15,y0+19);
        KEN_draw_straightlineY( x0-5,y0+15,y0+19);
        KEN_draw_straightlineY( x0,y0+15,y0+19);
        KEN_draw_straightlineY( x0+4,y0+15,y0+19);
        KEN_draw_straightlineY( x0+9,y0+15,y0+19);
        KEN_draw_straightlineY( x0+14,y0+15,y0+19);
        KEN_draw_straightlineY( x0+19,y0+15,y0+19);
				
        // Draw the fifth set of blue blocks
        KEN_draw_straightlineY( x0-15,y0+20,y0+24);
        KEN_draw_straightlineY( x0-10,y0+20,y0+24);
        KEN_draw_straightlineY( x0-5,y0+20,y0+24);
        KEN_draw_straightlineY( x0,y0+20,y0+24);
        KEN_draw_straightlineY( x0+4,y0+20,y0+24);
        KEN_draw_straightlineY( x0+9,y0+20,y0+24);

        x0++;
        k++;
		}

}
void KEN_draw_UFORIGHT( int x0, int y0){
		int k = 0 ;
    while (k < 5){
				// Erase the blocks to the left
        GLCD_SetTextColor(Black);
        KEN_draw_straightlineY( x0-15,y0,y0+4);
        KEN_draw_straightlineY( x0-25,y0+5,y0+9);
        KEN_draw_straightlineY( x0-35,y0+10,y0+14);
        KEN_draw_straightlineY( x0-15,y0+20,y0+24);
		    KEN_draw_straightlineY( x0-25,y0+15,y0+19);
			
				// draw blue boxes to the right
        GLCD_SetTextColor(Blue);
        KEN_draw_straightlineY( x0+14,y0,y0+4);
        KEN_draw_straightlineY( x0+24,y0+5,y0+9);
        KEN_draw_straightlineY( x0+24,y0+15,y0+19);
        KEN_draw_straightlineY( x0+14,y0+20,y0+24);

				//redraw red and yellow boxes
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-30,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-25,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-20,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-15,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-10,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+4,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+9,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+14,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+19,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+24,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+29,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+34,y0+10,y0+14);

				x0++;
				k++;
		}
}

void KEN_draw_UFOLEFT( int x0, int y0){

	int k = 0 ;
	while (k < 5)
	{
        // Erase the blocks to the right
        GLCD_SetTextColor(Black);
				KEN_draw_straightlineY( x0+14,y0,y0+4);
				KEN_draw_straightlineY( x0+24,y0+5,y0+9);
				KEN_draw_straightlineY( x0+34,y0+10,y0+14);
				KEN_draw_straightlineY( x0+24,y0+15,y0+19);
				KEN_draw_straightlineY( x0+14,y0+20,y0+24);

        // redraw blue boxes to the left
        GLCD_SetTextColor(Blue);
        KEN_draw_straightlineY( x0-15,y0,y0+4);
        KEN_draw_straightlineY( x0-25,y0+5,y0+9);
        KEN_draw_straightlineY( x0-25,y0+15,y0+19);
        KEN_draw_straightlineY( x0-15,y0+20,y0+24);

        //redraw red and yellow boxes
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-40+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-35+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-30+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-25+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-20+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-15+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0-10+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0-5+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+4+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+9+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+14+5,y0+10,y0+14);
        GLCD_SetTextColor(Red);
        KEN_draw_straightlineY( x0+19+5,y0+10,y0+14);
        GLCD_SetTextColor(Yellow);
        KEN_draw_straightlineY( x0+24+5,y0+10,y0+14);

				x0--;
				k++;
		}
}
/******************************************************************************/
/* The initial grenade drawing is also done using the line functions.         */
/******************************************************************************/
void KEN_draw_grenade( int x0, int y0){
		int k ;
		
		while ( k < 10){
        KEN_draw_straightlineX( x0 - 7, y0+19, x0 + 7); 	// straight line for base
        KEN_draw_straightlineX( x0 - 1, y0+9, x0 + 1); 		// staright line for stem 
			k++;
        y0--;
		}
}
/******************************************************************************/
/* The grenade also is redrawn by erasing and drawing only parts of the UFO   */
/* which are being changed.                                                   */
/******************************************************************************/
void KEN_draw_grenadeM( int x0, int y0){
    int k = 0 ;
    while ( k < 5){
        GLCD_SetTextColor(Black);
        KEN_draw_straightlineX( x0 - 7, y0+19, x0 + 7); 	// bottom erased
        GLCD_SetTextColor(Magenta);	
        KEN_draw_straightlineX( x0 - 1, y0+1, x0 + 1);   	// New stem drawn
        KEN_draw_straightlineX( x0 - 7, y0+9, x0 + 7);   	// New base bottom drawn
        k++;
        y0--;
    }
}
