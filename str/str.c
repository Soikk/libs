#include "str.h"


__attribute__ ((optimize(3))) bool charisalpha(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

__attribute__ ((optimize(3))) bool charisnum(char c){
	return c >= '0' && c <= '9';
}

__attribute__ ((optimize(3))) bool charisblank(char c){
	return c == ' ' || c == '\t';
}

__attribute__ ((optimize(3))) bool charislinebreak(char c){
	return c == '\n' || c == '\f' || c == '\v';
}

__attribute__ ((optimize(3))) bool charisspace(char c){
	switch(c){
		case ' ': case '\t': case '\n': case '\r': case '\f': case '\v':
			return true;
		default:
			return false;
	}
}

char lowerchar(char c){
	if(c >= 'A' && c <= 'Z') c += 32;
	return c;
}

u32 lowers(char *s){
	u32 l = -1;
	while(s[++l]) s[l] = lowerchar(s[l]);
	return l;
}

__attribute__ ((optimize(1))) u32 len(const char *s){
	if(s == NULL) return 0;
	u32 l = -1;
	while(s[++l]);
	return l;
}

str dstr(char *s){
	str r = {
		.cap = len(s),
		.len = r.cap,
		.ptr = calloc(r.len+1, sizeof(char))
	};
	if(r.ptr == NULL) r = (str){0};
	else memcpy(r.ptr, s, r.len);
	return r;
}

str dnstr(u32 cap){
	str s = {
		.cap = cap,
		.len = 0,
		.ptr = calloc(cap+1, sizeof(char))
	};
	return s;
}

int resize_str(str *s, u32 nsize){
	if(nsize == 0) return 1;
	char *nptr = realloc(s->ptr, nsize);
	if(nptr == NULL) return 1;
	s->ptr = nptr;
	s->cap = nsize;
	return 0;
}

str dup_str(str s){
	// we use len here to account for static strings that have no cap
	str r = {.cap = s.len, .len = s.len, .ptr = calloc(s.len+1, sizeof(char))};
	if(r.ptr == NULL) return (str){0};
	memcpy(r.ptr, s.ptr, s.len);
	return r;
}

u32 lowerstr(str s){
	return lowers(s.ptr);
}

str utostr(u64 n, int b){
	str s = {
		.ptr = calloc(sizeof(n)*8 + 2, sizeof(char))
	};
	if(s.ptr == NULL) return (str){0};
	u64 dn = n, p = 1;
	while(dn /= b) p *= b;
	while(p){
		dn = n/p;
		s.ptr[s.len++] = dn > 9 ? 'A'-10+dn : '0'+dn;
		n %= p, p /= b;
	}
	char *nptr = realloc(s.ptr, s.len+1);
	if(nptr == NULL){
		free(s.ptr);
		return (str){0};
	}
	s.ptr = nptr;
	s.cap = s.len;
	return s;
}

// TODO add support for different bases
u64 strtou(str s){
	u64 i = 0, r = 0;
	while(charisnum(s.ptr[i])){
		r *= 10;
		r += s.ptr[i++] - '0';
	}
	return r;
}

int streq(str s1, str s2){
	if(s1.len != s2.len){
		return 0;
	}
	int i = 0;
	while(i < s1.len){
		if(s1.ptr[i] != s2.ptr[i]){
			return 0;
		}
		i++;
	}
	return 1;
}

u64 len_nstrs(u64 n, ...){
	u64 s = 0;
	va_list vl;
	va_start(vl, n);
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(vl, str);
		s += t.len;
	}
	va_end(vl);
	return s;
}

u64 vlen_nstrs(u64 n, va_list args){
	u64 s = 0;
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(args, str);
		s += t.len;
	}
	return s;
}

void copy_nstrs(str dst, u64 n, ...){
	va_list vl;
	va_start(vl, n);
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(vl, str);
		copy_str(dst, t);
	}
	va_end(vl);
}

void vcopy_nstrs(str dst, u64 n, va_list args){
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(args, str);
		copy_str(dst, t);
	}
}

