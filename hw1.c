#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 128

int programWait = 1;
int isPathSet = 0;

void redirectOut(char *fileName) {
    printf("** redirectOut ** \n");
    int out = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

int main(int argc, char **argv)
{
    
    size_t length; //lenth of input
    char* args[MAX];
    char* path[MAX];
    
    //An infinite loop until the user enters "exit".
    while(1){
        printf("HW1 Shell >> ");
        fflush(stdout);
        char line[MAX];
        fgets(line, MAX, stdin);
        length = strlen(line);
        
        
        //Storing each string into an array.
        int i = 0;
        int j = 0;
        char* token = (char *)malloc((MAX * 2) * sizeof(char));
        
        for (i = 0; i < strlen(line); i++) {
            if (line[i] != '>') {
                token[j++] = line[i];
            } else {
                token[j++] = ' ';
                token[j++] = line[i];
                token[j++] = ' ';
            }
        }
        token[j++] = '\0';
        
	// adding Null terminator
        char *end;
        end = token + strlen(token) - 1;
        end--;
        *(end + 1) = '\0';
        
	// Adding " " as delimeters to arg
        char* arg = strtok(token, " ");
        i = 0;

	// redirection if user enters '>'. Otherwise, arg will be stored within args[].
        while(arg) {
            printf("** checking for > **\n");
            if (*arg == '>') {
                printf("** found '>' **\n");
                redirectOut(strtok(NULL, " "));
            } else {
                args[i] = arg;
                i++;
            }
            arg = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        //Testing to see if string are stored correctly.
        printf("args[0] = %s, args[1] = %s, args[2] = %s, len=%ld\n", args[0], args[1], args[2], strlen(args[0]));
        
        //If user is doing "cd" command, go into that file.
        if (!strcmp(args[0], "cd")){
            chdir(args[1]);
        }
        
        //fork
        int child_pid;
        
        //This will exit the code if the user types 'exit'.
        if(strcmp(args[0], "exit") != 0){
            child_pid = fork();
            if(child_pid == -1){ //Fork didn't work. throw perror
                perror("Unable to fork");
            } else if(child_pid == 0){ //Fork worked.
                execv(args[0], args);
            }
            else{ //Parent process wait
                if (programWait) {
                    waitpid(child_pid, NULL, 0);
                } else {
                    programWait = 0;
                }
            }
            // Return back to the terminal
            redirectOut("/dev/tty");
        } else {
            exit(1);
        }
    }
}

