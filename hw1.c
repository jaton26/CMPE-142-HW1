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
		//char **words = (char **)calloc(1, sizeof(void *)*MAX/2);
		char **words = (char **)malloc(sizeof(void *)*MAX);
		i = 0;
		size_t length = strlen(line);
		if(line[length - 1] == '\n'){
			line[length - 1] = '\0';
		}
		//New code
		//char *aPtr;
		//int count = 0;
		//do {
		//	aPtr = strsep(&line, " ");
		//	if(aPtr && count < (MAX/2)){
		//		words[count++] = aPtr;
		//	}
		//} while(aPtr != NULL);
		//for(int z = 0; z < count; z++){
		//	printf("%s\n", words[z]);
		//}
		
		//New new code
		char *token = NULL;
		while((token = strsep(&line, " ")) != NULL){
			
			words[i] = token;
			i++;
		}
		i = 0;
		//size_t length = strlen(words);
		//if(words[length] == '\n'){
		//	words[length] = '\0';
		//}
		
		//New code

		//while((*(words + i) = strsep(&line, " ")) != NULL){
		//	i++;

		//}
		//j = 0;

		//Testing to see whether the parsing worked. 
		while(words[j] != NULL){
			//printf("words0 = %s, words1 = %s, words2 = %s, len=%d\n", words[0], words[1], words[2], strlen(words[1]));
			//printf("%s ", *(words+j) );
			//putchar('\n');
			j++;
		}
		//fork
		int child_pid = fork();
		//char *argv[] = {words, NULL};
		if(child_pid == -1){ //Fork didn't work. 
			perror("Unable to fork");
		}
		else if(child_pid == 0){ //Fork worked.
			//execv(ls_args[0], ls_args);
			printf("words0 = %s, words1 = %s, words2 = %s, len=%d\n", words[0], words[1], words[2], strlen(words[1]));
			//printf("words2 = %s\n", words[2]);
			
			execv(words[0], words);
			//execvp (*words, words);
		}
		else{ //Parent
			int hold = wait(NULL);
			assert(hold >= 0);
		}
		//if child, exec
		//Make everything null again. 
		i = 0;
		while(words[i] != NULL){
			words[i] = NULL;
			i++;
		}
		free(words);
	}
	
	free(line);
	if (ferror(stdin))
		err(1, "getline");
}
