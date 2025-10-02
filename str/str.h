#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "types/types.h"
#include "files/files.h"

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

// reorder?
str dstr(char *s);
str dnstr(u32 cap);
str dsstr(char *s);
str dsnstr(char *s, u32 len);

#define slen(s) (sizeof(s)-1)

#define sstr(s) ((str){.cap = 0, .len = slen(s), .ptr = s})

#define snstr(s, n) ((str){.cap = 0, .len = n, .ptr = s})

int resize_str(str *s, u32 nsize);

str dup_str(str s);

u32 lowerstr(str s);

str utostr(u64 n, int b);

u64 strtou(str s);

int streq(str s1, str s2);
int streqn(str s1, str s2, u32 n);

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

// probably do away with this
u32 get_line_len(char *buf);

str fd_to_str(int fd);
str fd_to_nstr(int fd, u32 len);
str fp_to_str(FILE *fp);
str fp_to_nstr(FILE *fp, u32 len);
str file_to_str(char *filename);
str file_to_nstr(char *filename, u32 len);
str map_file(char *filename);
// consider adding 'at' to other file-to-str functions
str map_file_at(char *filename, int len, int at);
void unmap_file(str *s);

#define read_str(max) fread_str(STDIN_FILENO, max)
str fread_str(int fd, int max);
void print_str(str s);

void free_str(str *s);

char *charinstr(char c, str s); // move somewhere relevant

#endif
