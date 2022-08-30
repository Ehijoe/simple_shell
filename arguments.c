#include <stdlib.h>

#include "arguments.h"


/**
 * parse - Parses a command line and returns a list of arguments
 * @line: The command line to pass
 *
 * Return: A pointer to the argument vector
 */
char **parse(char *line)
{
	char **argv;
	int i, j, k;

	argv = malloc(sizeof(char *) * 2);
	argv[1] = NULL;
	for (i = 0; is_whitespace(line[i]) == 1; i++)
		continue;
	for (j = 0; is_whitespace(line[i + j]) == 0; j++)
		continue;
	argv[0] = malloc(j);
	for (k = 0; k < j; k++)
	{
		argv[0][k] = line[i + k];
	}

	return (argv);
}


/**
 * is_whitespace - Checks if a character is NUL or whitespace
 * @c: Character to check
 *
 * Return: 1 if whitespace and 0 otherwise
 */
int is_whitespace(char c)
{
	char *whitespaces = " \n\t\r\f\v";
	int i;

	for (i = 0; whitespaces[i] != '\0'; i++)
	{
		if (c == whitespaces[i])
			return (1);
	}
	if (c == '\0')
		return (1);
	return (0);
}


/**
 * del_arglist - Delete a list of arguments
 * @arglist: List of arguments to delete
 */
void del_arglist(char **arglist)
{
	int i;

	if (arglist == NULL)
		return;
	for (i = 0; arglist[i] != NULL; i++)
	{
		free(arglist[i]);
		arglist[i] = NULL;
	}
	free(arglist);
	arglist = NULL;
}
