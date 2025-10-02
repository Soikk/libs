#ifndef LIST_H
#define LIST_H
// possible todo: overload macros to be able to pass them the header too

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types/types.h"
#include "bit/bit.h"


struct list_header {
	u32 cap;
	u32 size;
	int tsize;
	int type;
};

enum LIST_TYPE {
	LIST_STATIC,
	LIST_DYNAMIC,
	LIST_NAIVE_DYNAMIC,
};


#define LIST(T) typeof(T) *
#define LIST_INIT_CAP 31

#define list_header(l) ({	\
	(l) ? (struct list_header *)(((void*)l) - sizeof(struct list_header)) : NULL;	\
})

#define list_cap(l) ({	\
	struct list_header *h = list_header(l);	\
	h != NULL ? h->cap : 0;	\
})

#define list_size(l) ({	\
	struct list_header *h = list_header(l);	\
	h != NULL ? h->size : 0;	\
})

#define list_tsize(l) ({	\
	struct list_header *h = list_header(l);	\
	h != NULL ? h->tsize : 0;	\
})

#define list_type(l) ({	\
	struct list_header *h = list_header(l);	\
	h != NULL ? h->type : 0;	\
})

#define list_full(l) ({	\
	struct list_header *h = list_header(l);	\
	h->size < h->cap ? false : true;	\
})

#define init_slist(l, n) ({	\
	_init_list((void**)&(l), n, sizeof(*(l)), LIST_STATIC);	\
})

#define init_dlist(l) ({	\
	_init_list((void**)&(l), LIST_INIT_CAP, sizeof(*(l)), LIST_DYNAMIC);	\
})

#define init_nlist(l) ({	\
	_init_list((void**)&(l), 1, sizeof(*(l)), LIST_NAIVE_DYNAMIC);	\
})

// if you init with 2 arguments, you init a static list. otherwise,
// a dynamic list. naive list has to be explicitly initialized
#define _choose_init(_1, _2, NAME, ...) NAME
#define init_list(...) _choose_init(__VA_ARGS__, init_slist, init_dlist)(__VA_ARGS__)

#define list_size_increment(l) ({	\
	struct list_header *h = list_header(l);	\
	if(h != NULL) h->size++;	\
})

#define list_peek(l) ({	\
	typeof((l)[0]) d = {0};	\
	struct list_header *h = list_header(l);	\
	if(h != NULL && h->size > 0) d = l[h->size-1];	\
	d;	\
})

#define list_pop(l) ({	\
	struct list_header *h = list_header(l);	\
	typeof((l)[0]) d = {0};	\
	if(h != NULL){	\
		if(h->size > 0){	\
			d = l[h->size-1];	\
			l[h->size-1] = (typeof(d)){0};	\
			h->size--;	\
			_list_adjust((void**)&(l));	\
		}	\
	}	\
	d;	\
})

#define list_remove(l, i) ({	\
	struct list_header *h = list_header(l);	\
	typeof(*(l)) d = {0};	\
	if(h != NULL && i < h->size){	\
		d = l[i];	\
		_list_remove((void**)&(l), i);	\
	}	\
	d;	\
})

#define list_remove_entry(l, d) ({	\
	struct list_header *h = list_header(l);	\
	typeof(d) _d = (d);	\
	if(h != NULL){	\
		for(u32 i = 0; i < h->size; i++){	\
			if(!memcmp(&(l[i]), &(_d), sizeof(_d))){	\
				_list_remove((void**)&(l), i);	\
				_list_adjust((void**)&(l));	\
				break;	\
			}	\
		}	\
	}	\
	d;	\
})

#define list_entry_exists(l, d) ({	\
	struct list_header *h = list_header(l);	\
	bool found = false;	\
	if(h != NULL){	\
		typeof(d) _d = (d);	\
		for(u32 i = 0; i < h->size; i++){	\
			if(!memcmp(&(l[i]), &(_d), sizeof(_d))){	\
				found = true;	\
				break;	\
			}	\
		}	\
	}	\
	found;	\
})

