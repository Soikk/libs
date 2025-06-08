#include "log.h"


static struct {
	char *name;
	int set;
	FILE *fps[MAX_LOGFILES];
	int nfps;
	int stder;
#ifdef COLOR
	char *color;
#endif
} log_levels[LOG_LEVEL_COUNT] = {
	[LOG_DEBUG] = { 
		.name = "DEBUG", .set = 1, .fps = {0}, .nfps = 0, .stder = 1,
#ifdef COLOR
		.color = "\e[38;2;255;255;0m"
#endif
	},
	[LOG_INFO] = {
		.name = "INFO", .set = 1, .fps = {0}, .nfps = 0, .stder = 1,
#ifdef COLOR
		.color = "\e[38;2;0;224;255m"
#endif	
	},
	[LOG_WARN] = {
		.name = "WARN", .set = 1, .fps = {0}, .nfps = 0, .stder = 1,
#ifdef COLOR
		.color = "\e[38;2;255;165;0m"
#endif
	},
	[LOG_ERROR] = {
		.name = "ERROR", .set = 1, .fps = {0}, .nfps = 0, .stder = 1,
#ifdef COLOR
		.color = "\e[38;2;255;0;0m"
#endif
	}
};

static char time_format[16] = "%T";
static int nanosecond_precision = 0;


int log_set_stderr(int level, int of){
	if(level >= 0 && level < LOG_LEVEL_COUNT){
		return log_levels[level].stder = of;
	}
	return 0;
}

void log_set_level(int level, int of){
	if(level >= 0 && level < LOG_LEVEL_COUNT){
		log_levels[level].set = of;
	}
}

int log_add_fp(int level, FILE *fp){
	if(level >= 0 && level < LOG_LEVEL_COUNT && log_levels[level].nfps < MAX_LOGFILES){
		log_levels[level].fps[log_levels[level].nfps++] = fp;
		return 0;
	}
	return 1;
}

FILE *log_get_fp(int level, int i){
	if(level >= 0 && level < LOG_LEVEL_COUNT && i >= 0 && i < log_levels[level].nfps){
		return log_levels[level].fps[i];
	}
	return NULL;
}

int log_remove_fp(int level, FILE *fp){
	if(level < 0 || level >= LOG_LEVEL_COUNT){
		return 1;
	}
	for(int i = 0; i < log_levels[level].nfps; i++){
		if(log_levels[level].fps[i] == fp){
			for(int j = i; j < MAX_LOGFILES-1; j++){
				log_levels[level].fps[j] = log_levels[level].fps[j+1];
			}
			log_levels[level].fps[log_levels[level].nfps--] = NULL;
			return 0;
		}
	}
	return 1;
}

int log_get_files(int level){
	if(level >= 0 && level < LOG_LEVEL_COUNT){
		return log_levels[level].nfps;
	}
	return 0;
}

void log_time_format(char *tf){
	strncpy(time_format, tf, sizeof(time_format)/sizeof(time_format[0]));
}

int log_nanoseconds(int n){
	return nanosecond_precision = n%10;
}

void log_message(int level, char *file, int line, char *fmt, ...){
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	if(level >= 0 && level < LOG_LEVEL_COUNT && log_levels[level].set){
		struct tm *lt = localtime(&ts.tv_sec);
		char t[32] = {0};
		strftime(t, 31, time_format, lt);
		char ns[9] = {0};
		snprintf(ns, nanosecond_precision+1, "%ld", ts.tv_nsec);
		char msg[MSG_LIMIT] = {0};
		int written = snprintf(msg, MSG_LIMIT-2,
#ifdef PID
			"[%d] "
#endif
			"%s%s%s%s%s%s%s\t",
#ifdef PID
			getpid(),
#endif
			t, nanosecond_precision ? "." : "", ns,
			t[0] != '\0' ? " " : "",
#ifdef COLOR
			log_levels[level].color,
#else
			"",
#endif
			log_levels[level].name, "\e[0m"
		);
		if(level == LOG_DEBUG){
			written += snprintf(msg+written, MSG_LIMIT-2-written, "%s:%d: ",file, line);
		}
		va_list args;
		va_start(args, fmt);
		written += vsnprintf(msg+written, MSG_LIMIT-2-written, fmt, args);
		msg[written] = '\n';
		if(log_levels[level].stder) fputs(msg, stderr);
		for(int i = 0; i < log_levels[level].nfps; i++){
			if(log_levels[level].fps[i] != NULL)
				fputs(msg, log_levels[level].fps[i++]);
		}
	}
}

