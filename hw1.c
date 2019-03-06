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
	char *line = NULL;
	//char **words = (char **)malloc( sizeof(void *)*MAX/2);
	int i = 0;
	int j = 0;
	size_t linesize = 0;
	ssize_t linelen;
	
	
	while ((linelen = getline(&line, &linesize, stdin)) != -1){
		if (strncmp("exit", line, 4) == 0) {
			//user wants to exit
			exit(0);
		}

		//fwrite (line, linelen, 1, stdout); //This repeats what the 								user inputed. 
		
		//Parsing the line
		char **words = (char **)malloc( sizeof(void *)*MAX/2);
		i = 0;
		while((*(words + i) = strsep(&line, " ")) != NULL){
			i++;
		}
		j = 0;

		//Testing to see whether the parsing worked. 
		while(words[j] != NULL){
			printf("%s ", *(words+j) );
			putchar('\n');
			j++;
		}

		
		//fork
		int child_pid = fork();
		if(child_pid == -1){ //Fork didn't work. 
			perror("Unable to fork");
		}
		else if(child_pid == 0){ //Fork worked.
			execv("/bin/ls", words);
			//execvp (words[0], words);
		}
		else{ //Parent
			int hold = wait(NULL);
			assert(hold >= 0);
		}
		//if child, exec
	}
	
	free(line);
	if (ferror(stdin))
		err(1, "getline");
}
