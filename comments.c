#include "comments.h"


/**
 * ex_comment - removes comment from input string
 * @line: input string
 */
char *ex_comment(char *line)
{
	int i;

	for (i = 0; line[i] != '0'; i++)
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			break;
		}
	}
	return (line);
}
