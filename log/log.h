#ifndef LOG_H
#define LOG_H

#define PID
#define COLOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#ifdef PID
#include <unistd.h>
#endif


enum {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_LEVEL_COUNT
};

#define MAX_LOGFILES (8)
#define MSG_LIMIT (256)


int log_set_stderr(int level, int of);
void log_set_level(int level, int of);
int log_add_fp(int level, FILE *fp);
FILE *log_get_fp(int level, int i);
int log_remove_fp(int level, FILE *fp);
int log_get_files(int level);
void log_time_format(char *tf);
int log_nanoseconds(int n);
void log_message(int level, char *file, int line, char *fmt, ...);

#define log_debug(...) log_message(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_message(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_message(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_message(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif
