#ifndef BUILTINS_H
#define BUILTINS_H

typedef int (*builtin_func)(char **, char *, char ***);

/**
 * struct builtin - A struct that stores the info of a shell builtin
 * @name: The name of the builtin
 * @func: The function to call the builtin
 */
typedef struct builtin
{
	char *name;
	builtin_func func;
} builtin_s;

int check_builtins(char **arglist, char *shell_name, char ***env);

int builtin_exit(char **arglist, char *shell_name, char ***env);
int builtin_env(char **arglist, char *shell_name, char ***env);
int builtin_setenv(char **arglist, char *shell_name, char ***env);
int builtin_unsetenv(char **arglist, char *shell_name, char ***env);

#endif
