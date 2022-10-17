/************************************** 
* Action Maze Chase Game              *
* in C, v0.92                         *
* josip.kalebic@gmail.com, 2022.      *
**************************************/
//Build: cl65 g92.c -o g92.prg

#include "/usr/share/cc65/include/stddef.h"
#include "/usr/share/cc65/include/stdio.h"
#include "/usr/share/cc65/include/stdint.h"
#include "/usr/share/cc65/include/stdlib.h"
#include "/usr/share/cc65/include/conio.h"
#include "/usr/share/cc65/include/string.h"
#include "/usr/share/cc65/include/c64.h"
#include "/usr/share/cc65/include/cc65.h"
#include "/usr/share/cc65/include/peekpoke.h"

unsigned char* T = (char *) 0xd018;

uint16_t screen_loc=1024;
uint16_t color_loc=55296;
uint16_t joystick_loc=56320;

//Enemys parameters
uint8_t zx[10] = {0,0,0,0,0,0,0,0,0,0};
uint8_t zxold[10] = {0,0,0,0,0,0,0,0,0,0};

uint8_t zy[10] ={0,0,0,0,0,0,0,0,0,0};
uint8_t zyold[10] = {0,0,0,0,0,0,0,0,0,0};

uint16_t zold[10] = {0,0,0,0,0,0,0,0,0,0};
uint16_t zoldchar[10] = {95,95,95,95,95,95,95,95,95,95};
uint16_t zoldcolor[10] = {0,0,0,0,0,0,0,0,0,0};

uint8_t zstall[10] = {0,0,0,0,0,0,0,0,0,0};

signed int zdx[10] = {0,0,0,0,0,0,0,0,0,0};
signed int zdy[10] = {0,0,0,0,0,0,0,0,0,0};

uint8_t zcolor=15;
uint8_t zchar=138;
uint8_t zcount=7;
uint8_t zact=0;
uint8_t zdist=18;


//player parameters
uint16_t p, pold;
signed int px,py,pxold,pyold;
uint8_t pcolor=7;
uint8_t pchar[2]={133,134};
uint8_t pcharcnt=0;
uint8_t ppower=100;

//target/collectible items parameters
uint8_t tcolors[6]={3,4,5,8,10,13};
uint8_t tchar=143;
uint8_t tnumber=12;
uint8_t tcollected=0;


//walls/maze parameters
uint8_t wcolor=14;
uint8_t wchar=130; //160;
uint8_t owchar=128; //outter wall char
uint8_t owcolor=15; //outter wall colour

//playground params
uint8_t plgrx=32;
uint8_t plgry=14;
uint8_t plgroffset=4;
uint8_t plbgcolor=0;
uint8_t plbgchar=95;


/*
const unsigned char playground[25][5] = 
{
   {15, 225, 0, 0, 0}, {0, 1, 127, 255, 128}, {0, 5, 0, 0, 140}, {127, 245, 0, 0, 156}, {2, 5, 39, 228, 148}, {114, 5, 180, 36, 148}, {18, 0, 148, 36, 148}, {19, 254, 148, 36, 151}, {18, 8, 16, 36, 144}, {114, 8, 31, 228, 16}, {2, 8, 128, 4, 16}, {2, 0, 191, 247, 240}, {63, 252, 128, 32, 0}, {2, 0, 144, 32, 14}, {2, 1, 147, 231, 250}, {58, 63, 16, 32, 2}, {10, 0, 16, 48, 2}, {10, 0, 17, 241, 250}, {8, 255, 16, 48, 146}, {8, 128, 24, 100, 146}, {8, 128, 8, 108, 146}, {56, 158, 15, 228, 30}, {32, 130, 8, 108, 0}, {32, 130, 8, 108, 128}, {32, 130, 8, 4, 128}
};
*/

