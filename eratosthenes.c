#include "eratosthenes.h"
#include <stdio.h>

void eratosthenes(bit_array_t ba) {

	unsigned long sz = ba_size(ba);
   // initialize eratosthenes field
   ba_set_bit(ba, 0UL, 1);
   ba_set_bit(ba, 1UL, 1);
   unsigned long sqrt_sz = sqrt(sz) + 1;
   // unset the rest of the field
   for(unsigned long i = 2; i < sqrt_sz; i++) {
      unsigned long bset = ba_get_bit(ba, i);
      if(bset == 0) {
	 		for(unsigned long j = 2*i; j < sz; j += i) {
	    	ba_set_bit(ba, j, 1);
	 }
      }
   } 
}


