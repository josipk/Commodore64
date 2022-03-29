/************************************** 
* CC65 - MicroPong in C - MultiChar   *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 micro_pong_multichar.c -o micro_pong_multichar.prg

#include "/usr/share/cc65/include/stddef.h"
#include "/usr/share/cc65/include/stdio.h"
#include "/usr/share/cc65/include/stdint.h"
#include "/usr/share/cc65/include/stdlib.h"
#include "/usr/share/cc65/include/conio.h"
#include "/usr/share/cc65/include/c64.h"
#include "/usr/share/cc65/include/peekpoke.h"
#include "/usr/share/cc65/include/cc65.h"
#include "/usr/share/cc65/include/string.h"

unsigned char* T = (char *) 0xd018;
unsigned char KEYREG = 0xCB;

uint8_t arena[8] = {255,0,0,0,0,0,0,255};
uint8_t arena2[8] = {255,0,174,170,202,174,0,255};
uint8_t micro3[8] = {0,108,108,110,124,192,0,0};

uint8_t ball_x=3;
uint8_t ball_y=2;
uint8_t ball_dx=1;
uint8_t ball_dy=1;
uint8_t ball_hx=0;
uint8_t ball_hy=0;


uint8_t bat_l=1;
uint8_t bat_r=3;

uint8_t score_l=0;
uint8_t score_r=0;

uint8_t keypause = 0;
uint8_t kp_counter = 0;

void writePos(int pos) {
	POKE(0x3000+pos,arena[pos]);  //0x3200 -> 12800 / 64 = 200
}

uint8_t getBitXY(int x,int y) {

	uint8_t xx2 = x % 8;
	uint8_t pos = y;	
	uint8_t val = arena[pos] & (1 << (7-xx2));
	
	if(val >0) {
		return 1;
	} else {
		return 0;
	}	

}

void setBitXY(int x,int y) {

	uint8_t xx2 = x % 8;
	uint8_t pos = y;	
	arena[pos] = arena[pos] | (1 << (7-xx2));
    writePos(pos); 
}


void clearBitXY(int x,int y) {

	uint8_t xx2 = x % 8;
	uint8_t pos = y;	
	arena[pos] = arena[pos] & ~(1 << (7-xx2));
	writePos(pos); 

}


void setupChars(void) {
	
	unsigned int i;
	

    //Turn off KB and IO
    //printf("turn off keyboard and IO\n");
    POKE(56334, PEEK(56334) & 254);
    POKE(1u, PEEK(1u) & 251);


    //copy charset to ram
    //printf("copying charset to ram at 12288\n"); 0x3000
    for (i=0; i<128; i++)
    {
        memcpy(12288, 53248, 8*i);
    }

    //turn back IO and Keyboard
    //printf("turning back on keyboard and io\n");
    POKE(1, PEEK(1) |4);
    POKE(56334, PEEK(56334) |1);

    //printf("pointing VIC 2 to new charset location\n");
    POKE(53272, (PEEK(53272) & 240) | 12); // bank 12, second to last



	for(i=0; i<8; i++) {
		POKE(12288+i, arena[i]);  //0x3200 -> 12800 / 64 = 200
	}
	
	for(i=0; i<8; i++) {
		POKE(12296+i, arena2[i]);  //0x3200 -> 12800 / 64 = 200
	}

	for(i=0; i<8; i++) {
		POKE(12304+i, micro3[i]);  //0x3200 -> 12800 / 64 = 200
	}	

		

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
	makeSound();
	//for(t=0;t<100;t++) {}
}

void doScores(int addto) {

	unsigned int i;

	if(addto == 1) {
		++score_l;
	} else if(addto == 2) {
		++score_r;
	}


	if(addto > 0) {
	
		for(i=120; i<320; i++) {
			POKE(0xd800+i,2); 
			POKE(0x0400+i,1); 
		}


		delay();
		
		for(i=120; i<320; i++) {
			POKE(0xd800+i,1); 
			POKE(0x0400+i,0); 
		}

		
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
		
		if(ball_y >= 6) { ball_y=6; ball_dy=-ball_dy; }
		if(ball_y <= 1) { ball_y=1; ball_dy=-ball_dy; }


		//this part will end current game a calcualte score		
		if(ball_x >= 7) { ball_dx=-ball_dx;  doScores(1); }
		if(ball_x <= 0) { ball_dx=-ball_dx;  doScores(2); }


}



void setBats(void) {

		unsigned int i;

		for(i=bat_l; i<bat_l+2; i++) {
			setBitXY(0,i);
		}			

		for(i=bat_r; i<bat_r+2; i++) {
			setBitXY(7,i);
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
				clearBitXY(0,bat_l+2);

			}	
			
			if(bat_r < 5) {
				clearBitXY(7,bat_r);
				bat_r = bat_r+1; 
				setBitXY(7,bat_r+1);				
			}	

	}

	//s
	if (k1==13) {

			if(bat_l < 5) {
				clearBitXY(0,bat_l);
				bat_l = bat_l+1; 
				setBitXY(0,bat_l+1);

			}

			if(bat_r > 1) {
				bat_r = bat_r-1; 
				setBitXY(7,bat_r);
				clearBitXY(7,bat_r+2);						
			}


	}	
	



}


void setUpInitArena(void) {

	setBats();
	ball_x=3;ball_y=2;ball_dx=1;ball_dy=1;
	setBitXY(ball_x,ball_y);
	ball_hx = ball_x;ball_hy = ball_y;		


}


void drawScreen(void) {

	unsigned int i=0;

	gotoxy(0,0);
	textcolor(1);
	printf(" b - pong\n");

	textcolor(5);	
	printf("**********\n");
	
	textcolor(7);
	gotoxy(0,2);
	printf(" %i - %i\n", score_l, score_r);

	for(i=120; i<320; i++) {
		POKE(0xd800+i,1); 
		POKE(0x0400+i,0); 
	}	
	
	
}

int main(void) {

	unsigned int c1=0;
	unsigned int c2=0;	
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear screen

	setupChars();

	drawScreen();

	setUpInitArena();

	
	while(1) {	
		
		//read keys
		if(c2 % 60 == 0) { moveBall(); }
		if(c1 % 20 == 0) { checkKeyPress();}
		++c1;++c2;
		
	}
	
	return EXIT_SUCCESS;
}
