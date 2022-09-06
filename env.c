#include "env.h"

/**
 * get_env - gets an environment variable
 *
 * @key: key of the variable
 * 
 * Return:	address of value of key if found
 * 			null if not found
 */
char *get_env(char *key)
{
	char **envs;
	int i, j;

	if (!key)
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
 * 
 * Return: 0 success -1 failed
 */
int set_env(char *key, char *val)
{
	int i = 0;
	char *key_val, **temp;

	if (!key || !key[0] || is_whitespace(key, '='))
		return (-1);
	/* reserve space for env */
	key_val = malloc(_strlen(key) + _strlen(val) + 2);
	if (!key_val)
		return (-1);
	key_val[0] = '\0';
	key_val = _strcat(key_val, key);
	key_val = _strcat(key_val, "=");
	key_val = _strcat(key_val, val);
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
	environ = temp;
	environ[i] = key_val;
	environ[i + 1] = NULL;
	return (0);
}





/**
 * unset_env - unsets an environment variable
 * @key: key of the variable
 * 
 * Return: 0 success -1 failed
 */
int unset_env(char *key)
{
	int i = 0, j = 0, index = -1;
	char **temp;

	if (!key || !key[0] || is_whitespace(key, '='))
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
	environ = temp;
	return (0);
}