/******************************************************************************/
/******************************************************************************/

#include "GLCD.h"
#include "UTILITIES.h"
/*---------------------------------------------------------------------------*/
/* Draw the main element                                                     */
/*---------------------------------------------------------------------------*/
void Draw_element(int x0 , int y0, int t ){ 
		int j ,k;
		j= k = -t;
		while(j<(t+1)){
				while(k<t+1){		
						GLCD_PutPixel(x0-k, y0-j);
						k++;
				}
				k = -t;
				j++;
		}
}


/*---------------------------------------------------------------------------*/
/* display transmit and receieve values                                      */
/*---------------------------------------------------------------------------*/
void val_display(char c) {
    GLCD_SetTextColor(Red);
		GLCD_DisplayChar (5, 5, 1, c);
}


/******************************************************************************/
/*draws a starting line in x direction 																				*/
/******************************************************************************/
void Draw_straightlineX( int x0, int y0, int x1){
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
void Draw_straightlineY( int x0, int y0, int y1){
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

