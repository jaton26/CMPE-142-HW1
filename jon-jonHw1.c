// homework 1
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv [])
{
	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;
	while((linelen = getline(&line, &linesize, stdin)) != -1) {
		if (strncmp ("exit", line, 4) == 0){
			exit(0);
		}
		
		fwrite(line, linelen, 1, stdout);
	}
	
	free(line);
	if(ferror(stdin)) {
		err(1, "getline");
	}
}