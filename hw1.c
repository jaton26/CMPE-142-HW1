#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 128


int
main(int argc, char **argv)
{
	char* line = NULL;
	size_t linelen;
	size_t linesize = 0;
	while(1){
		linelen = getline(&line, &linesize, stdin);
		size_t length = strlen(line);
		if(line[length - 1] == '\n'){
			line[length - 1] = '\0';
		}
		if(strcmp(line, "exit") == 0){
			exit(0);
		}
	}
}
