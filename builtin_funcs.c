#include <stdlib.h>
#include <unistd.h>

#include "io.h"

/**
 * builtin_exit - exits with a specific status code
 * @arglist: The list of arguments passed
 * @shell_name: The name of the shell
 *
 * Return: 1 on success -1 on failure.
 */
int builtin_exit(char **arglist, char *shell_name)
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