void move_nstrs(str dst, u64 n, ...){
	va_list vl;
	va_start(vl, n);
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(vl, str);
		move_str(dst, t);
	}
	va_end(vl);
}

void vmove_nstrs(str dst, u64 n, va_list args){
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(args, str);
		move_str(dst, t);
	}
}

str dup_nstrs(u64 n, ...){
	va_list vl, vlc;
	va_start(vl, n);
	va_copy(vlc, vl);
	str r = dnstr(vlen_nstrs(n, vlc));
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(vl, str);
		copy_str(r, t);
	}
	va_end(vlc);
	va_end(vl);
	return r;
}

str vdup_nstrs(u64 n, va_list args){
	va_list vlc;
	va_copy(vlc, args);
	str r = dnstr(vlen_nstrs(n, vlc));
	for(u64 i = 0; i < n; i++) {
		str t = va_arg(args, str);
		copy_str(r, t);
	}
	va_end(vlc);
	return r;
}

str read_delim(char *buf, char d){
	u32 i = 0;
	while(buf[i] && buf[i] != d) i++;
	str s = {.cap = i, .len = i, .ptr = calloc(s.cap+1, sizeof(char))};
	if(s.ptr == NULL) return (str){0};
	memcpy(s.ptr, buf, i);
	return s;
}

str sread_delim(char *buf, char d){
	u32 i = 0;
	while(buf[i] && buf[i] != d) i++;
	str s = {.cap = 0, .len = i, .ptr = buf};
	return s;
}

str read_delim_f(char *buf, bool (*func)(char), bool func_cond){
	u32 i = 0;
	while(buf[i] && (func(buf[i]) != func_cond)) i++;
	str s = {.cap = i, .len = i, .ptr = calloc(s.cap+1, sizeof(char))};
	if(s.ptr == NULL) return (str){0};
	memcpy(s.ptr, buf, i);
	return s;
}

str sread_delim_f(char *buf, bool (*func)(char), bool func_cond){
	u32 i = 0;
	while(buf[i] && (func(buf[i]) != func_cond)) i++;
	str s = {.cap = 0, .len = i, .ptr = buf};
	return s;
}

u32 get_line_len(char *buf){
	u32 l = 0;
	while(buf[l] != '\0' && buf[l] != '\n') l++;
	return l;
}

void fd_to_str(str *s, int fd){
	// should probably check this isnt bigger than u32 max
	off_t len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	s->ptr = calloc(len+1, sizeof(char));
	if(s->ptr == NULL) return;
	for(u32 l = len; l != 0; l -= read(fd, s->ptr+(len-l), l));
	s->cap = len;
	s->len = len;
}

void fd_to_nstr(str *s, int fd, u32 len){
	s->ptr = calloc(len+1, sizeof(char));
	if(s->ptr == NULL) return;
	for(u32 l = len; l != 0; l -= read(fd, s->ptr+(len-l), l));
	s->cap = len;
	s->len = len;
}

void file_to_str(str *s, FILE *fp){
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	s->ptr = calloc(len+1, sizeof(char));
	if(s->ptr == NULL) return;
	for(u32 l = len; l != 0; l -= fread(s->ptr, sizeof(char), len, fp));
	s->cap = len;
	s->len = len;
}

void file_to_nstr(str *s, FILE *fp, u32 len){
	s->ptr = calloc(len+1, sizeof(char));
	if(s->ptr == NULL) return;
	for(u32 l = len; l != 0; l -= fread(s->ptr, sizeof(char), len, fp));
	s->cap = len;
	s->len = len;
}

void print_str(str s){
	for(u32 i = 0; i < s.len; i++){
		putchar(s.ptr[i]);
	}
}

void free_str(str *s){
	if(s->ptr != NULL && s->cap > 0) free(s->ptr);
	s->ptr = NULL;
	s->cap = 0;
	s->len = 0;
}

char *charinstr(char c, str s){
	for(u32 i = 0; i < s.len; i++){
		if(s.ptr[i] == c){
			return s.ptr + i;
		}
	}
	return NULL;
}

