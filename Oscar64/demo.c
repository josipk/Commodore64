#include <stdio.h>
#include <string.h>
#include <c64/vic.h>

#define Screen ((char *) 0x0400)
#define ScreenColor ((char *) 0xd021)
#define BorderColor ((char *) 0xd020)

int main(void) {

	memset(Screen, 32, 1000);
	
	//*BorderColor = 1;
	//*ScreenColor = 3;
	vic.color_back = 0x03;
	vic.color_border = 0x01;
	
	
	
	Screen[0] = 42;
	Screen[1] = 43;
	Screen[2] = 44;

	char c = Screen[1];
	
	printf("\n\n%c %d", c, c);
	
	return 0;
}