/*
const unsigned char playground[25][5] =  {
	{15, 225, 0, 4, 8}, {0, 65, 127, 255, 136}, {0, 65, 1, 0, 140}, {127, 253, 1, 0, 156}, {2, 5, 39, 36, 148}, {114, 1, 180, 36, 148}, {16, 0, 148, 36, 148}, {31, 254, 148, 36, 151}, {18, 0, 16, 36, 144}, {114, 0, 28, 228, 16}, {2, 8, 128, 132, 16}, {0, 8, 191, 247, 240}, {127, 248, 128, 32, 0}, {2, 0, 128, 32, 14}, {2, 0, 159, 39, 250}, {58, 63, 144, 36, 2}, {10, 0, 16, 52, 2}, {10, 0, 19, 245, 250}, {120, 255, 16, 52, 146}, {8, 128, 24, 100, 147}, {8, 128, 8, 100, 146}, {62, 242, 121, 236, 22}, {32, 130, 8, 100, 0}, {32, 130, 8, 116, 128}, {32, 130, 8, 36, 128}
};
*/

const unsigned char playground[25][5] =  {
	{0, 0, 0, 0, 0}, 
	{100, 94, 15, 32, 0}, 
	{4, 66, 8, 32, 4}, 
	{4, 66, 8, 32, 0}, 
	{124, 95, 255, 62, 0}, 
	{0, 66, 2, 16, 0}, 
	{0, 66, 2, 16, 0}, 
	{127, 242, 66, 16, 0}, 
	{18, 2, 64, 16, 0}, 
	{16, 14, 127, 158, 0}, 
	{16, 64, 1, 144, 0}, 
	{31, 243, 244, 16, 0}, 
	{48, 2, 4, 16, 0}, 
	{0, 2, 4, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 16, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0}
};


const unsigned char gamecharset[18][8] = { 
	{126,255,255,255,255,255,255,126}, //0, wall1
	{126,255,255,231,231,255,255,126}, //1, wall2 
	{126,219,129,219,219,129,219,126}, //2 wall3
	{24, 60,126,126,102,102,126, 0},   //3 home1
	{24, 60,126,126,126,102,102,102},  //4 home2
	{56, 56, 16,124,186, 56, 40, 40},//5  player1
	{56, 56, 16,254, 56, 56, 40, 40},//6 player2
	{56, 56, 16,124,186, 56, 40, 68},//7player3
	{56, 56, 16,254, 56, 56, 40, 68},//8player4
	{0,  0, 60,102,126,126,231,231},  //9 enemy1
	{36, 60, 90,165,126, 90,165, 66}, //10 enemy2
	{0, 60, 90,102,102, 90, 60,  0}, //11 target1
	{24, 36, 90,165,165, 90, 36, 24},//12  target2
	{0, 60, 90,102,102, 90, 60,  0},//13target3
	{0, 60,126,126,126, 60,  0,  0}, //14target4
	{0, 60,102, 66,102, 60,  0,  0}, //15target5
	{0, 60,126,102,126, 60,  0,  0}, //16target6
	{0, 60, 66, 90, 66, 60,  0,  0} //17target7
};


//music effects notes
const int scale[] = {
	0x1125,	0x133F,	0x159A,	0x16E3,	
	0x19B1, 0x1CD6,	0x205E,	0x22AF
};


//------------------------------------------------

