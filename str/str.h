#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "types/types.h"

#define XSTR(S)	STR(S)
#define STR(S)	#S


typedef struct str {
	u32 cap;
	u32 len;
	char *ptr;
} str;


bool charisalpha(char c);

bool charisnum(char c);

bool charisblank(char c);

bool charislinebreak(char c);

bool charisspace(char c);

char lowerchar(char c);

u32 lowers(char *s);

u32 len(const char *s);

str dstr(char *s);

str dnstr(u32 cap);

#define slen(s) (sizeof(s)-1)

#define sstr(s) ((str){.cap = 0, .len = slen(s), .ptr = s})

#define snstr(s, n) ((str){.cap = 0, .len = n, .ptr = s})

int resize_str(str *s, u32 nsize);

str dup_str(str s);

u32 lowerstr(str s);

str utostr(u64 n, int b);

u64 strtou(str s);

int streq(str s1, str s2);

#define NUMSTRS(...) (sizeof((str[]){{0}, ##__VA_ARGS__})/sizeof(str)-1)

// look into calling vlen_nstrs from len_nstrs
u64 len_nstrs(u64 n, ...);

u64 vlen_nstrs(u64 n, va_list args);

#define len_strs(...) \
	len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

// probably should change to append or something
#define copy_str(dest, src) \
	if(dest.ptr != NULL && src.ptr != NULL){	\
		memcpy((dest).ptr+(dest).len, (src).ptr, (src).len); \
		(dest).len += (src).len;	\
	}

#define move_str(dest, src) \
	if(dest.ptr != NULL && src.ptr != NULL){	\
		memmove((dest).ptr+(dest).len, (src).ptr, (src).len); \
		(dest).len += (src).len;	\
	}

void copy_nstrs(str dst, u64 n, ...);

void vcopy_nstrs(str dst, u64 n, va_list args);

void move_nstrs(str dst, u64 n, ...);

void vmove_nstrs(str dst, u64 n, va_list args);

str dup_nstrs(u64 n, ...);

str vdup_nstrs(u64 n, va_list args);

#define copy_strs(d, ...) \
	copy_nstrs(d, NUMSTRS(__VA_ARGS__), __VA_ARGS__); \
	(d).len += len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

#define move_strs(d, ...) \
	move_nstrs(d, NUMSTRS(__VA_ARGS__), __VA_ARGS__); \
	(d).len += len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

#define dup_strs(...) \
	dup_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__);

str read_delim(char *buf, char d);

str sread_delim(char *buf, char d);

str read_delim_f(char *buf, bool (*func)(char), bool func_cond);

str sread_delim_f(char *buf, bool (*func)(char), bool func_cond);

u32 get_line_len(char *buf);

void fd_to_str(str *s, int fd, u32 len);

void file_to_str(str *s, FILE *fp, u32 len);

void print_str(str s);

void free_str(str *s);

char *charinstr(char c, str s); // move somewhere relevant

#endif
