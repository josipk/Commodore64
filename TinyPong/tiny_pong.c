/************************************** 
* CC65 Tiny-Pong in C                 *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 tiny_pong.c -o tiny_pong.prg

#include "/usr/share/cc65/include/stddef.h"
#include "/usr/share/cc65/include/stdio.h"
#include "/usr/share/cc65/include/stdint.h"
#include "/usr/share/cc65/include/stdlib.h"
#include "/usr/share/cc65/include/conio.h"
#include "/usr/share/cc65/include/c64.h"
#include "/usr/share/cc65/include/peekpoke.h"
#include "/usr/share/cc65/include/cc65.h"

unsigned char* T = (char *) 0xd018;
unsigned char KEYREG = 0xCB;
#define SPR 0xD000 //53248

uint8_t sprite[64] = {255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,0};
uint8_t sprite2[64] = {255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,47,128,2,40,128,2,72,128,2,136,128,3,136,128,2,136,128,2,72,128,2,40,128,2,47,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,0};


uint8_t ball_x=4;
uint8_t ball_y=4;
uint8_t ball_dx=1;
uint8_t ball_dy=1;
uint8_t ball_hx=0;
uint8_t ball_hy=0;


uint8_t bat_l=5;
uint8_t bat_r=10;

uint8_t score_l=0;
uint8_t score_r=0;

uint8_t x=30;
uint8_t y=60;
uint8_t xp=0;
uint8_t dy=1;
uint8_t dx=1;

int move_sprite=-1;
uint8_t keypause = 0;
uint8_t kp_counter = 0;

void writePos(int pos) {
	POKE(0x3200+pos,sprite[pos]);  //0x3200 -> 12800 / 64 = 200
}

uint8_t getBitXY(int x,int y) {

	uint8_t xx = (uint8_t) (x/8);
	uint8_t xx2 = x % 8;
	uint8_t pos = y*3+xx;	
	uint8_t val = sprite[pos] & (1 << (7-xx2));
	
	if(val >0) {
		return 1;
	} else {
		return 0;
	}	

}

void setBitXY(int x,int y) {

	uint8_t xx = (uint8_t) (x/8);
	uint8_t xx2 = x % 8;
	uint8_t pos = y*3+xx;	
	
	sprite[pos] = sprite[pos] | (1 << (7-xx2));

    writePos(pos); 
}


void clearBitXY(int x,int y) {

	uint8_t xx = (uint8_t) (x/8);
	uint8_t xx2 = x % 8;
	uint8_t pos = y*3+xx;	

	sprite[pos] = sprite[pos] & ~(1 << (7-xx2));

	writePos(pos); 

}



void initSpritePos(void) {

	xp=0;
	x=30;
	y=80;

	//printf("%u ",y);
		
	POKE(SPR, x); 
	POKE(SPR + 1, y);
	POKE(SPR + 16, xp);	


}

void setupSprite(void) {

	unsigned int i;
	
	POKE(SPR + 21, 3); //enable sprite 1 and 2
	POKE(0x07F8, 200);  //0x07F8 = 2040 
	//POKE(0x07F9, 201);  //0x07F8 = 2040 

	for(i=0; i<64; i++) {
		POKE(0x3200+i,sprite[i]);  //0x3200 -> 12800 / 64 = 200
	}

	for(i=0; i<64; i++) {
		POKE(0x3240+i,sprite2[i]);  //0x3200 -> 12800 / 64 = 200
	}	
	

	POKE(SPR + 29, 0); // sprite double width no
	POKE(SPR + 23, 0); // sprite double height no

	POKE(SPR + 39, 1);  // sprite main color
	POKE(SPR + 28, 0);  // disable multicolor

	initSpritePos();
}




void moveSprite(void) {

	x=x+dx;
	y=y+dy;	
			
	POKE(SPR, x);
	POKE(SPR + 1, y);
	
	
	if(x == 0 && xp == 1) {

		xp=0;
		x=255;
		
		POKE(SPR, x); 
		POKE(SPR + 16, xp);		
	
	} else if(x == 255 && xp != 1) {
	
		xp=1;
		x=0;
		
		POKE(SPR, x); 
		POKE(SPR + 16, xp);
	
	} 
	
	
	if(y >= 228 || y <= 50) { dy=-dy; }
	if((x >= 65 && xp==1) || (x <= 24 && xp==0)) { dx=-dx; }
		
}

void batSound(void) {

	unsigned int i;


	SID.v1.ctrl  = 0x10;
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x09; 	// Attack/decay voice 1
	
	SID.v1.freq  = 0x1125;	// Frequency 
	SID.v1.ctrl  = 0x11;	// Control voice 1
	for (i = 0 ; i < 50 ; i++) {}
	SID.v1.ctrl  = 0x10;	

}


void makeSound(void) {

	const int scale[] = {
		0x1125,	0x133F,	0x159A,	0x16E3,	
		0x19B1, 0x1CD6,	0x205E,	0x22AF
	};

	unsigned int i;
	unsigned char t;
	
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x09; 	// Attack/decay voice 1
	
	for (t = 0 ; t < sizeof(scale) / 2; t++) {
		SID.v1.freq  = scale[t];	// Frequency 
		SID.v1.ctrl  = 0x11;	// Control voice 1
		for (i = 0 ; i < 200; i++) {}
		SID.v1.ctrl  = 0x10;
		for (i = 0 ; i < 10 ; i++) {}
	}		
	//return EXIT_SUCCESS;	


}


void delay(void) {
	unsigned int t=0;
	//for(t=0;t<3000;t++) {}
	makeSound();
}

void doScores(int addto) {

	if(addto == 1) {
		++score_l;
	} else if(addto == 2) {
		++score_r;
	}
	
	if(addto > 0) {
	
		POKE(0x07F8, 201);
	
		delay();
		
		POKE(0x07F8, 200);
		
		
	}
	
	textcolor(7);
	gotoxy(0,2);
	printf(" %i - %i\n", score_l, score_r);


}

void moveBall(void) {

		
		ball_x = ball_x + ball_dx;
		ball_y = ball_y + ball_dy;		

		//here we will check for collision with a bats
		if(getBitXY(ball_x,ball_y) > 0) {
			//we have a collision	
			ball_dx=-ball_dx;
			ball_x = ball_hx + ball_dx;
			batSound();
		} 
				
		clearBitXY(ball_hx,ball_hy);
		
		setBitXY(ball_x,ball_y);		
		
		ball_hx = ball_x;ball_hy = ball_y;
		
		if(ball_y >= 19) { ball_y=19; ball_dy=-ball_dy; }
		if(ball_y <= 1) { ball_y=1; ball_dy=-ball_dy; }


		//this part will end current game a calcualte score		
		if(ball_x >= 23) { ball_dx=-ball_dx; doScores(1); }
		if(ball_x <= 0) { ball_dx=-ball_dx; doScores(2); }


}



void setBats(void) {

		unsigned int i;

		for(i=bat_l; i<bat_l+6; i++) {
			setBitXY(0,i);
		}			

		for(i=bat_r; i<bat_r+6; i++) {
			setBitXY(23,i);
		}

		return;			

}

void checkKeyPress(void) {
	
	uint8_t k1 = (int) PEEK(KEYREG);
	
	//w
	if (k1==9) {


			if(bat_l > 1) {
				bat_l = bat_l-1; 
				setBitXY(0,bat_l);
				clearBitXY(0,bat_l+7);

			}	
			
			if(bat_r < 13) {
				clearBitXY(23,bat_r);
				bat_r = bat_r+1; 
				setBitXY(23,bat_r+6);				
			}	

	}

	//s
	if (k1==13) {

			if(bat_l < 13) {
				clearBitXY(0,bat_l);
				bat_l = bat_l+1; 
				setBitXY(0,bat_l+6);

			}

			if(bat_r > 1) {
				bat_r = bat_r-1; 
				setBitXY(23,bat_r);
				clearBitXY(23,bat_r+7);						
			}


	}	
	
	//space
	if (k1==60 && keypause ==0)  {
		move_sprite=-move_sprite;
		keypause=1;
	}
	
	//esc
	if (k1==63) {
		//end game!!!!!
		move_sprite=-1;
		x=30;
		y=80;
		xp=0;
		POKE(SPR, x);
		POKE(SPR + 1, y);
		POKE(SPR + 16, xp);
			
	}
	
	
	//gotoxy(30,0);
	//printf("%i", k1);
	
	//q
	if (k1==62 && keypause ==0) {
		keypause=1;
		if(PEEK(SPR + 29) == 0) {

			POKE(SPR + 29, 1); // sprite double width no
			POKE(SPR + 23, 1); // sprite double height no		
		
		} else {
			POKE(SPR + 29, 0); // sprite double width no
			POKE(SPR + 23, 0); // sprite double height no		
		
		}
			
	}	
	
	if(keypause==1) {
		++kp_counter;
		if(kp_counter > 10) {
			keypause=0;
			kp_counter=0;
		}
	}	

}


void setUpInitArena(void) {

	setBats();
	ball_x=4;ball_y=4;ball_dx=1;ball_dy=1;
	setBitXY(ball_x,ball_y);
	ball_hx = ball_x;ball_hy = ball_y;		


}


void drawScreen(void) {

	gotoxy(0,0);
	
	textcolor(1);
	printf("tiny - pong\n");

	textcolor(5);	
	printf("***********\n");
	
	textcolor(7);
	gotoxy(0,2);
	printf(" %i - %i\n", score_l, score_r);
	
	textcolor(12);
	gotoxy(0,10);
	printf("q - change size\n");	
	printf("space - start/stop move arena\n");
	printf("esc - default arena position\n");		
	
	
}

int main(void) {

	unsigned int c1=0;
	unsigned int c2=0;	
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear screen

	drawScreen();

	setUpInitArena();

	setupSprite();
	
	while(1) {	
		
		//read keys
		if(c2 % 30 == 0) { moveBall(); }
		if(c1 % 20 == 0) { checkKeyPress();}
		if(move_sprite > 0 && c2 % 15 == 0) { moveSprite(); }
		++c1;++c2;
		
	}
	
	return EXIT_SUCCESS;
}
