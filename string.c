#include "string.h"

/**
 * _strlen - calculates the length of a string
 * @s: pointer to the string
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		continue;
	}
	return (i);
}






/**
 * _strcmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: 0, if both strings are equal
 * negative number, if s1 is less than s2
 * positive number, if s2 is less than s1
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, diff = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
		{
			diff = s1[i] - s2[i];
			break;
		}
	}

	return (diff);
}






/**
 * _strcat - concatenates two strings
 * @string1: pointer to the destination string
 * @string2: pointer to the source string
 *
 * Return: Pointer to concatenated string or NULL on error
 */
char *_strcat(char *string1, char *string2)
{
	unsigned int i;
	unsigned int length1, length2, length3;
	char *full_string;

	length1 = _strlen(string1);
	length2 = _strlen(string2);
	length3 = length1 + length2 + 1;

	full_string = malloc(length3 + 1);
	if (full_string == NULL)
		return (NULL);

	for (i = 0; i < length1; i++)
		full_string[i] = string1[i];

	for (i = 0; i < length2; i++)
		full_string[length1 + i] = string2[i];

	full_string[length3 - 1] = '\0';

	return (full_string);
}
