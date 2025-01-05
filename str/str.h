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


struct str {
	u32 cap;
	u32 len;
	char *ptr;
};


bool charisalpha(char c);

bool charisnum(char c);

bool charisblank(char c);

bool charislinebreak(char c);

bool charisspace(char c);

char lowerchar(char c);

u32 len(const char *s);

u32 lowers(char *s);

struct str str(char *s);

struct str nstr(u32 cap);

#define slen(s) (sizeof(s)-1)

#define sstr(s) ((struct str){.cap = 0, .len = slen(s), .ptr = s})

#define snstr(s, n) ((struct str){.cap = 0, .len = n, .ptr = s})

int resize_str(struct str *s, u32 nsize);

struct str dup_str(struct str s);

u32 lowerstr(struct str s);

struct str utostr(u64 n, int b);

u64 strtou(struct str s);

#define NUMSTRS(...) (sizeof((struct str[]){{0}, ##__VA_ARGS__})/sizeof(struct str)-1)

u64 len_nstrs(u64 n, ...);

#define len_strs(...) \
	len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

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

void copy_nstrs(struct str dst, u64 n, ...);

void move_nstrs(struct str dst, u64 n, ...);

#define copy_strs(d, ...) \
	copy_nstrs(d, NUMSTRS(__VA_ARGS__), __VA_ARGS__); \
	(d).len += len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

#define move_strs(d, ...) \
	move_nstrs(d, NUMSTRS(__VA_ARGS__), __VA_ARGS__); \
	(d).len += len_nstrs(NUMSTRS(__VA_ARGS__), __VA_ARGS__)

struct str read_delim(char *buf, char d);

struct str sread_delim(char *buf, char d);

struct str read_delim_f(char *buf, bool (*func)(char), bool func_cond);

struct str sread_delim_f(char *buf, bool (*func)(char), bool func_cond);

u32 get_line_len(char *buf);

void fd_to_str(struct str *s, int fd, u32 len);

void file_to_str(struct str *s, FILE *fp, u32 len);

void print_str(struct str s);

void free_str(struct str *s);

char *charinstr(char c, struct str s); // move somewhere relevant

#endif
