#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 128

int programWait = 1;

void redirectIn(char *fileName) {
    int in = open(fileName, O_RDONLY);
    dup2(in, 0);
    close(in);
}

void redirectOut(char *fileName) {
    int out = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

void beginProcess(char *args[]) {
    int child_pid;
        if (strcmp(args[0], "exit") != 0) {
            child_pid = fork();
            if(child_pid == -1) {
                perror("Unable to fork");
            } else if (child_pid == 0) {
                execv(args[0], args);
            } else {
                if (programWait) {
                    waitpid(child_pid, NULL, 0);
                } else {
                    programWait = 0;
                }
            }
	    // Return back to the terminal
	    redirectIn("/dev/tty");
            redirectOut("/dev/tty");
        } else {
	    exit(1);
	}
}

void createPipe(char *args[]) {
    int fd[2];
    pipe(fd);

    dup2(fd[1], 1);
    close(fd[1]);

    printf("args = %s\n", *args);

    beginProcess(args);

    dup2(fd[0], 0);
    close(fd[0]);
}

int main(void) {
    char *args[MAX]; //array
    
    while(1) {
        printf("HW1 Shell >> ");
        fflush(stdout);
        
        char array[MAX]; //args
        fgets(array, MAX, stdin); //array line
        
        int tokenI;
        int tokenJ = 0;
        char *tokens = (char *)malloc((MAX * 2) * sizeof(char));
        
        for(tokenI = 0; tokenI < strlen(array); tokenI++) {
            if (array[tokenI] != '>' && array[tokenI] != '<') {
                tokens[tokenJ++] = array[tokenI];
            } else {
                tokens[tokenJ++] = ' ';
                tokens[tokenJ++] = array[tokenI];
                tokens[tokenJ++] = ' ';
            }
        }
        tokens[tokenJ++] = '\0';
        
        char *end;
        end = tokens + strlen(tokens) - 1;
        end--;
        *(end + 1) = '\0';
        
        if (tokens[strlen(tokens) - 1] == '&') {
            programWait = 0;
            tokens[strlen(tokens) - 1] = '\0';
        }
        
        char *arg = strtok(tokens, " "); 
        int i = 0;
        while(arg) {
            if (*arg == '<') {
                redirectIn(strtok(NULL, " "));
            } else if (*arg == '>') {
                redirectOut(strtok(NULL, " "));
            } else if (*arg == '|') {
	        args[i] == NULL;
		createPipe(args);
		i = 0;
	    }else {
                args[i] = arg;
                i++;
            }
            arg = strtok(NULL, " ");
        }
        args[i] = NULL;
	
        beginProcess(args);
    }
    return 0;
}
