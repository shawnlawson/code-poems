// gcc a.c -lncurses
#include<math.h>
#include<curses.h>
struct g{char l;int x,y;};char r[6]="PLOP! ";struct g f[4]={{'f',60,10},{'r',61,10},{'o',62,10},{'g',63,10}};int w=-40,i;float u=0,p=0;int main(void){initscr();while(1){if(w<1)w++;if(w>0){u+=.1;for(i=3;i>=0;--i){f[i].x-=1;if(!i)f[i].y=10-(int)(6*sinf(u));else f[i].y=f[i-1].y;if(33>f[1].x)w=2;}}clear();if(w>1&&p<6){mvaddch(10,32,r[(int)floorf(p)]);p+=.1;}for(i=0;i<4&&2>w;++i)mvaddch(f[i].y,f[i].x,f[i].l);refresh();usleep(50000);}}