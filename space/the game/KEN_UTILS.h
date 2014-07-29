#ifndef _KEN_UTILS_H
#define _KEN_UTILS_H

extern void KEN_draw_circle( int x0, int y0, int radius);

extern void KEN_draw_line( int x0, int y0, int x1, int y1);

extern void KEN_draw_rectangle( int x0, int y0, int x1, int y1);
extern void KEN_draw_straightlineX( int x0, int y0, int x1) ;
extern void KEN_draw_straightlineY( int x0, int y0, int y1) ;
extern void KEN_draw_UFO( int x0, int y0) ;
extern void KEN_draw_UFOLEFT( int x0, int y0) ;
extern void KEN_draw_UFORIGHT( int x0, int y0) ;

extern void KEN_draw_UFOB( int x0, int y0) ;
extern void KEN_draw_rightD( int x0, int y0) ;
extern void KEN_draw_leftD( int x0, int y0) ;
extern void KEN_draw_grenade( int x0, int y0) ;
extern void KEN_draw_grenadeM( int x0, int y0) ;
extern void sound( int x0) ;
#endif	