// TODO check for typeof
#define list_push(l, d) ({	\
	_list_adjust((void**)&(l));	\
	struct list_header *h = list_header(l);	\
	if(h != NULL && h->tsize == sizeof(d)){	\
		if(h->size < h->cap){	\
			l[h->size] = d;	\
			h->size++;	\
		}	\
	}	\
})

// TODO check for typeof
// TODO check i > 0
#define list_push_i(l, d, i) ({	\
	_list_adjust((void**)&(l));	\
	struct list_header *h = list_header(l);	\
	if(h != NULL && h->tsize == sizeof(d) && i < h->size){	\
		u32 n = (h->size-i < h->cap-i-1) ? h->size-i : h->cap-i-1;	\
		memmove(((void*)l)+(i+1)*h->tsize, ((void*)l)+i*h->tsize, n*h->tsize);	\
		l[i] = d;	\
		h->size += h->size < h->cap ;	\
	}	\
})

#define list_append(l1, l2) ({	\
	struct list_header *h1 = list_header(l1);	\
	struct list_header *h2 = list_header(l2);	\
	if(h1 != NULL && h2 != NULL && h1->tsize == h2->tsize){	\
		u32 ins = h2->size;	\
		if(h1->size+h2->size > h1->cap){	\
			if(h1->type == LIST_STATIC){	\
				ins = h1->cap-h1->size;	\
			}else if(h1->type == LIST_DYNAMIC){	\
				_list_realloc((void**)&(l1), clp2_32(h1->cap+ins)-1);	\
			}else if(h1->type == LIST_NAIVE_DYNAMIC){	\
				_list_realloc((void**)&(l1), h1->cap+ins);	\
			}	\
		}	\
		h1 = list_header(l1);	\
		memcpy(l1+h1->size, l2, ins);	\
		h1->size += ins;	\
	}	\
})

#define list_append_array(l, a, n) ({	\
	struct list_header *h = list_header(l);	\
	if(h != NULL && h->tsize == sizeof(a[0])){	\
		u32 ins = n;	\
		if(h->size+n > h->cap){	\
			if(h->type == LIST_STATIC){	\
				ins = h->cap-h->size;	\
			}else if(h->type == LIST_DYNAMIC){	\
				_list_realloc((void**)&(l), clp2_32(h->cap+ins)-1);	\
			}else if(h->type == LIST_NAIVE_DYNAMIC){	\
				_list_realloc((void**)&(l), h->cap+ins);	\
			}	\
		}	\
		h = list_header(l);	\
		memcpy(l+h->size, a, ins);	\
		h->size += ins;	\
	}	\
})

// TODO encapsulate all indexes in parentheses in all macros
#define list_swap(l, i, j) ({	\
	struct list_header *h = list_header(l);	\
	if(h != NULL && (i) != (j) && (i) >= 0 && (i) < h->size && (j) >= 0 && (j) < h->size){	\
		typeof((l)[0]) t = (l)[i];	\
		(l)[i] = (l)[j];	\
		(l)[j] = t;	\
	}	\
})

#define list_clamp_n(l, n) ({	\
	struct list_header *h = list_header(l);	\
	if(h != NULL){	\
		u32 _n = h->size > n ? h->size : n;	\
		_list_realloc((void**)&l, _n);	\
	}	\
})

#define list_clamp_s(l) ({	\
	struct list_header *h = list_header(l);	\
	if(h != NULL){	\
		_list_realloc((void**)&l, h->size);	\
	}	\
})

#define _choose_clamp(_1, _2, NAME, ...) NAME
#define list_clamp(...)  _choose_clamp(__VA_ARGS__, list_clamp_n, list_clamp_s)(__VA_ARGS__)

#define list_free(l) _list_free((void**)&(l))


void _init_list(void **list, u32 n, int tsize, enum LIST_TYPE type);

void _list_realloc(void **list, u32 n);

void _list_adjust(void **list);

void _list_remove(void **list, u32 i);

void _list_free(void **list);

#endif
