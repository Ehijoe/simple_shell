#include "comments.h"
#include "io.h"
#include <stdlib.h>

/**
 * ex_comment - removes comment from input string
 * @line: input string
 *
 * Return: strings from the input without
 *         the comment and characters after it
 */
char *ex_comment(char *line)
{
	int i, count_to = 0;

	while (line[i] != '\0')
	{
		for (i = 0; line[i]; i++)
		{
			if (line[i] == '#')
			{
				return (NULL);
				if (line[i + 1])
				{
					line[i + 1] = '\0';
					i++;
				}
			}
		}
		return (line);
	}
}