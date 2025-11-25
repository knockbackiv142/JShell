#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtin(char *cmd);
int run_builtin(char **args);

int builtin_cd(char **args);
int builtin_exit(char **args);
int builtin_pwd(char **args);
int builtin_echo(char **args);
int builtin_help(char **args);
int builtin_dirs(char **args);
int builtin_logout(char **args);
int builtin_suspend(char **args);
int builtin_kill(char **args);
int builtin_wait(char **args);

#endif

