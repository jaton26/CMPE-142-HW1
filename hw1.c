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
	size_t length;
	size_t linelen;
	size_t linesize = 0;
	char* array[MAX]; //I had troubles using malloc and calloc. 

	//An infinite loop until the user enters "exit". 
	while(1){
		printf("HW1 Shell >> ");
		linelen = getline(&line, &linesize, stdin);
		length = strlen(line);

		//Deleting the '\n'.
		if(line[length - 1] == '\n'){
			line[length - 1] = '\0';
		}

		//This will exit the code if the user types 'exit'.  
		if(strcmp(line, "exit") == 0){
			exit(0);
		}

		//Making everything NULL so the dummy values aren't stored. 
		int i = 0;
		while(array[i] != NULL){
			array[i] = NULL;
			i++;
		}	
		
		//Storing each string into an array. 
		i = 0;
		char* token = NULL;
		while((token = strsep(&line, " ")) != NULL){
			array[i] = token;
			i++;
		}
		
		//Testing to see if string are stored correctly. 
		printf("array[0] = %s, array[1] = %s, arrar[2] = %s, len=%d\n", array[0], array[1], array[2], strlen(array[0]));

		//fork
		int child_pid = fork();
		if(child_pid == -1){ //Fork didn't work. 
			perror("Unable to fork");
		}
		else if(child_pid == 0){ //Fork worked.
			execv(array[0], array);
		}
		else{ //Parent
			int hold = wait(NULL);
			assert(hold >= 0);
		}	
		
		//Making everything NULL again at the end.  
		i = 0;
		while(array[i] != NULL){
			array[i] = NULL;
			i++;
		}	
				
	}
}
