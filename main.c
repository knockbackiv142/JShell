#include <stdio.h>
#include <stdlib.h>
#include "./lib/linenoise.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"

#define PROMPT "jshell$ "
#define HISTORY_LENGTH 1024
#define MAX_ARGS 1024
#define TOKEN_SEP " \t"

int s_read(char *input, char **args) {
	int i = 0;
	char *token = strtok(input, TOKEN_SEP);
	while (token != NULL && i < (MAX_ARGS - 1)) {
		args[i++] = token;
		token = strtok(NULL, TOKEN_SEP);
	}
	args[i] = NULL;
	return i;
}
int s_execute(char *cmd, char **cmd_args) {

	int status;
	pid_t pid;
	if (is_builtin(cmd_args[0])) {
		return run_builtin(cmd_args);
		
	}
	pid = fork();
	if (pid < 0) {
		return 1;
	}

	if (pid == 0) {
		execv(cmd, cmd_args);
		perror("execv");
		exit(1);
		
	} else {
		if (waitpid (pid, &status, 0) != pid) {
			return 1;
		}
	}
	return status;
}




char *path_finder(char *command) {
	char *path = getenv("PATH");
	if(!path) return NULL;

	char *pathcopy = strdup(path);
	char *dir = strtok(pathcopy, ":");
	static char fullpath[512];

	while (dir != NULL) {
		snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, command);
		if (access(fullpath, X_OK) == 0) {
			free(pathcopy);
			return fullpath;
		}
		dir = strtok(NULL, ":");
	}
	free(pathcopy);
	return NULL;
}





int main(void) {
  if (!linenoiseHistorySetMaxLen(HISTORY_LENGTH)) {
    fprintf(stderr, "Could not set linenoise history!");
    exit(1);    
  }

  char *line;  
  char *args[MAX_ARGS];

  while((line = linenoise(PROMPT)) != NULL) {
    int args_read = s_read(line, args);
    
    if (args_read == 0) {
	linenoiseFree(line);
	continue;
    }
    /* built-ins go first */
    if (is_builtin(args[0])) {
    	run_builtin(args);
    	linenoiseHistoryAdd(line);
    	linenoiseFree(line);
    	continue;               // do NOT search PATH or fork
    }

/* external command */
    char *cmd = path_finder(args[0]);
    if (cmd == NULL) {
    	fprintf(stderr, "%s: command not found\n", args[0]);
 	linenoiseHistoryAdd(line);
    	linenoiseFree(line);
    	continue;
    }

    s_execute(cmd, args);	
    linenoiseHistoryAdd(line);
    linenoiseFree(line);    
  }

  return 0;
}






