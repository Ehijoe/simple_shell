#include <stdlib.h>
#include <unistd.h>

#include "io.h"
#include "env.h"
#include "environment.h"

/**
 * builtin_exit - exits with a specific status code
 * @arglist: The list of arguments passed
 * @shell_name: The name of the shell
 * @env: Pointer to the environment
 *
 * Return: 1 on success -1 on failure.
 */
int builtin_exit(char **arglist,
		 char *shell_name,
		 __attribute__ ((unused)) char ***env)
{
	int i;
	int status = 0;

	if (arglist == NULL)
		return (-1);
	/* Count number of arguments in arglist */
	for (i = 0; arglist[i] != NULL; i++)
		continue;

	if (i > 2)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, "exit: too many arguments\n");
		return (-1);
	}
	if (i == 2)
	{
		status = 0;
		i = 0;
		while (arglist[1][i] != '\0')
		{
			if (arglist[1][i] > '9' || arglist[1][i] < '0')
				return (-1);
			status *= 10;
			status += arglist[1][i] - '0';
			i++;
		}
	}
	free_env(*env);
	exit(status);
}


/**
 * builtin_env - Prints the shell environment
 * @arglist: List of arguments in command line
 * @shell_name: Name of the calling shell
 * @env: A pointer to the environment
 *
 * Return: 1 on success and -1 on failure
 */
int builtin_env(char **arglist, char *shell_name, char ***env)
{
	int i;
	char **environ;

	if (env == NULL || *env == NULL)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, arglist[0]);
		print(STDERR_FILENO, ": Could not find environment.\n");
		return (-1);
	}
	environ = *env;
	for (i = 0; environ[i] != NULL; i++)
	{
		print(STDOUT_FILENO, environ[i]);
		print(STDOUT_FILENO, "\n");
	}
	return (1);
}


/**
 * builtin_setenv - Sets an environment variable
 * @arglist: List of arguments in command line
 * @shell_name: Name of the calling shell
 * @env: A pointer to the environment
 *
 * Return: 1 on success and -1 on failure
 */
int builtin_setenv(char **arglist, char *shell_name, char ***env)
{
	int args;

	if (arglist == NULL)
		return (-1);
	for (args = 0; arglist[args] != NULL; args++)
		continue;
	if (args != 3)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, arglist[0]);
		print(STDERR_FILENO, ": Usage: env [variable name] [value].\n");
		return (-1);
	}
	if (set_env(arglist[1], arglist[2], env) == -1)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, arglist[0]);
		print(STDERR_FILENO, ": Could update environment.\n");
		return (-1);
	}
	return (1);
}


/**
 * builtin_unsetenv - Deletes an environment variable
 * @arglist: List of arguments in command line
 * @shell_name: Name of the calling shell
 * @env: A pointer to the environment
 *
 * Return: 1 on success and -1 on failure
 */
int builtin_unsetenv(char **arglist, char *shell_name, char ***env)
{
	int args;

	if (arglist == NULL)
		return (-1);
	for (args = 0; arglist[args] != NULL; args++)
		continue;
	if (args != 2)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, arglist[0]);
		print(STDERR_FILENO, ": Usage: env [variable name].\n");
		return (-1);
	}
	if (unset_env(arglist[1], env) == -1)
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		print(STDERR_FILENO, arglist[0]);
		print(STDERR_FILENO, ": Could update environment.\n");
		return (-1);
	}
	return (1);
}
