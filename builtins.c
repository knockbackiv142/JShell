#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"

struct builtin {
	char *cmd; // cmd name
	int (*func)(char **args); // handling function
};

static struct builtin builtins[] = {
	{"cd", builtin_cd},
	{"exit", builtin_exit},
	{"pwd", builtin_pwd},
	
};

static int builtin_count() {
	return sizeof(builtins) / sizeof(builtins[0]);
}

int is_builtin(char *cmd) {
	for (int i = 0; i < builtin_count(); i++){
		if (strcmp(cmd, builtins[i].cmd) == 0) {
			return 1;
		}
	}
	return 0;
}

int run_builtin(char **args) {
	for (int i = 0; i < builtin_count(); i++){
		if (strcmp(args[0], builtins[i].cmd) == 0) {
			return builtins[i].func(args);
		}

	}
	return 1;
}


// BUILT-INS

int builtin_cd(char **args) {
	if (args[1] == NULL) {
		printf("missing folder\n");
		return 0;
	}

	if (chdir(args[1]) != 0){
		perror("cd");
	} 
	return 1;
}

int builtin_exit(char **args) {
	exit(0);
}

int builtin_pwd(char **args) {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL){
		printf("%s\n", cwd);
	}
	return 1;
}