long map(uint16_t x, uint16_t out_max)
{

  uint16_t  in_min = 0;
  uint16_t  in_max = 127;
  uint16_t  out_min = 0;
  x = (x & 127);
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



void printStatusBar() {
	gotoxy(0,0);printf("power: %i, targets: %i/%i   ", ppower, tcollected ,tnumber);	
}

void setupChars(void) {
	
	/*
	    Bits #1-#3: In text mode, pointer to character memory (bits #11-#13), relative to VIC bank, memory address $DD00. Values:

        %000, 0: $0000-$07FF, 0-2047.

        %001, 1: $0800-$0FFF, 2048-4095.

        %010, 2: $1000-$17FF, 4096-6143.

        %011, 3: $1800-$1FFF, 6144-8191.

        %100, 4: $2000-$27FF, 8192-10239.

        %101, 5: $2800-$2FFF, 10240-12287.

        %110, 6: $3000-$37FF, 12288-14335.

        %111, 7: $3800-$3FFF, 14336-16383.

		Values %010 and %011 in VIC bank #0 and #2 select Character ROM instead. 
	 */
	
	
	unsigned int i,j;
	uint16_t char_start_pos = 14336;	

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


	for(i=0; i<18; i++) {
		for(j=0; j<8; j++) {
			POKE(char_start_pos+(128*8)+(i*8)+j, gamecharset[i][j]);
		}	
	}
	
    //turn back IO and Keyboard
    //printf("turning back on keyboard and io\n");
    POKE(1, PEEK(1) |4);
    POKE(56334, PEEK(56334) |1);

    //printf("pointing VIC 2 to new charset location\n");
    POKE(53272, (PEEK(53272) & 240) | 14); // bank 14, last (1110)

}

void playSound() {

	unsigned int i;
	unsigned char t;
	
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x09; 	// Attack/decay voice 1
	
	for (t = 0 ; t < sizeof(scale) / 2; t++) {
		SID.v1.freq  = scale[t];	// Frequency 
		SID.v1.ctrl  = 0x11;	// Control voice 1
		for (i = 0 ; i < 100; i++) {}
		SID.v1.ctrl  = 0x10;
		for (i = 0 ; i < 100 ; i++) {}
	}		

}

void pickupSound() {

	unsigned int i;
	
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x09; 	// Attack/decay voice 1
	
	SID.v1.freq  = scale[0];	// Frequency 
	SID.v1.ctrl  = 0x11;	// Control voice 1
	for (i = 0 ; i < 100; i++) {}
	SID.v1.ctrl  = 0x10;

}

void loseEnergySound() {

	unsigned int i;
	
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x01; 	// Attack/decay voice 1
	
	SID.v1.freq  = scale[3];	// Frequency 
	SID.v1.ctrl  = 0x11;	// Control voice 1
	for (i = 0 ; i < 10; i++) {}
	SID.v1.ctrl  = 0x10;

}



void playerDeathSound() {

	unsigned int i;
	unsigned char t;
	unsigned int sc;
	
	sc=sizeof(scale);
	
	
	SID.amp      = 0x1F; 	// Volume
	SID.v1.ad    = 0x09; 	// Attack/decay voice 1
	
	for (t = 0 ; t < (sc / 2); t++) {
		SID.v1.freq  = scale[sc-t-1];	// Frequency 
		SID.v1.ctrl  = 0x11;	// Control voice 1
		for (i = 0 ; i < 100; i++) {}
		SID.v1.ctrl  = 0x10;
		for (i = 0 ; i < 100 ; i++) {}
	}		

}

void createGamePlayground(void) {

	uint8_t a,b,c,d,done;
	uint16_t i,j,g,z;

	g=((plgroffset-1)+plgry+1)*40;
	//generate outter wall
	for(a=(plgroffset-1); a<=(plgroffset-1)+(plgrx+1); ++a) {
		POKE(screen_loc+((plgroffset-1)*40)+a,owchar);
		POKE(screen_loc+g+a,owchar);

		POKE(color_loc+((plgroffset-1)*40)+a,owcolor);
		POKE(color_loc+g+a,owcolor);
		
	}

	for(a=(plgroffset-1); a<(plgroffset-1)+(plgry+1); ++a) {
		
		POKE(screen_loc+(a*40)+(plgroffset-1),owchar);
		POKE(screen_loc+(a*40)+(plgroffset-1)+(plgrx+1),owchar);

		POKE(color_loc+(a*40)+(plgroffset-1),owcolor);
		POKE(color_loc+(a*40)+(plgroffset-1)+(plgrx+1),owcolor);
		
	}

	//playbgound bg color walls
	
	for(a=0; a<plgry; ++a) {
		for(b=0; b<plgrx; ++b) {
			g = (plgroffset*40) + plgroffset + (a*40) + b;
			POKE(screen_loc+g,plbgchar);
			POKE(color_loc+g, plbgcolor);
		}
	}

	//generate walls
	for(a=0; a<plgry; ++a) {
		for(b=0; b<(plgrx/8); ++b) {
			for(c=0; c<8; c++) {
			
			d = 1 << (7-c);
			
			g = (plgroffset*40) + plgroffset + (a*40) + (b*8) + c;
				
			if((playground[a][b] & d) == d) {
				POKE(screen_loc+g,wchar);
				POKE(color_loc+g, wcolor);
			}
			//++g;
			
			}
		}
	}

	_randomize();
	gotoxy(0,1);
	//generate targets/items
	for(i=0; i<tnumber; ++i) {
		done=0;
		while(done==0) { 
			c = plgroffset + (map(rand(), plgry));
			d = plgroffset + (map(rand(), plgrx));
			j = (c*40)+d;
			g = map(rand(), 5);
			if(PEEK(screen_loc+j) == plbgchar) {
				POKE(screen_loc+j,tchar);
				POKE(color_loc+j, tcolors[g]);
				done=1;
			}
		}
	}

	//randomize();
	
	//generate enemies
	for(i=0; i<zcount; ++i) {
		
		done=0;
		while(done==0) {
			_randomize();		
			zx[i] = plgroffset + (map(rand(), plgrx)); 
			zy[i] = plgroffset + (map(rand(), plgry)); 
			zxold[i] = zx[i];zyold[i] = zy[i];
			zdx[i] = 1; zdy[i] = 1;
			z = (zy[i]*40)+zx[i];zold[i]=z;

			if(PEEK(screen_loc+z) == plbgchar) {
				POKE(screen_loc+z,zchar);
				POKE(color_loc+z, zcolor);
				done=1;	
			}

		}
	}


	_randomize();
	//generate player
	done=0;
	while(done==0) {
		px = plgroffset + map(rand(), plgrx); 
		py = plgroffset + map(rand(), plgry); 
		pxold=px;pyold=py;
		p = (py*40)+px;pold=p;
		if(PEEK(screen_loc+p) == plbgchar) {
			POKE(screen_loc+p,pchar[pcharcnt]);
			POKE(color_loc+p, pcolor);
			done=1;
		}
	}
}


uint8_t readJoystick() {

	uint8_t y,c;
	y=~(PEEK(joystick_loc));
	c=0;
	
	//up
	if(y&1) {
		py=py-1;
		c=1;
	}

	//down
	if(y&2) {
		py=py+1;
		c=1;
	}

	//left
	if(y&4) {
		px=px-1;
		c=1;
	}

	//right
	if(y&8) {
		px=px+1;
		c=1;
	}

	//fire button
	if(y&16) {
		c=2;
	}

	return c;
}


void blinkPlayer() {
	
	uint8_t i;
	POKE(color_loc+p, pcolor);
	for(i=0; i<150; ++i) {  }
	POKE(color_loc+p, 0);
	for(i=0; i<150; ++i) {  }
	POKE(color_loc+p, pcolor);
	
}

void playerDeath() {
	
	POKE(color_loc+p, plbgcolor);
	
}

void movePlayer() {

	uint8_t g,h;

	if(px < plgroffset) { px = plgroffset + plgrx-1; }
	if(py < plgroffset) { py = plgroffset + plgry-1; }

	
	if(px >= (plgroffset+plgrx)) { px = plgroffset; }
	if(py >= (plgroffset+plgry)) { py = plgroffset; }


	
	p=(py*40)+px;
	g=PEEK(screen_loc+p);

	if(g!=plbgchar) { 
		//did we hit the target?	
		if(g==tchar) {
			++tcollected;
			
			pickupSound();
			
			printStatusBar();
			
			if(tcollected >= tnumber) {
				gotoxy(0,1);
				printf("well done!");
			}
			
		} else {
			//we hit something else so return
			px=pxold;py=pyold;
			p=pold; return; 
		}
	}
	
	
	POKE(screen_loc+p,pchar[pcharcnt]);
	POKE(color_loc+p, pcolor);

	POKE(screen_loc+pold,plbgchar);
	POKE(color_loc+pold, plbgcolor);	

	pxold=px;pyold=py;pold=p;
	++pcharcnt;
	if(pcharcnt > 1) { pcharcnt=0; }
}

void recalcEnemyDirection(uint8_t i) {

	if(py==zy[i]) {zdy[i]=0; }
	else if(py > zy[i]) { zdy[i]=1; } 
	else { zdy[i]=-1; }
	
	if(px==zx[i]) { zdx[i]=0; }
	else if(px > zx[i]) { zdx[i]=1; } 
	else { zdx[i]=-1; }
	
}


void moveEnemies() {

	uint8_t g,h,i,zdiff;
	uint16_t z,distance;

	for(i=0; i<zcount; ++i) {
		
		
		zx[i] = zx[i] + zdx[i]; 
		zy[i] = zy[i] + zdy[i];		 

		distance = abs(px-zx[i])+abs(py-zy[i]);

		if(zx[i] > (plgroffset + plgrx)) { zx[i] = plgroffset + plgrx; }
		if(zy[i] > (plgroffset + plgry)) { zy[i] = plgroffset + plgry; }

		if(distance < zdist) {
				recalcEnemyDirection(i);

		} 
		
		z=(zy[i]*40)+zx[i];
		
		g=PEEK(screen_loc+z);

		if(g!=plbgchar && g!=tchar) {		

			if(g==pchar[0] || g==pchar[1]) {
		
				zstall[i] = 0;
				--ppower;
				loseEnergySound();
				printStatusBar();
				blinkPlayer();
				
				if(ppower < 1) {
				
					playerDeath();
					playerDeathSound();
					gotoxy(0,1);printf("game over!");
				}
				
			} else { ++zstall[i]; } 

			if(distance > 4 || zstall[i] > 1) {
				
				
				zdx[i]=map(rand(), 2) - 1;
				zdy[i]=map(rand(), 2) - 1;

				if(zdx[i] == 0 && zdy[i] == 0) {
					
					h=(rand() & 1);
					if(h>0) {
						zdx[i]=(rand() & 2)-1;
					} else {
						zdy[i]=(rand() & 2)-1;
					}
				}
				
				zstall[i]=0;

			}

			zx[i]=zxold[i];
			zy[i]=zyold[i];
				
		} else {

			h=PEEK(color_loc+z);
			
			POKE(screen_loc+z,zchar);
			POKE(color_loc+z, zcolor);
			
			POKE(screen_loc+zold[i],zoldchar[i]);
			POKE(color_loc+zold[i],zoldcolor[i]);
			
			zold[i] = z;zxold[i] = zx[i];zyold[i] = zy[i];
			zoldchar[i] = g;
			zoldcolor[i] = h;
		
		}
				
	}
	
	



}

int main(void) {

	uint16_t c,d;
	
	*T = 20; //set big petscii chars!!!

	clrscr(); //clear main screen
	
	setupChars();
	printStatusBar();
	createGamePlayground();

	playSound();
	
	//if(ppower < 1) {
	while(ppower > 0) {

		if(readJoystick()>0) {
	
			movePlayer();
						
			for(c=0; c<200; ++c) { ++d; }
		}	

		if(zact % 2 == 0) {
			moveEnemies();
			for(c=0; c<10; ++c) { ++d; }
		}
	
		for(c=0; c<150; ++c) { ++d; }
		
		++zact;
	
	} 
	
	gotoxy(10,22);printf("the end!");	
	
	return EXIT_SUCCESS;
}
