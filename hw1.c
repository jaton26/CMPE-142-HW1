#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
		fwrite (line, linelen, 1, stdout);
		
		//Parsing the line
		char **words = (char **)malloc( sizeof(void *)*MAX/2);
		i = 0;
		while((*(words + i) = strsep(&line, " ")) != NULL){
			i++;
		}
		j = 0;
		while(words[j] != NULL){
			printf("%s ", *(words+j) );
			putchar('\n');
			j++;
		}

		
		//fork
		//if child, exec
	}
	
	free(line);
	if (ferror(stdin))
		err(1, "getline");
}
