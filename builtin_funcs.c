#include <stdlib.h>
#include <unistd.h>

#include "io.h"

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
		print(STDERR_FILENO, ": Could not find environment.");
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
