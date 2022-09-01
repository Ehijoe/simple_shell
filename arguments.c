#include <stdlib.h>
#include <stdio.h>

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
	int i, j, k, l;
	int args;

	args = count_args(line);
	argv = malloc(sizeof(char *) * (args + 1));
	if (argv == NULL)
	{
		perror("malloc");
		exit(1);
	}
	argv[args] = NULL;

	for (l = 0; l < args; l++)
	{
		for (i = 0; is_whitespace(line[i]) == 1; i++)
			continue;
		for (j = 0; is_whitespace(line[i + j]) == 0; j++)
			continue;
		argv[l] = malloc(j);
		if (argv[l] == NULL)
		{
			perror("malloc");
			exit(1);
		}
		for (k = 0; k < j; k++)
		{
			argv[l][k] = line[i + k];
		}
		line += i + j;
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
 * count_args - Counts the number of arguments in a line
 * @line: A pointer to the line
 *
 * Return: The number of separate tokens in the line
 */
int count_args(char *line)
{
	int args = 0, i;
	int in_arg;

	in_arg = 0;
	for (i = 0; line[i] != '\0'; i++)
	{
		if (is_whitespace(line[i]))
		{
			in_arg = 0;
		}
		else if (!in_arg)
		{
			in_arg = 1;
			args++;
		}
	}
	return (args);
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
