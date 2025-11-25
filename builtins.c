#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"

struct builtin {
	char *cmd; // cmd name
	int (*func)(char **args); // handling function
}

static struct builtin builtins[] = {
	{"cd", builtin_cd},
	{"exit", builtin_cd},
	{"pwd", builtin_cd},
	{"echo", builtin_cd},
	{"help", builtin_cd},
	{"dirs", builtin_cd},
	{"logout", builtin_cd},
	{"suspend", builtin_cd},
	{"kill", builtin_cd},
	{"wait", builtin_cd},
}
