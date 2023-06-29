/************************************** 
* CC65 Maze Demo 					  * 
* Recursive Backtracker Algo.		  *
* JOSIP RETRO BITS, 2023              *
**************************************/
//Build: cl65 maze3.c -o maze3.prg

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <c64.h>
#include <peekpoke.h>
#include <cc65.h>

unsigned char* T = (char *) 0xd018;
#define RASTER 0xD012

uint8_t dp[1000] = {}; //directions
unsigned int sp[1000] = {}; //stack
unsigned int sc=0; //stack counter
uint8_t we_are_done = 0;
uint8_t spop = 0; //are we pop the stack?

	uint8_t chr0=66;
	uint8_t chr1=67;

	uint8_t chr2=112;
	uint8_t chr3=110;
	uint8_t chr4=109;
	uint8_t chr5=125;

	uint8_t chr6=107;
	uint8_t chr7=115;
	uint8_t chr8=113;
	uint8_t chr9=114;
	uint8_t chr9p=91;

int dirlookup[16][5] = {
	{0,0,0,0,0},
	{1,1,0,0,0},
	{1,2,0,0,0},
	{2,2,1,0,0},
	{1,4,0,0,0},
	{2,4,1,0,0},
	{2,4,2,0,0},
	{3,4,2,1,0},
	{1,8,0,0,0},
	{2,8,1,0,0},
	{2,8,2,0,0},
	{3,8,2,1,0},			
	{2,8,4,0,0},
	{3,8,4,1,0},
	{3,8,4,2,0},
	{4,8,4,2,1}									
	};



void delay(void) {
	unsigned int t=0;
	for(t=0;t<1000;t++) {}
}

uint8_t getRandomDirection(uint8_t ds) {

	 uint8_t sd = ds^15; //15-ds
	 uint8_t n = dirlookup[sd][0];
	 uint8_t m = (uint8_t) (rand() % n);
	 return dirlookup[sd][m+1];

} 

void markNeighbours(unsigned int p) {

	if(p>=40) { dp[p-40] |= 4; }
	if(p+40<1000) { dp[p+40] |= 1; }
	if(p>=1) { dp[p-1] |= 8; }
	if(p+1<1000) { dp[p+1] |= 2; }

}


