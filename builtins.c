#include <stdlib.h>
#include <unistd.h>

#include "builtins.h"
#include "io.h"
#include "string.h"

/**
 * check_builtins - Checks if a command line is a builtin
 * @arglist: The list of arguments passed to the shell
 * @shell_name: The name of the shell
 *
 * Return: 1 if the command was a builtin and 0 otherwise
 */
int check_builtins(char **arglist, char *shell_name)
{
	int i;
	builtin_s builtins[] = {
		{"exit", builtin_exit},
		{NULL, NULL}
	};

	if (arglist == NULL)
	{
		print(STDERR_FILENO, "check_builtins: NULL arglist\n");
		return (0);
	}
	for (i = 0; arglist[i] != NULL; i++)
	{
		int j;

		for (j = 0; builtins[j].name != NULL; j++)
		{
			if (_strcmp(arglist[0], builtins[j].name) == 0)
			{
				builtins[j].func(arglist, shell_name);
				return (1);
			}
		}
	}
	return (0);
}
