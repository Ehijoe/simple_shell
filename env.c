#include <stdlib.h>

#include "env.h"
#include "string.h"
#include "arguments.h"



/**
 * startsWith - checks if s starts with ndl
 *
 * @s: the string to check
 * @ndl: the search string
 * Return: 0 if false
 *
 * else returns the next index after ndl in s
 */
int startsWith(char *s, char *ndl)
{
	int i = 0;

	if (!s || !ndl)
		return (0);
	while (ndl[i])
	{
		if (ndl[i] != s[i])
			return (0);
		i++;
	}
	if (s[i] == '=')
		return (i);
	return (0);
}



/**
 * is_valid_key - Checks if a key is a valid variable name
 * @key: The key to check
 *
 * Return: 1 if valid and 0 otherwise
 */
int is_valid_key(char *key)
{
	int i;

	if (key == NULL)
		return (0);
	if (key[0] == '\0')
		return (0);
	for (i = 0; key[i] != '\0'; i++)
	{
		if (key[i] == '=' || is_whitespace(key[i]))
			return (0);
	}

	return (1);
}




/**
 * get_env - gets an environment variable
 *
 * @key: key of the variable
 * @environ: The environment to search
 *
 * Return: address of value of key if found
 *         null if not found
 */
char *get_env(char *key, char **environ)
{
	char **envs;
	int i, j;

	if (!is_valid_key(key))
		return (0);
	for (i = 0, envs = environ; envs[i]; i++)
	{
		j = startsWith(envs[i], key);
		if (j)
			return (envs[i] + 1 + j);
	}
	return (0);
}





/**
 * set_env - sets an environment variable
 *
 * @key: key of the variable
 * @val: value of the variable
 * @env: A pointer to the environment to modify
 *
 * Return: 0 success -1 failed
 */
int set_env(char *key, char *val, char ***env)
{
	int i = 0;
	char *key_val, **temp, *key_eq, **environ;

	if (!is_valid_key(key))
		return (-1);
	/* reserve space for env */
	key_eq = _strcat(key, "=");
	key_val = _strcat(key_eq, val);
	free(key_eq);
	environ = *env;
	/* check if key exist and overwrite */
	while (environ[i])
	{
		if (startsWith(environ[i], key))
		{
			free(environ[i]);
			environ[i] = key_val;
			return (0);
		}
		i++;
	}
	/* key is new add it */
	temp = malloc((i + 2) * sizeof(char *));
	if (!temp)
		return (-1);
	for (i = 0; environ[i]; i++)
		temp[i] = environ[i];
	free(environ);
	*env = temp;
	(*env)[i] = key_val;
	(*env)[i + 1] = NULL;
	return (0);
}





/**
 * unset_env - unsets an environment variable
 * @key: key of the variable
 * @env: The environment to change
 *
 * Return: 0 success -1 failed
 */
int unset_env(char *key, char ***env)
{
	int i = 0, j = 0, index = -1;
	char **temp, **environ;

	environ = *env;
	if (!is_valid_key(key))
		return (-1);
	/* check if key exist and save the index */
	while (environ[i])
	{
		if (startsWith(environ[i], key))
			index = i;
		i++;
	}
	/* if key is not found */
	if (index == -1)
		return (0);
	/* key is found remove it */
	temp = malloc(i * sizeof(char *));
	if (!temp)
		return (-1);
	for (i = 0; environ[i]; j++, i++)
	{
		if (i == index)
		{
			free(environ[i]);
			j--;
			continue;
		}
		temp[j] = environ[i];
	}
	temp[j] = NULL;
	free(environ);
	*env = temp;
	return (0);
}
