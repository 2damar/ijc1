#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdlib.h>
#include <limits.h>
#include "error.h"

#define UL_BIT_SIZE (CHAR_BIT * sizeof(unsigned long))

typedef unsigned long* bit_array_t;

#define BA_GET_BIT(ba, index) \
   ((ba[(index) / (CHAR_BIT * sizeof ba[0]) + 1]) & \
      (1UL << ((index) % (CHAR_BIT * sizeof ba[0]))))

#define BA_SET_BIT(ba, index, ex) \
   ((ex != 0) ? \
      (ba[(index) / (CHAR_BIT * sizeof ba[0]) + 1] |= \
	 		(1UL << ((index) % (CHAR_BIT * sizeof ba[0])))) \
   	: \
      (ba[(index) / (CHAR_BIT * sizeof ba[0]) + 1] &= \
      ~(1UL << ((index) % (CHAR_BIT * sizeof ba[0]))))) 


#define ba_create(ba, size) \
   unsigned long ba[(size/UL_BIT_SIZE + 2)] = {size} 

#define ba_size(ba) ba[0] 

#ifndef USE_INLINE

#define ba_set_bit(ba, i, expr) \
   (((i) >= ba_size(ba)) ? \
      (error_msg("Index %lu out of range 0..%lu", i, ba_size(ba)), 0) \
   	: \
      BA_SET_BIT(ba, (i), (expr))) 

#define ba_get_bit(ba, i) \
   (((i) >= ba_size(ba)) ? \
      (error_msg("Index %lu out of range 0..%lu", i, ba_size(ba)), 0) \
      : \
      BA_GET_BIT(ba, (i)))

#else // USE_INLINE
static inline void ba_set_bit(bit_array_t ba, unsigned long i, int expr) {
   if((i) >= ba_size(ba)) 
      error_msg("Index %lu out of range 0..%lu", i, ba_size(ba));
	else
		BA_SET_BIT(ba, i, expr);
}

static inline unsigned long ba_get_bit(bit_array_t ba, unsigned long i) {
   if((i) >= ba_size(ba)) 
      error_msg("Index %lu out of range 0..%lu", i, ba_size(ba));

   return  BA_GET_BIT(ba, i);
}
#endif // ~USE_INLINE

#endif // ~BIT_ARRAY_H

