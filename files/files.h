#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <sys/stat.h>
#include "types/types.h"


int dir_exists(char *dirpath);
int file_exists(char *filepath);
int path_exists(char *path);

u64 get_fd_size(int fd);
u64 get_fp_size(FILE *fp);
u64 get_file_size(char *filename);

char *get_extension(char *filename);

#endif
