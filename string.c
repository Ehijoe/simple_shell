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
			diff = s1[i] - s2[i];
		break;
	}

	return (diff);
}






/**
 * _strcat - concatenates two strings
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 *
 * Return = destination
 */
char *_strcat(char *dest, char *src)
{
	int count1 = 0, count2 = 0;

	while (dest[count1] != '\0')
		count1++;

	while (src[count2] != '\0')
		dest[count1++] = src[count2++];

	return (dest);
}
