#include "list.h"


void _init_list(void **list, u32 n, int tsize, enum LIST_TYPE type){
	struct list_header *h = calloc(1, sizeof(struct list_header) + n*tsize);
	if(h == NULL) return; // TODO error warning??
	*h = (struct list_header){.cap = n, .size = 0, .tsize = tsize, .type = type};
	*list = h+1;
}

void _list_realloc(void **list, u32 n){
	struct list_header *h = list_header(*list);
	if(h == NULL) return; // TODO error warning??
	struct list_header *nh = realloc(h, sizeof(struct list_header) + n*h->tsize);
	if(nh == NULL) return; // TODO error warning??	
	nh->cap = n;
	*list = (void*)nh+sizeof(struct list_header);
}

void _list_adjust(void **list){
	struct list_header *h = list_header(*list);
	if(h == NULL) return; // TODO error warning??
	u32 ncap = 0;
	if(h->type == LIST_DYNAMIC){
		if(h->size == h->cap && h->cap < UINT32_MAX){
			ncap = clp2_32(h->cap+2)-1;
		}else if(h->size < h->cap>>1 && h->cap > LIST_INIT_CAP){
			ncap = flp2_32(h->cap)-1;
		}
	}else if(h->type == LIST_NAIVE_DYNAMIC){
		if(h->size == h->cap && h->cap < UINT32_MAX){
			ncap = h->cap+1;
		}else if(h->size < h->cap && h->cap > 1){
			ncap = h->cap-1;
		}
	}
	if(ncap != 0) _list_realloc(list, ncap);
}

void _list_remove(void **list, u32 i){
	struct list_header *h = list_header(*list);
	if(h == NULL) return; // TODO error warning??
	memmove(*list+i*h->tsize, *list+(i+1)*h->tsize, (h->size-i-1)*h->tsize);
	h->size--;
	memset(*list+h->size*h->tsize, 0, h->tsize);
}

void _list_free(void **list){
	if(*list == NULL) return;
	struct list_header *h = list_header(*list);
	free(h);
	*list = NULL;
}

