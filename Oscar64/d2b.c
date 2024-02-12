#include <stdio.h>

void d2b(int n) {

	int a;
	
	if(n) {

		if(n & 1) {
			a = 1;		
		} else {
			a = 0;	
		}		
		
		d2b(n >> 1);
		
		printf("%d", a);
	}	

}




int main(void)  {
	
	d2b(25);
	return 0;
}
