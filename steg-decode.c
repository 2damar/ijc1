#include <stdio.h>
#include "ppm.h"
#include "bit_array.h"
#include "eratosthenes.h"

#define PFSIZE 300000

int main(void) {
	struct ppm* pic = ppm_read("du1-obrazek.ppm");
	if(pic == NULL) 
		return -1;

	unsigned long size = 3UL * pic->xsize * pic->ysize;
	ba_create(pf, PFSIZE);
	eratosthenes(pf);

	int c = 0;
	unsigned bit_i = 0;
	for(unsigned long i = 0; i < size; i++) {
		if(ba_get_bit(pf, i) == 0) {
			c |= (pic->data[i] & 1U) << bit_i;
			bit_i++;
			if(bit_i == 8) {
				if(c == '\0')
					break;
				putchar(c);
				c = 0;
				bit_i = 0;
			}
		}		
	}
	
	return 0;
}
	
			
			
			



