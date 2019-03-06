// homework 1
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv [])
{
	char *line = NULL;
	int i = 0;
	int j = 0;
	size_t linesize = 0;
	ssize_t linelen;
	int rc = fork();
	if (rc < 0) {
		// fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
	} else if (rc == 0) {
		while((linelen = getline(&line, &linesize, stdin)) != -1) {
			if (strncmp ("exit", line, 4) == 0){
				exit(0);
			}
			if (strncmp ("poop", line, 4) == 0){
				fprintf(stderr, "poopy\n");
				exit(0);
			}
			if (strncmp ("ls", line, 4) == 0){
				execv( args[0], args);
			}
			
			fwrite(line, linelen, 1, stdout);
		}
	} else {
		// parent goes down this path (original process)
		int wc = wait(NULL);
		assert(wc >= 0);
	}
	
	free(line);
	if(ferror(stdin)) {
		err(1, "getline");
	}
}
