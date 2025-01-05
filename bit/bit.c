#include "bit.h"


u64 flp2(u64 x){
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x |= (x >> 32);
	return x - (x >> 1);
}

u32 flp2_32(u32 x){
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x - (x >> 1);
}

u64 clp2(u64 x){
	x -= 1;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x |= (x >> 32);
	return x + 1;
}

u32 clp2_32(u32 x){
	x -= 1;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	return x + 1;
}

void _bitstofile(void const * const ptr, size_t const size, FILE *fp){
	unsigned char *b = (unsigned char*)ptr;
	for(int i = size-1; i >= 0; i--){
		for(int j = 7; j >= 0; j--){
			unsigned char byte = ((b[i] >> j) & 1) ? '1' : '0';
			fputc(byte, fp);
		}
		if(i != 0) fputc(' ', fp);
	}
}

