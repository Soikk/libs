#include "files.h"


int dir_exists(char *dirpath){
	struct stat st;
	if(stat(dirpath, &st) == 0){
		return S_ISDIR(st.st_mode);
	}
	return 0;
}

int file_exists(char *filepath){
	struct stat st;
	if(stat(filepath, &st) == 0){
		return
			S_ISREG(st.st_mode) ||
			S_ISSOCK(st.st_mode) ||
			S_ISFIFO(st.st_mode) ||
			S_ISCHR(st.st_mode) ||
			S_ISBLK(st.st_mode) ||
			S_TYPEISSHM(&st) ||
			S_TYPEISMQ(&st) ||
			S_TYPEISSEM(&st)
		;
	}
	return 0;
}

int path_exists(char *path){
	return dir_exists(path) || file_exists(path);
}

u64 get_fd_size(int fd){
	struct stat st;
	if(fstat(fd, &st) == 0){
		return st.st_size;
	}
	return 0;
}

u64 get_fp_size(FILE *fp){
	if(fp != NULL){
		return get_fd_size(fileno(fp));
	}
	return 0;
}

u64 get_file_size(char *filename){
	struct stat st;
	if(stat(filename, &st) == 0){
		return st.st_size;
	}
	return 0;
}

char *get_extension(char *filename){
	int len = 0, i = 0;
	while(filename[len] != '\0') len++;
	while(len-i > 0){
		if(filename[len-i-1] == '.') break;
		i++;
	}
	if(i == 0 || i == len){
		return NULL;
	}
	return filename + len - i;
}

