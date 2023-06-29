/************************************** 
* CC65 More Ships on Waves in C       *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 waves_ships_m.c -o waves_ships_m.prg

#include "/usr/share/cc65/include/stddef.h"
#include "/usr/share/cc65/include/stdio.h"
#include "/usr/share/cc65/include/stdint.h"
#include "/usr/share/cc65/include/stdlib.h"
#include "/usr/share/cc65/include/c64.h"
#include "/usr/share/cc65/include/peekpoke.h"

#define UTXT 0xd018 //53272
#define SPR 0xD000 //53248

char wave[13] = {239,210,198,195,196,197,247,197,196,195,198,210,239};
char ship[64] = {0,0,0,2,0,0,3,128,0,1,192,0,1,240,0,1,252,0,1,255,0,1,255,192,1,255,240,1,255,252,1,85,86,1,0,0,1,0,0,170,0,10,42,128,42,42,170,170,10,170,170,10,170,168,2,170,168,0,170,160,0,0,0,0};

uint8_t y[2]={120,120};
uint8_t x[2]={90,90};
uint8_t xp[2]={1,1};
uint8_t go[2]={0,0};
uint8_t speed[2]={1,1};

void restartShipPos(uint8_t p) {

	uint8_t i=0;

	y[p] = (uint8_t) ((rand() % 140) + 80);
	go[p] = (uint8_t) (rand() % 14);
	speed[p] = (uint8_t) (rand() % 3) +1;	
	x[p]=90;
    xp[p]=1;

	//printf("[%u:%u] ", p, go[p]);

		
	POKE(SPR + (p*2), x[p]); 
	POKE(SPR + (p*2+1), y[p]);
	POKE(SPR + 16, PEEK(SPR + 16) | (xp[p] << p));	

}

void initShipPos(void) {

	uint8_t i=0;

	y[0] = (uint8_t) ((rand() % 140) + 80);
	y[1] = (uint8_t) ((rand() % 140) + 80);

	go[0] = (uint8_t) (rand() % 14);
	go[1] = (uint8_t) (rand() % 14);

	speed[0] = (uint8_t) (rand() % 3) + 1;
	speed[1] = (uint8_t) (rand() % 3) + 1;

	//printf("%u %u", go[0], go[1]);

	x[0]=90;
	x[1] =90;
	
    xp[0]=1;
    xp[1]=1;

	for(i=0; i<2; i++) {	
		POKE(SPR + (i*2), x[i]); 
		POKE(SPR + (i*2+1), y[i]);
		POKE(SPR + 16, PEEK(SPR + 16) | (xp[i] << i));	
	}


}

void setupShip(void) {

	unsigned int i;
	
	POKE(SPR + 21, 3); //enable first two sprites
	POKE(0x07F8, 200);  //0x07F8 = 2040, frame to read
	POKE(0x07F9, 201);  //0x07F8 = 2040, frame to read

	for(i=0; i<64; i++) {
		POKE(0x3200+i,ship[i]);
	}
	
	for(i=0; i<64; i++) {
		POKE(0x3240+i,ship[i]);
	}	

	POKE(SPR + 29, 0); 
	POKE(SPR + 23, 0); 

	POKE(SPR + 37, 5); 
	POKE(SPR + 38, 1); 

	POKE(SPR + 39, 9); 
	POKE(SPR + 28, 7); 

	initShipPos();
}

void moveShip(void) {

	uint8_t i=0;
	
	for(i=0; i<2; i++) {
	
		if(go[i] == 1) {

			//--x[i];
			x[i] = x[i] - speed[i];
			
			POKE(SPR + (2*i), x[i]);
			
			if(x[i] == 0 && xp[i] == 1) {

					xp[i]=0;
					x[i]=255;
					
					POKE(SPR + (2*i), x[i]);
					
					POKE(SPR + 16, PEEK(SPR + 16) &  (255 - (1 << i)));		
				
			} else if(x[i] <= 5 && xp[i] != 1) {
				
					restartShipPos(i);
				
			} 			
			
		} else {
			restartShipPos(i);
		}
	}
	
		
}

int main(void) {

	unsigned int c=0;
	uint8_t i=0;
	uint8_t j=0;
			
	POKE(UTXT, 20); //set big petscii chars!!!

	
	setupShip();
	

	while(1) {	
		
		printf(wave);
		if(c % 3 == 0) { moveShip(); }
		++c;
	}
	
	return 0;
}
