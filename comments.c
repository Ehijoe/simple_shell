#include "comments.h"


/**
 * ex_comment - removes comment from input string
 * @line: input string
 * @nread: The number of characters read into the string
 *
 * Return: The modified input string
 */
char *ex_comment(char *line, int nread)
{
	int i;

	for (i = 0; i < nread; i++)
	{
		if (line[i] == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
	}
	return (line);
}
