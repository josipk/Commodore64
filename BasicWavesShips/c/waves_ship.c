/************************************** 
* CC65 - Ships on Waves in C          *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 waves_ship.c -o waves_ship.prg

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

uint8_t y=120;
uint8_t x=90;
uint8_t xp=1;


void initShipPos(void) {
	
	xp=1;
	x=90;
	y=(rand() % 140) + 80;
	
	POKE(SPR,x);
	POKE(SPR+1,y);
	POKE(SPR+16,xp);
		
}

void setupShip(void) {

	unsigned int i;
	
	POKE(SPR + 21, 1); //enable sprite 1
	POKE(0x07F8, 200);  //0x07F8 = 2040 

	for(i=0; i<64; i++) {
		POKE(0x3200+i,ship[i]);  //0x3200 -> 12800 / 64 = 200
	}

	POKE(SPR + 29, 0); // sprite double width no
	POKE(SPR + 23, 0); // sprite double height no

	POKE(SPR + 37, 5);  // sprite multicolor 1
	POKE(SPR + 38, 1);  // sprite multicolor 2

	POKE(SPR + 39, 9);  // sprite main color
	POKE(SPR + 28, 7);  // enable multicolor

	initShipPos();
	

}



void moveShip(void) {

	--x;
	POKE(SPR, x);
	
	if(x==0 && xp == 1) {
	
		xp=0;
		x=255;
		POKE(SPR, x);
		POKE(SPR+16, xp);
		
	} else if(x <= 5 && xp==0) {
		
		initShipPos();
	}	
		
		
}


int main(void) {

	unsigned int c=0;

	POKE(UTXT, 20); //set big petscii chars!!!
	
	setupShip();
	
	while(1) {	
		printf(wave);
		if(c % 3 == 0) { moveShip(); }
		++c;
	}
	return 0;
}
