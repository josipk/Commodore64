/************************************** 
* CC65 Maze Demo 					  * 
* Recursive Backtracker Algo.		  *
* JOSIP RETRO BITS, 2023              *
**************************************/
//Build:
//cl65 maze6spc2.c -o maze6spc2.prg -t c64 -C c64_g.cfg
//start sys4109

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

uint8_t dp[1000] = {}; //directions
unsigned int sp[1000] = {}; //stack
unsigned int sc=0; //stack counter

unsigned int tail[5] = {}; //stack
uint8_t tailc=0;

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

	/*
	uint8_t chr0=194; //66;
	uint8_t chr1=195; //67;

	uint8_t chr2=240;	//112;
	uint8_t chr3=238;	//110;
	uint8_t chr4=237;	//109;
	uint8_t chr5=253;	//125;

	uint8_t chr6=235;	//107;
	uint8_t chr7=243;	//115;
	uint8_t chr8=241;	//113;
	uint8_t chr9=242;	//114;
	uint8_t chr9p=219;	//91;
	*/


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


const unsigned char mazecharset[11][9] = { 
	{66,126,126,126,126,126,126,126,126},
	{67,0,255,255,255,255,255,255,0},
	{91,126,255,255,255,255,255,255,126},
	{112,0,127,127,127,127,127,127,126},
	{113,126,255,255,255,255,255,255,0},
	{114,0,255,255,255,255,255,255,126},
	{115,62,254,254,254,254,254,254,126},
	{107,126,127,127,127,127,127,127,126},
	{109,126,127,127,127,127,127,127,0},
	{110,0,254,254,254,254,254,254,126},
	{125,126,254,254,254,254,254,254,0}
};


void setupChars(void) {

	/*
	    Bits #1-#3: In text mode, pointer to character memory (bits #11-#13), relative to VIC bank, memory address $DD00. 
	    * Values:

        %000x, 0: $0000-$07FF, 0-2047.

        %001x, 1: $0800-$0FFF, 2048-4095.

        %010x, 2: $1000-$17FF, 4096-6143.

        %011x, 3: $1800-$1FFF, 6144-8191.

        %100x, 4: $2000-$27FF, 8192-10239.

        %101x, 5: $2800-$2FFF, 10240-12287.

        %110x, 6: $3000-$37FF, 12288-14335.

        %111x, 7: $3800-$3FFF, 14336-16383.

		Values %010 and %011 in VIC bank #0 and #2 select Character ROM instead. 
	 */
	
	
	unsigned int i,j;
	uint16_t char_start_pos = 2048;  //0x8800	
	//-----------------------------------------
    //Turn off KB and IO
    //printf("turn off keyboard and IO\n");
    POKE(56334, PEEK(56334) & 254);
    POKE(1u, PEEK(1u) & 251);
	

    //copy charset to ram
    //printf("copying charset to ram at 12288\n"); 0x3000
    for (i=0; i<128; i++)
    {
        memcpy(char_start_pos, 53248, 8*i);
    }

	//mazecharset
	for(i=0; i<11; i++) {
		for(j=0; j<8; j++) {
			POKE(char_start_pos+(mazecharset[i][0]*8)+j, mazecharset[i][j+1]);
		}	
	}

    //turn back IO and Keyboard
    //printf("turning back on keyboard and io\n");
    POKE(1, PEEK(1) |4);
    POKE(56334, PEEK(56334) |1);

    //printf("pointing VIC 2 to new charset location\n");
    POKE(53272, (PEEK(53272) & 240) | 2); // (1110)

}



void delay(void) {
	unsigned int t=0;
	for(t=0;t<200;t++) {}
}

uint8_t getRandomDirection(uint8_t ds) {

	 uint8_t sd = ds^15; //15-ds
	 uint8_t n = dirlookup[sd][0];
	 uint8_t m = (uint8_t) (rand() % n);
	 return dirlookup[sd][m+1];

} 

void markNeighbours(unsigned int p) {

	if(p>39) { dp[p-40] |= 4; }
	if(p<960) { dp[p+40] |= 1; }
	if(p>0) { dp[p-1] |= 8; }
	if(p<999) { dp[p+1] |= 2; }
	return;
}

void checkTail() {
	
	uint8_t i;

	POKE(55296+tail[0],0);

	if(tailc>0) { 
		for(i=0;i<tailc-1; ++i) {
			tail[i] = tail[i+1];
			POKE(55296+tail[i],i);
		}	
		--tailc; 
	} 

	return;
}


void addTail(unsigned int p) {

	if(tailc==5) {
		checkTail();
	}
	tail[tailc] = p;
	POKE(55296+tail[tailc],tailc);
	++tailc;
	return;
}


