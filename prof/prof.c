#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <intrin.h>


struct timespec t_start, t_end;

#define start_timing() clock_gettime(CLOCK_MONOTONIC, &t_start)
#define end_timing() clock_gettime(CLOCK_MONOTONIC, &t_end)

double get_timing(void){
	uint64_t diff = (t_end.tv_sec*1000000000 + t_end.tv_nsec) - (t_start.tv_sec*1000000000 + t_start.tv_nsec);
	return diff/1000000000.0;
}

uint64_t c_start, c_end;

#define start_clock() c_start = __rdtsc()
#define end_clock() c_end = __rdtsc()
#define clock_cycles (c_end-c_start)


int main(){


	start_timing();
	end_timing();

	struct timespec res;
	clock_getres(CLOCK_MONOTONIC, &res);
	printf("%d.%08ld\n", res.tv_sec, res.tv_nsec);

	return 0;
}