void nextMove(void) {

	/*
	uint8_t chr0=66;
	uint8_t chr1=67;

	uint8_t chr2=112;
	uint8_t chr3=110;
	uint8_t chr4=109;
	uint8_t chr5=125;

	uint8_t chr6=107;
	uint8_t chr7=115;
	uint8_t chr8=113;
	uint8_t chr9=114;
	uint8_t chr9p=91;
	*/

	unsigned int p2;
	uint8_t cdh,chp,b1,b2,b3,b4,b5,b6;
	uint8_t nextd,lastd;
	uint8_t blockddir;
	uint8_t na,nb,nc;

	unsigned int p=sp[sc];
    uint8_t y= (uint8_t) (p/40);
    uint8_t x= (uint8_t) p-(y*40);
	uint8_t ds=dp[p];
	    
	if(ds==15) {
		//dead end
		POKE(55296+p,15);
		sp[sc]=0;
		--sc;
		spop=1;
		if(sc==0) { we_are_done = 1; }
		return;
	}
	
	nextd = getRandomDirection(ds); 
	blockddir = 0;

	if(nextd & 1) { 
		if(y==0) { 
			dp[p] |= 1;
			return;
		} else {
			y=y-1;
			blockddir=4;
		}	
	} else if(nextd & 2) { 
		if(x==0) { 
			dp[p] |= 2;
			return;
		} else {
			x=x-1;
			blockddir=8;
		}	
	} else if(nextd & 4) { 
		if(y==24) { 
			dp[p] |= 4;
			return;
		} else {
			y=y+1;
			blockddir=1;
		}	
	} else if(nextd & 8) { 
		if(x==39) { 
			dp[p] |= 8;
			return;
		} else {
			x=x+1;
			blockddir=2;
		}	
	}

	//current character
	cdh=(nextd==1 || nextd==4)*chr0+(nextd==2 || nextd ==8)*chr1;

	//previous character
	if(spop==0) { 
		b1=((lastd==2 && nextd==4) || (lastd==1 && nextd==8))*chr2;
		b2 =((lastd==8 && nextd==4) || (lastd==1 && nextd==2))*chr3;
		b3=((lastd==2 && nextd==1) || (lastd==4 && nextd==8))*chr4;
		b4=((lastd==8 && nextd==1) || (lastd==4 && nextd==2))*chr5;
		b5=((lastd==1 && nextd==1) || (lastd==4 && nextd==4))*chr0;
		b6=((lastd==2 && nextd==2) || (lastd==8 && nextd==8))*chr1;
		
		chp=b1+b2+b3+b4+b5+b6;
	} else {
		/*
		 *chr6 -> |-
		 *chr7 -> -|
		 *chr8 -> _up
		 *chr9 -> -down  
		 * chr9p -> +   
		 **/

		/*
		 *  1
		 * 2 8
		 *  4
		 * */
		 
		if(nextd & 1) { 
			
			na=PEEK(1024+p-1); 
			nb=PEEK(1024+p+40);
			nc=PEEK(1024+p+1);

			/*
			POKE(55296+p-1,4);
			POKE(55296+p+40,7);
			POKE(55296+p+1,2);

			delay();
			*/
			if(na==chr0 || na==chr5 || na==chr3 || na==32) { chp=chr6; }
			else if(nc==chr0 || nc==chr4 || nc==chr2 || nc==32) { chp=chr7; }
			else if(nb==chr0 || nb==chr5 || nb==chr4 || nb==chr6 || nb==chr7 || nb==chr8 ) { chp = chr9p; }
			else { chp = chr8; }
		
			
		} else if(nextd & 2) { 

			na=PEEK(1024+p+40);
			nb=PEEK(1024+p+1);
			nc=PEEK(1024+p-40);
			
			/*
			POKE(55296+p+40,4);
			POKE(55296+p+1,7);
			POKE(55296+p-40,2);
		
			delay();
			*/
			
			if(na==chr1 || na==chr2 || na==chr3 || na==32) { chp=chr8; }
			else if(nc==chr1 || nc==chr5 || nc==chr4 || nc==32) { chp=chr9; }
			else if(nb==chr1 || nb==chr5 || nb==chr3 || nb==chr7 || nb==chr9 || nb==chr8) { chp = chr9p; }
			else { chp = chr7; }


		} else if(nextd & 4) { 

			na=PEEK(1024+p+1);
			nb=PEEK(1024+p-40);
			nc=PEEK(1024+p-1);

			/*
			POKE(55296+p+1,4);
			POKE(55296+p-40,7);
			POKE(55296+p-1,2);


			delay();
			*/	
			

			if(na==chr0 || na==chr4 || na==chr2 || na==32) { chp=chr7; }
			else if(nc==chr0 || nc==chr5 || nc==chr3 || nc==32) { chp=chr6; }
			else if(nb==chr0 || nb==chr3 || nb==chr2 || nb==chr7 || nb==chr9 || nb==chr6) { chp = chr9p; }
			else { chp = chr9; }


		} else if(nextd & 8) { 

			na=PEEK(1024+p-40);
			nb=PEEK(1024+p-1);
			nc=PEEK(1024+p+40);

			//POKE(55296+p-40,4);
			//POKE(55296+p-1,7);
			//POKE(55296+p+40,2);


			if(na==chr1 || na==chr5 || na==chr4 || na==32) { chp=chr9; }
			else if(nc==chr1 || nc==chr2 || nc==chr3 || nc==32) { chp=chr8; }
			else if(nb==chr1 || nb==chr2 || nb==chr4 || nb==chr6 || nb==chr9 || nb==chr8) { chp = chr9p; }
			else { chp = chr6; }

		}		 

	}

	p2=y*40+x;
	sc=sc+1;
	sp[sc]=p2;
	dp[p2] |= blockddir;
	
	lastd=nextd;
	
	POKE(1024+p,chp); 
	POKE(1024+p2,cdh);

	//mark taken directions for all 4 neighbours
	markNeighbours(p2);

	spop=0;
	return;

}




int main(void) {

	uint8_t x,y;
	unsigned int p;
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear screen

	x=20;y=10;sc=0;
	p=y*40+x;
	sp[sc]=p;
	POKE(1024+p,chr0);

	//rand init, using raster line value as a seed
	srand(PEEK(RASTER));
	
	
	while(!we_are_done) {	
		
		nextMove();
		//delay();
				
	}
	
	cgetc();
	

	return EXIT_SUCCESS;
}