void nextMove(void) {

	unsigned int p2;
	uint8_t cdh,chp,b1,b2,b3,b4,b5,b6;
	uint8_t nextd,lastd;
	uint8_t blockddir;
	uint8_t na,nb,nc;
	//unsigned int prevp;

	unsigned int p=sp[sc];
    uint8_t y= (uint8_t) (p/40);
    uint8_t x= (uint8_t) p-(y*40);
	uint8_t ds=dp[p];

	/*
	if(sc > 0) {
		prevp = sp[sc-1];
	}
	*/
	    
	if(ds==15) {
		//dead end
		//POKE(55296+p,15);
		sp[sc]=0;
		--sc;
		spop=1;
		if(sc==0) { we_are_done = 1; }
		addTail(p);
		return;
		
	} 
	/*
	else {
		
		checkTail();	
		
	}*/
	
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
		
		na=255;
		nb=255;
		nc=255;
		 
		if(nextd & 1) { 
			
			if(p>0) { na=PEEK(1024+p-1);  }
			if(p<960) { nb=PEEK(1024+p+40); }
			if(p<999) { nc=PEEK(1024+p+1); }

			if(na==chr0 || na==chr5 || na==chr3 || na==32) { chp=chr6; }
			else if(nc==chr0 || nc==chr4 || nc==chr2 || nc==32) { chp=chr7; }
			else if(na != 255 && nc != 255 && (nb==chr0 || nb==chr5 || nb==chr4 || nb==chr6 || nb==chr7 || nb==chr8 )) { chp = chr9p; }
			else { chp = chr8; }
		
			
		} else if(nextd & 2) { 

			if(p<960) { na=PEEK(1024+p+40); }
			if(p<999) { nb=PEEK(1024+p+1); }
			if(p>39) {nc=PEEK(1024+p-40); }
			
			if(na==chr1 || na==chr2 || na==chr3 || na==32) { chp=chr8; }
			else if(nc==chr1 || nc==chr5 || nc==chr4 || nc==32) { chp=chr9; }
			else if(na != 255 && nc != 255 && (nb==chr1 || nb==chr5 || nb==chr3 || nb==chr7 || nb==chr9 || nb==chr8)) { chp = chr9p; }
			else if(na == 255) { chp = chr8; }
			else if(nc == 255) { chp = chr9; }
			else { chp = chr7; }

		/*
		 *chr6 -> |-
		 *chr7 -> -|
		 *chr8 -> _up
		 *chr9 -> -down  
		 * chr9p -> +   
		 **/


		} else if(nextd & 4) { 

			if(p<999) { na=PEEK(1024+p+1); }
			if(p>39) {nb=PEEK(1024+p-40); }
			if(p>0) {nc=PEEK(1024+p-1); }

			if(na==chr0 || na==chr4 || na==chr2 || na==32) { chp=chr7; }
			else if(nc==chr0 || nc==chr5 || nc==chr3 || nc==32) { chp=chr6; }
			else if(na != 255 && nc != 255 && (nb==chr0 || nb==chr3 || nb==chr2 || nb==chr7 || nb==chr9 || nb==chr6)) { chp = chr9p; }
			else { chp = chr9; }


		} else if(nextd & 8) { 

			if(p>39) {na=PEEK(1024+p-40); }
			if(p>0) {nb=PEEK(1024+p-1); }
			if(p<960) { nc=PEEK(1024+p+40); }

			if(na==chr1 || na==chr5 || na==chr4 || na==32) { chp=chr9; }
			else if(nc==chr1 || nc==chr2 || nc==chr3 || nc==32) { chp=chr8; }
			else if(na != 255 && nc != 255 && (nb==chr1 || nb==chr2 || nb==chr4 || nb==chr6 || nb==chr9 || nb==chr8)) { chp = chr9p; }
			else if(na == 255) { chp = chr9; }
			else if(nc == 255) { chp = chr8; }
			else { chp = chr6; }
			

		/*
		 *chr6 -> |-
		 *chr7 -> -|
		 *chr8 -> _up
		 *chr9 -> -down  
		 * chr9p -> +   
		 **/
			
			

		}		 

	}

	p2=y*40+x;
	sc=sc+1;
	sp[sc]=p2;
	dp[p2] |= blockddir;
	
	lastd=nextd;
	
	addTail(p);
	
	POKE(1024+p,chp); 
	POKE(1024+p2,cdh);
	
	POKE(55296+p2,5);	
	//POKE(55296+p,15);

	//mark taken directions for all 4 neighbours
	markNeighbours(p2);
	//checkTail();
	
	spop=0;
	return;

}

//waiting for the raster line 9th bit
void syncit(void)
{
    while(!((*(unsigned char*)0xd011) & 0x80)) {} ;
}


int main(void) {

	uint8_t x,y;
	unsigned int p;
	*T = 20; //set big petscii chars!!!

	setupChars();

	clrscr(); //clear screen

	//POKE(53280,14);
	//POKE(53281,6);

	x=0;y=0;sc=0;
	p=y*40+x;
	sp[sc]=p;
	//rand init, using raster line value as a seed
	srand(PEEK(RASTER));
	
	
	while(!we_are_done) {	
		
		nextMove();
		syncit();
				
	}
	
	while(tailc > 0) {
		checkTail();	
	}

	POKE(55296,4);
	POKE(55296+999,4);	
	
	cgetc();
	

	return EXIT_SUCCESS;
}
