#include "comments.h"
#include "io.h"
#include <stdlib.h>

/**
 * ex_comment - removes comment from input string
 * @line: input string
 * 
 * Return: strings from the input without
 *         the comment and character after it
 */
char *ex_comment(char *line)
{
	int i, count_to = 0;

	for (i = 0; line[i]; i++)
	{
		if (count_to[i] == '#')
		{
			if (i == 0)
			{
				free(line);
				return (NULL);
			}
			if (line[i - 1] == ' ' || line[i - 1] == '\t' || line[i - 1] == ';')
				count_to = i;
		}
	}
	if (count_to)
	{
		extend(line, count_to + 1);
		count_to = '\0';
	}
	return (line);

}
