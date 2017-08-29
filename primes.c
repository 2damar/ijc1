#include <stdio.h>
#include "bit_array.h"
#include "eratosthenes.h"


int main(void){
   ba_create(ba, 303000000UL);
   unsigned long ba_sz = ba_size(ba);
   eratosthenes(ba);

   unsigned long primes[10];
   int pidx = 9;

   unsigned long top = ba_sz - 1;
   for(int i = pidx; i >= 0; i--) {
      
      while((ba_get_bit(ba, top)) != 0) {
	 		top--;
      }
      primes[i] = top;
      top--;
   }

   for(int i = 0; i < 10; i++) {
      printf("%lu\n", primes[i]);
   }   
   
   return 0;
}
	 


   
