#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Usage: tme [program]\n");
		return 1;
	}

	struct timespec t_start, t_end;
	pid_t cpid = fork();
	clock_gettime(CLOCK_MONOTONIC, &t_start);
	if(cpid == 0){
		int r = execvp(argv[1], argv+1);
		//r = execv(argv[1], argv+1);
		if(r == -1){
			perror("tme");
		}
		return 2;
	}

	int wstatus;
	waitpid(cpid, &wstatus, 2); // use 2 instead of 1 because WNOHANG is 1
	clock_gettime(CLOCK_MONOTONIC, &t_end);
	uint64_t diff = (t_end.tv_sec*1000000000 + t_end.tv_nsec) - (t_start.tv_sec*1000000000 + t_start.tv_nsec);
	double timing = diff/1000000000.0;
	
	printf("time: %lfs\n", timing);
	if(WIFEXITED(wstatus)){
		printf("'%s' exited with status %d\n", argv[1], WEXITSTATUS(wstatus));
	}

	return 0;
}
