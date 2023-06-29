/************************************** 
* CC65 Maze Demo                      *
* Recursive Division Algo.            *
* JOSIP RETRO BITS, 2023              *
**************************************/
//Build: cl65 maze_div4.c -o maze_div4.prg

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <c64.h>
#include <peekpoke.h>
#include <cc65.h>
#include <string.h>

unsigned char* T = (char *) 0xd018;
#define RASTER 0xD012

uint8_t nd=1;
uint8_t sd=2;
uint8_t ed=4;
uint8_t wd=8;

uint8_t horizontal=0;
uint8_t vertical=1;

uint8_t grid[25][25];

uint8_t width=25;
uint8_t height=25;

int chrlookup[7] = {
	32,
	1,
	111,
	3,
	103,
	5,
	122
	};


void delay(void) {
	unsigned int t=0;
	for(t=0;t<1000;t++) {}
}


void drawMaze() {

	uint8_t x,y;
	unsigned int p;
	
	for(y=0;y<height;y++) {
		for(x=0;x<width;x++) {
			p=y*40+x;
			POKE(1024+p, chrlookup[grid[y][x]]);
 		}
	}
	
	return;

}

void divide(uint8_t mx, uint8_t my, uint8_t ax, uint8_t ay) {
	
	uint8_t x,y,dx,dy,xp,yp,wall;
	
    dx = ax - mx;
    dy = ay - my;
   
    if( dx < 2 || dy < 2) {

		if(dx > 1) {
            y = my;
            for(x=mx;x<(ax-1);++x) {
                grid[y][x] &= ~ed;
            }    
        } else if(dy > 1) {
            x = mx;
            for(y=my;y<(ay-1);++y) {
                grid[y][x] &= ~sd;
            }
		}		
		
        return;
	}
	
    if(dy > dx) {
		wall = horizontal;
	} else if(dx > dy) {
		wall = vertical;
	} else {
		wall = (uint8_t) (rand() % 1);
	}

    xp = (uint8_t) (rand() % (ax-mx-(wall == vertical)))+mx;
    yp = (uint8_t) (rand() % (ay-my-(wall == horizontal)))+my;

    x=xp;y=yp;

    if(wall == horizontal) {
        grid[y][x] &= ~sd;
        //drawMaze();
        
        divide(mx, my, ax, y+1);
        divide(mx, y+1, ax, ay);      
       
        
	} else {
        grid[y][x] &= ~ed;
        //drawMaze();

        divide(mx, my, x+1, ay);
        divide(x+1, my, ax, ay);

	}


	
	return;

}




int main(void) {

	uint8_t x,y;
	
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear screen
	//rand init, using raster line value as a seed
	srand(PEEK(RASTER));

	memset(grid, 6, height*width*sizeof(grid[0]));

	
	divide(0, 0, width, height); 

	drawMaze();

	cgetc();
	

	return EXIT_SUCCESS;
}
