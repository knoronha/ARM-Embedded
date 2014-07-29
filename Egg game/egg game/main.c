#include "GLCD.h"


int X4,Y4,X1,Y1,X2,Y2,X3,Y3,i;

int main (void){
	//LCD iniialization
	GLCD_Init();                             	// Initialize graphical LCD
	GLCD_Clear(White); 												// Clear graphical LCD display
	
	

	
	// int x0, int y0,int x1,int d, int t,int s)
	
	GLCD_SetTextColor(DarkGrey);

	Draw_lineXY( 0,61,0,64,27,0);
	Draw_lineXY( 19,61,83,93,8,2);
	
	Draw_lineXY( 0,142,0,145,27,0);
	Draw_lineXY( 19,142,83,174,8,2);
	
	Draw_lineXY( 293,61,293	,64,27,0);
	Draw_lineXY( 228,93,293,61,8,2);
	
	Draw_lineXY( 293,142,293,145,27,0);
	Draw_lineXY( 228,174,293,142,8,2);	


	 
	Draw_CHICKEN1(29);
	Draw_CHICKEN1(110);
	
  Draw_CHICKEN2(29);
	Draw_CHICKEN2(110);
	
	X1 = 32;
	Y1 = 54;
	
	
	X2 = 32;
	Y2 = 135;
	
	
	X3 = 286;
	Y3 = 54;
	
	X4 = 286;
	Y4 = 135;
	
	
	Drawbasket( 122, 96);
	
	
	
	
	while(1){
		
		
		
		GLCD_SetTextColor(Orange);
	
		Drawegg1(X1,Y1);
		Drawegg2(X2,Y2);
		Drawegg3(X3,Y3);
		Drawegg4(X4,Y4);
		
		for ( i =0 ; i <1000000; i++);

		GLCD_SetTextColor(White);
		
		Drawegg1(X1,Y1);
		Drawegg2(X2,Y2);
		Drawegg3(X3,Y3);
		Drawegg1(X4,Y4);
		
		X1 = X1 + 15;
		Y1 = Y1 + 7;
		
		if ( X1 == 122 & Y1 == 96){
				X1 = 32;
				Y1 = 54;
		}
		
		X2 = X2 + 15;
		Y2 = Y2 + 7;
		
		if ( X2 == 122 & Y2 == 177){
				X2 = 32;
				Y2 = 135;
		}
		
		
		X3 = X3 - 15;
		Y3 = Y3 + 7;
		
		if ( X3 == 196 & Y3 == 96){
				X3 = 286;
				Y3 = 54;
		}
		
		X4 = X4 - 15;
		Y4 = Y4 + 7;
		
		if ( X4 == 196 & Y4 == 177){
				X4 = 286;
				Y4 = 135;
		}

		
	}
	
	
	
}
