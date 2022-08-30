#include "io.h"
#include "string.h"

#include <unistd.h>
#include <stdlib.h>

/**
 * print - Prints a string to a file
 * @fd: File descriptor of the file to print to
 * @s: A pointer to the string
 *
 * Return: Number of characters printed and -1 on error
 */
int print(int fd, char *s)
{
	int len, printed;

	if (s == NULL)
	{
		return (-1);
	}
	len = _strlen(s);
	printed = write(fd, s, len);
	if (printed == -1)
	{
		return (-1);
	}
	return (printed);
}


/**
 * extend - Doubles the size of a buffer
 * @buffer: A pointer to the buffer
 * @n: A pointer to the size of the buffer
 *
 * Return: 1 on success and -1 on failure
 */
int extend(char **buffer, unsigned int *n)
{
	char *new_buffer;
	unsigned int i;

	if (buffer == NULL || n == NULL)
		return (-1);
	if (*buffer == NULL || *n == 0)
	{
		*buffer = malloc(MIN_LINE_SIZE);
		if (*buffer == NULL)
			return (-1);
		*n = MIN_LINE_SIZE;
		return (1);
	}

	new_buffer = malloc((*n) * 2);
	if (new_buffer == NULL)
		return (-1);

	for (i = 0; i < *n; i++)
		new_buffer[i] = (*buffer)[i];
	free(*buffer);
	*buffer = new_buffer;
	*n *= 2;
	return (1);
}

/**
 * readline - Reads a line from a file
 * @buffer: A pointer to the buffer to read into
 * @n: A pointer to the size of the buffer
 * @fd: File descriptor of the file to read from
 *
 * Return: The number of characters read including the '\n' or -1 on error
 */
int readline(char **buffer, unsigned int *n, int fd)
{
	unsigned int nread = 0;
	int file_not_ended = 1;
	char c = '\0';

	if (buffer == NULL || n == NULL)
		return (-1);
	if (*buffer == NULL || *n == 0)
	{
		*buffer = malloc(MIN_LINE_SIZE);
		if (*buffer == NULL)
			return (-1);
		*n = MIN_LINE_SIZE;
	}
	file_not_ended = read(fd, &c, 1);
	if (!file_not_ended)
	{
		(*buffer)[0] = '\0';
		return (0);
	}
	while (file_not_ended && c != '\n')
	{
		if (file_not_ended == -1)
		{
			free(*buffer);
			*buffer = NULL;
			*n = 0;
			return (-1);
		}
		(*buffer)[nread] = c;
		nread++;
		if (nread + 1 >= *n)
		{
			extend(buffer, n);
		}
		file_not_ended = read(fd, &c, 1);
	}
	(*buffer)[nread] = '\n';
	(*buffer)[nread + 1] = '\0';
	return (nread + 1);
}
