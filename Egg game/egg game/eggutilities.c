
#include "EGGUTILITIES.h"
#include "GLCD.h"
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
/*draws a starting line in with thicknes t an slope s 												*/
/* t = number of pixels in x direcion(thickness) of line                      */
/* s = slope. bigger the value smaller the slope                              */
/* does not guaranee x1 y1 position. Posiion will be defined by slope         */
/******************************************************************************/

void Draw_lineXY( int x0, int y0,int x1,int y1, int t,int s){ 
	int i,d;

y1>y0 ?  (d = 1) :  (d = 2);
		
while(x0<=x1 & y0!=y1)
	 {
		i = 0;
		while(i < t){
			GLCD_PutPixel(x0+i,y0);       		// Put pixels 
			i++;
		}
		if(d == 1){
			y0++;
		}
		else if(d == 2){
			y0--;
		}		
		x0 = x0 + s;                       		
	}
}
/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void Draw_lineX( int x0, int y0, int x1){ 

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
/*                                                                            */
/******************************************************************************/

void Draw_lineX2( int x0, int y0, int x1){ 

		// first obtain absolute distance
		int dx = x0<x1 ? (x1-x0) : (x0-x1); // basically dx=abs(x1-x0)
		int k = dx/2+1;                 		// Get k value to get distance by 2.
    while(k>0) {
        // call of GCLD function;
        GLCD_PutPixel(x0,y0);   				// Put pixels from one direction
        GLCD_PutPixel(x1,y0);   				// Put pixels from opposite direction
        x1++;                   				// decrement in one direction
        x0--;                   				// increment on other direction
        k--;
    }

		


			

}
/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void Draw_lineY( int x0, int y0, int y1){ 


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
/*                                                                            */
/******************************************************************************/

void Draw_CHICKEN1(int y0 ){ 


	GLCD_SetTextColor(Red);	
	
	GLCD_PutPixel(21,y0);    
	GLCD_PutPixel(17,y0+1); 
	GLCD_PutPixel(18,y0+1);
	
	Draw_lineX( 20, y0+1, 22);
	Draw_lineX(17, y0+2, 23);
	Draw_lineX(16, y0+3, 23);
	Draw_lineX(17, y0+4, 22);
	
	GLCD_PutPixel(18, y0+5);
	
	GLCD_SetTextColor(Orange);
	Draw_lineX(25, y0+7, 28);
	Draw_lineX(25, y0+8, 26);
	Draw_lineX(25, y0+9, 28);
	Draw_lineX(25, y0+10, 26);
	
	GLCD_SetTextColor(Black);
	GLCD_PutPixel(19, y0+9);
	
	GLCD_PutPixel(20, y0+9);

	
	GLCD_SetTextColor(Yellow);		
	Draw_lineX(19,y0+5,22);
	Draw_lineX(17,y0+6,23);
	Draw_lineX(17,y0+7,24);
	Draw_lineX(16,y0+8,24);
	Draw_lineX(15,y0+9,24);
	Draw_lineX(14,y0+10,24);
	Draw_lineX(14,y0+11,24);
	Draw_lineX(13,y0+12,24);
	Draw_lineX(12,y0+13,22);
	Draw_lineX(11,y0+14,22);
	Draw_lineX(10,y0+15,22);
	Draw_lineX(2,y0+16,22);
	Draw_lineX(0,y0+17,22);
	Draw_lineX(0,y0+18,22);
	Draw_lineX(0,y0+19,22);
	Draw_lineX(2,y0+20,21);
	Draw_lineX(4,y0+21,21);
	Draw_lineX(2,y0+22,21);
	Draw_lineX(0,y0+23,20);
	Draw_lineX(1,y0+24,20);
	Draw_lineX(1,y0+25,20);
	Draw_lineX(2,y0+26,19);
	Draw_lineX(3,y0+27,18);
	Draw_lineX(3,y0+28,17);
	Draw_lineX(4,y0+29,16);
	Draw_lineX(5,y0+30,15);
	Draw_lineX(6,y0+31,14);
	//Tail
	GLCD_PutPixel(0, y0+10);

	Draw_lineX(0, y0+9, 1);
	Draw_lineX(0, y0+10, 2);
	Draw_lineX(0, y0+11, 3);
	Draw_lineX(1, y0+12, 4);
	Draw_lineX(1, y0+13, 5);
	Draw_lineX(2, y0+14, 6);
	Draw_lineX(3, y0+15, 7);
	
	
	GLCD_SetTextColor(Black);
	GLCD_PutPixel(20, y0+8);
	
	GLCD_PutPixel(21, y0+8);
	
	GLCD_PutPixel(19, y0+9);
	GLCD_PutPixel(20, y0+9);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void Draw_CHICKEN2(int y0 ){ 


		GLCD_SetTextColor(Red);	
		
		GLCD_PutPixel(319-21,y0);    
		GLCD_PutPixel(319-17,y0+1); 
		GLCD_PutPixel(319-18,y0+1);
		
		Draw_lineX2( 319-20, y0+1, 319-22);
		Draw_lineX2(319-17, y0+2, 319-23);
		Draw_lineX2(319-16, y0+3, 319-23);
		Draw_lineX2(319-17, y0+4, 319-22);
		
		GLCD_PutPixel(319-18, y0+5);
		
		GLCD_SetTextColor(Orange);
		Draw_lineX2(319-25, y0+7, 319-28);
		Draw_lineX2(319-25, y0+8, 319-26);
		Draw_lineX2(319-25, y0+9, 319-28);
		Draw_lineX2(319-25, y0+10, 319-26);
		
		GLCD_SetTextColor(Black);
		GLCD_PutPixel(319-19, y0+9);
		
		GLCD_PutPixel(319-20, y0+9);

		
		GLCD_SetTextColor(Yellow);		
		Draw_lineX2(319-19,y0+5,319-22);
		Draw_lineX2(319-17,y0+6,319-23);
		Draw_lineX2(319-17,y0+7,319-24);
		Draw_lineX2(319-16,y0+8,319-24);
		Draw_lineX2(319-15,y0+9,319-24);
		Draw_lineX2(319-14,y0+10,319-24);
		Draw_lineX2(319-14,y0+11,319-24);
		Draw_lineX2(319-13,y0+12,319-24);
		Draw_lineX2(319-12,y0+13,319-22);
		Draw_lineX2(319-11,y0+14,319-22);
		Draw_lineX2(319-10,y0+15,319-22);
		Draw_lineX2(319-2,y0+16,319-22);
		Draw_lineX2(319-0,y0+17,319-22);
		Draw_lineX2(319-0,y0+18,319-22);
		Draw_lineX2(319-0,y0+19,319-22);
		Draw_lineX2(319-2,y0+20,319-21);
		Draw_lineX2(319-4,y0+21,319-21);
		Draw_lineX2(319-2,y0+22,319-21);
		Draw_lineX2(319-0,y0+23,319-20);
		Draw_lineX2(319-1,y0+24,319-20);
		Draw_lineX2(319-1,y0+25,319-20);
		Draw_lineX2(319-2,y0+26,319-19);
		Draw_lineX2(319-3,y0+27,319-18);
		Draw_lineX2(319-3,y0+28,319-17);
		Draw_lineX2(319-4,y0+29,319-16);
		Draw_lineX2(319-5,y0+30,319-15);
		Draw_lineX2(319-6,y0+31,319-14);
		//Tail
		GLCD_PutPixel(319-0, y0+10);

		Draw_lineX2(319-0, y0+9, 319-1);
		Draw_lineX2(319-0, y0+10, 319-2);
		Draw_lineX2(319-0, y0+11, 319-3);
		Draw_lineX2(319-1, y0+12, 319-4);
		Draw_lineX2(319-1, y0+13, 319-5);
		Draw_lineX2(319-2, y0+14, 319-6);
		Draw_lineX2(319-3, y0+15, 319-7);
		
		
		GLCD_SetTextColor(Black);
		GLCD_PutPixel(319-20, y0+8);
		
		GLCD_PutPixel(319-21, y0+8);
		
		GLCD_PutPixel(319-19, y0+9);
		GLCD_PutPixel(319-20, y0+9);
	}

void Drawegg1(int X0,int Y0){
		
		Draw_lineX(X0+2,Y0-4,X0+6);
		Draw_lineX(X0+1,Y0-3,X0+7);
		Draw_lineX(X0,Y0-2,X0+7);
		Draw_lineX(X0-1,Y0-1,X0+7);
		Draw_lineX(X0-1,Y0,X0+7);
		Draw_lineX(X0-1,Y0+1,X0+5);
		Draw_lineX(X0,Y0+2,X0+4);		
}
void Drawegg2(int X0,int Y0){
		
		Draw_lineX(X0+2,Y0-4,X0+6);
		Draw_lineX(X0+1,Y0-3,X0+7);
		Draw_lineX(X0,Y0-2,X0+7);
		Draw_lineX(X0-1,Y0-1,X0+7);
		Draw_lineX(X0-1,Y0,X0+7);
		Draw_lineX(X0-1,Y0+1,X0+5);
		Draw_lineX(X0,Y0+2,X0+4);		
}
void Drawegg3(int X0,int Y0){
		
		Draw_lineX(X0+2,Y0-4,X0+6);
		Draw_lineX(X0+1,Y0-3,X0+7);
		Draw_lineX(X0,Y0-2,X0+7);
		Draw_lineX(X0-1,Y0-1,X0+7);
		Draw_lineX(X0-1,Y0,X0+7);
		Draw_lineX(X0-1,Y0+1,X0+5);
		Draw_lineX(X0,Y0+2,X0+4);		
}
void Drawegg4(int X0,int Y0){
		
		Draw_lineX(X0+2,Y0-4,X0+6);
		Draw_lineX(X0+1,Y0-3,X0+7);
		Draw_lineX(X0,Y0-2,X0+7);
		Draw_lineX(X0-1,Y0-1,X0+7);
		Draw_lineX(X0-1,Y0,X0+7);
		Draw_lineX(X0-1,Y0+1,X0+5);
		Draw_lineX(X0,Y0+2,X0+4);		
}

void Drawbasket(int X0,int Y0){
		int j , k ;
		GLCD_SetTextColor(Olive);
		Draw_lineX(X0-12,Y0,X0+13);
		Draw_lineX(X0-12,Y0+1,X0+11);
		Draw_lineX(X0-10,Y0+2,X0+11);
		Draw_lineX(X0-10,Y0+3,X0+11);
		Draw_lineX(X0-10,Y0+4,X0+11);
		Draw_lineX(X0-10,Y0+5,X0+11);
		Draw_lineX(X0-10,Y0+6,X0+11);
		Draw_lineX(X0-10,Y0+7,X0+11);
		Draw_lineX(X0-10,Y0+8,X0+11);
		Draw_lineX(X0-10,Y0+9,X0+11);
		Draw_lineX(X0-10,Y0+10,X0+11);
		Draw_lineX(X0-10,Y0+11,X0+11);
		Draw_lineX(X0-9,Y0+12,X0+10);
		Draw_lineX(X0-9,Y0+13,X0+10);
		Draw_lineX(X0-9,Y0+14,X0+10);
		Draw_lineX(X0-8,Y0+15,X0+9);
		Draw_lineX(X0-8,Y0+16,X0+9);
		Draw_lineX(X0-8,Y0+17,X0+9);
	
		GLCD_SetTextColor(Black);
		k = 0;
		j = 0;
		while( k < 3){
				while( j < 6){
						Draw_lineX(X0-10+(4*j),Y0+2+(4*k),X0-9+(4*j));
						Draw_lineX(X0-10+(4*j),Y0+3+(4*k),X0-9+(4*j));
						j++;
				}
				j=0;
				k++;
		}
}

