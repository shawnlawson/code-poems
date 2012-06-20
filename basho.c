//
//  Basho-Watts-Lawson Haiku
//
//  Matsuo Bashô:
//  Furu ike ya
//  kawazu tobikomu
//  mizu no oto 
//
//  Translation by Alan Watts:
//  The old pond,
//  A frog jumps in:
//  Plop!
//
//  compile:
//  cc basho.c -o Haiku -ansi -l ncurses 
//  or
//  clang basho.c -o Haiku -ansi  -l ncurses 
//
//  run:
//  ./Haiku
//
//  usage:
//  spacebar to jump
//  r to reset
//
//  Created by Shawn Lawson on 4 March 2012.
//  Copyright (c) 2012.
//

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curses.h>

struct f{char l;int x,y;};
static char ripple[7]={' ','R','I','P','P','L','E'};
static char plop[7]={' ','P','L','O','P','!',' '};
static char pad[8]={'l','i','l','l','y','p','a','d'};
static char weed[6]={'w','e','e','e','e','d'};
static char fish[4]={'f','i','s','h'};
static int padXY[10]={28,3,63,5,10,10,40,15,58,11,};
static int weedXY[24]={2,9,4,13,8,15,5,18,62,13,68,8,74,14,55,18,20,3,15,5,58,17,57,6};
static int fishXY[2]={11,11};
static struct f tF[4]={{'f',60, 10},{'r',61,10},{'o',62,10},{'g',63,10}};
struct f frog[4];
bool c, **t;
int x=32,y=10,r=0,when=0,i,j,**theOldPond;
float jump=0.0,p=0.0,w=0.0;

static void watch(void){
    wclear(stdscr);
    if(c)
        attron(COLOR_PAIR(4));
    for(i=0;i<LINES;++i){
        for(j=0;j<COLS;++j)
            mvwaddch(stdscr,i,j,' ');
    }
    for(i=0;i<1;++i){
        for(j=0;j<4;++j)
            mvwaddch(stdscr,fishXY[i*2+1],fishXY[i*2]+j,fish[j]);
    }
    if(c){
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(1));
    }
    for(i=0;i<LINES;++i){
        for(j=0;j<COLS;++j)
            if(theOldPond[j][i])
                mvwaddch(stdscr,i,j,ripple[theOldPond[j][i]]);
    }
    if(2==when)
        mvwaddch(stdscr,y,x,plop[(int)floorf(p)]);
    if(c){
        attroff(COLOR_PAIR(1));	
        attron(COLOR_PAIR(2));
    }
    for(i=0;i<4;++i)
        mvwaddch(stdscr,frog[i].y,frog[i].x,frog[i].l);
    for(i=0;i<5;++i){
        for(j=0;j<8;++j)
            mvwaddch(stdscr,padXY[i*2+1],padXY[i*2]+j,pad[j]);
    }
    if(c){
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(3));
    }
    for(i=0;i<12;++i){
        for(j=0;j<6;++j){
            float b = fabsf(sinf(w)*j*.5);
            mvwaddch(stdscr,weedXY[i*2+1]-j,weedXY[i*2]+b,weed[5-j]);
        }
    }
    if(c)
        attroff(COLOR_PAIR(3));
    wmove(stdscr,0,0);
    wrefresh(stdscr);
}

static void growRipple(int x,int y){
    theOldPond[x][y]=(theOldPond[x][y]+1)%7;
    t[x][y]=true;
}

static void animate(void){
    w+=.1;
    if(0==when){
    }else if(1==when){
        jump+=.1;

        for (i=3;i>=0;--i){
            frog[i].x-=1;

            if(0==i)
                frog[0].y=10-roundf(6*sinf(jump));
            else
                frog[i].y=frog[i-1].y;

            if(32>=frog[i].x){
                frog[i].l=' ';
                if(3==i){
                    growRipple(x,y);
                    when=2;
                }
            }
        }
    }else if(2==when){
        for(i=0;i<COLS;++i){
            for(j=0;j<LINES;++j){
                if(theOldPond[i][j])
                    growRipple(i,j);
                else{
                    if(i>=x-r&&i<=x+r&&j>=y-r&&j<=y+r){
                        float d=sqrtf((float)((x-i)*(x-i)+(y-j)*(y-j)));
                        if(r>d&&!t[i][j]) 
                            growRipple(i,j);
                    }
                    if(i==x&&j==y&&p<6)
                        p+=.1;
                }
            }
        }
        r += 1;
    }
}

int main (int argc,const char* argv[]){
    initscr();
    clear();
    curs_set(0);
    noecho();
    cbreak();
    c=has_colors();
    if(c){
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLUE);
        init_pair(2,COLOR_GREEN,COLOR_BLUE);
        init_pair(3,COLOR_YELLOW,COLOR_BLUE);
        init_pair(4,COLOR_MAGENTA,COLOR_BLUE);
    }
    timeout(50);
    refresh();

    theOldPond=(int**)calloc(COLS,sizeof(int*));
    for (i=0;i<COLS;++i){
        theOldPond[i]=(int*)calloc(LINES,sizeof(int));
        memset(theOldPond[i],0,sizeof(int)*COLS);
    }

    t=(bool**)calloc(COLS,sizeof(bool*));
    for(i=0;i<COLS;++i){
        t[i]=(bool*)calloc(LINES,sizeof(bool));
        memset(t[i],false,sizeof(bool)*COLS);
    }

    for(i=0;i<4;++i) 
        frog[i]=tF[i];

    while(true){
        int g=getch();
        if(32==g){
            when=1;
        }else if(114==g){
            for(i=0;i<COLS;++i) 
                memset(t[i],false,sizeof(bool)*COLS);
            for(i=0;i<4;++i) 
                frog[i]=tF[i];
            jump=p=0.0;
            r=when=0;
        }
        animate();
        watch();
    }

    for(i=0;i<COLS-1;++i){
        free(theOldPond[i]);
        free(t[i]);
    }
    free(theOldPond);
    free(t);
    endwin();
    return 0;
}