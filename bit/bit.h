#ifndef BIT_H
#define BIT_H

/*
	Most of these functions are courtesy of
	Hacker's Delight, 2nd edition (Henry S. Warren, Jr.)
*/

#include <stdio.h>
#include "types/types.h"


// rounds down (floors) to the nearest power of 2
u64 flp2(u64 x);

// rounds down (floors) to the nearest power of 2 in 32 bits
u32 flp2_32(u32 x);

// rounds up (ceils) to the nearest power of 2
u64 clp2(u64 x);

// rounds up (ceils) to the nearest power of 2 in 32 bits
u32 clp2_32(u32 x);

// prints the bits of the data pointed to by ptr of size size to fp
void _bitstofile(void const * const ptr, size_t const size, FILE *fp);

#define fprintb(n, f) ({	\
		typeof(n) _n = (n);	\
		_bitstofile(&(_n), sizeof(_n), f);	\
	})

#define printb(n) fprintb(n, stdout)

#define fputb(n, f) ({	\
		fprintb(n, f);	\
		fputc('\n', f);	\
	})

#define putb(n) fputb(n, stdout)

#endif
