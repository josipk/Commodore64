/************************************** 
* MandelbrotSet 3                     *
* in C                                *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 mandelbrot3.c runtime.lib -o mandelbrot3.prg

#include "/usr/share/cc65/include/stddef.h"
#include "/usr/share/cc65/include/stdio.h"
#include "/usr/share/cc65/include/stdint.h"
#include "/usr/share/cc65/include/stdlib.h"
#include "/usr/share/cc65/include/conio.h"
#include "/usr/share/cc65/include/string.h"
#include "/usr/share/cc65/include/c64.h"
#include "/usr/share/cc65/include/peekpoke.h"
#include "/usr/share/cc65/include/cc65.h"
#include "float.h"
#include "math.h"

unsigned char* T = (char *) 0xd018;
char strbuf[0x20];

uint8_t rows=25;
uint8_t columns=40;
uint8_t colors_max=5;  //only 6 color will be used to plot image!

uint16_t screen_loc=1024;
uint16_t color_loc=55296;

//char petscii[16] = {239,210,198,195,196,197,247,197,196,195,198,210,239,198,210,239};
char petscii[16] = {230,232,219,214,241,242,243,230,232,219,214,241,242,243,242,243};

float aa,bb,cc,dd,ff;

unsigned int loopColorArray(unsigned int rx, unsigned int ry) {

	unsigned int i;
	float x=0;
	float y=0;
	float k=0;
	float xt=0;
	
	//--Mandlebrot Area------------------
	//X: -1.5, 1
	//Y: -1, 0
	//we map rx and ry screen coordinates to Mandlebrot Area Koordinates
	float g1 = fmul(itof(rx),aa);  
	float g2 = fdiv(g1,itof(columns));	
	float xz = fsub(g2,bb);	

	float h1 = fmul(itof(ry),cc);
	float h2 = fdiv(h1,itof(rows));	
	float yz = fsub(h2,dd);		
	//-----------------------------------
	
	for(i=0; i<=colors_max; ++i) { 

		k = fadd(fmul(x,x),fmul(y,y));
	
		if(fcmpgt(k,ff)) { 
			break; 
		}
		
		xt = fadd(fsub(fmul(x,x),fmul(y,y)), xz);
		y = fadd(fmul(fmul(x,y),cc),yz);
		x = xt;
		
	}
	
	return (i-1);
}

void generateMandlebrotSet(void) {

	unsigned int px,py;
	uint16_t u=0;
	uint8_t c;

	for(py=0; py<rows; ++py) {
			
		for(px=0; px<columns; ++px) {

			//in case that we do not use whole screen area 
			//u = (py*40)+px;	
			c = loopColorArray(px,py);
			//printf("%i ", c);
			//--c;
			
			//invert colors?
			c=colors_max-c;
			
			//POKE(screen_loc+u, 230);
            POKE(screen_loc+u, 201+c);
			//POKE(screen_loc+u, petscii[c]);
			POKE(color_loc+u, c);
			//in case that we use whole screen area we can just increment by one!
			++u;
			
		}	
	}
	
}



int main(void) {

    //120 xz = px*3.5/40-2.5
    //130 yz = py*2/25-1

    //we zoom out little bit here
    aa=fdiv(itof(45),itof(10));
	bb=fdiv(itof(25),itof(10));
	cc=itof(4);
    dd=itof(2);
	ff=itof(4);
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear main screen

	generateMandlebrotSet();
	
	
	return EXIT_SUCCESS;
}
