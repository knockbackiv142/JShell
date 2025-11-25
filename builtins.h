#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtin(char *cmd);
int run_builtin(char **args);

int builtin_cd(char **args);
int builtin_exit(char **args);
int builtin_pwd(char **args);


#endif

