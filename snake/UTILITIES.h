#ifndef _KEN_UTILS_H
#define _KEN_UTILS_H

extern void Draw_element(int x0 , int y0 , int t);

extern void tempstore (int direc , int a1, int a2, int a3 );

extern void val_display(char c);

extern void Draw_straightlineX( int x0, int y0, int x1) ;
extern void Draw_straightlineY( int x0, int y0, int y1) ;
extern void mouse( void );
extern int hitboundary( void );
extern void Draw_boundary( void );
extern void Draw_initialmouse( void );
extern void sound (int x0);
extern void blankscreen(void);
extern void Keychecklevel(void);
extern void Keycheckarrow(void);
extern void Initialize(void);
extern void Topdisplay(void);
extern void Getlevel(void);
#endif	
