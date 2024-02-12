#include <math.h>
#include <stdio.h>

int main() {
	
	int x,y,d;
	float t;

	for(y=-9; y<=9; y++) {
	
		for(x=0; x<=18; x++) {

			t = (float) (x*x-y*y)/6;
			
			d = 42 - 10*(t > (int) floor(t));
			
			printf("%c", d);
			
		}	

		printf("\n");

	}

	
	return 0;
}
