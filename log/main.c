#define COLOR
#include "log.h"


int main(void){

	int r, g, b;
	while(1){
		printf("select RBG trio: ");
		scanf("%d %d %d", &r, &g, &b);
		if(r > 255) r = 255;
		if(g > 255) g = 255;
		if(b > 255) b = 255;
		printf("%d %d %d\n", r, g, b);
		printf("\t\e[38;2;%d;%d;%dmDEBUG%s\n", r, g, b, CRESET);
		printf("\t\e[38;2;%d;%d;%dmINFO%s\n", r, g, b, CRESET);
		printf("\t\e[38;2;%d;%d;%dmWARN%s\n", r, g, b, CRESET);
		printf("\t\e[38;2;%d;%d;%dmERROR%s\n", r, g, b, CRESET);
	}

	return 0;
}
