#include <stdlib.h>

#include "string.h"
#include "environment.h"


/**
 * copy_env - Creates a duplicate of an environment
 * @env: The environment to duplicate
 *
 * Return: A pointer to the duplicate
 */
char **copy_env(char **env)
{
	int i, len;
	char **new_env;

	if (env == NULL)
		return (NULL);
	for (len = 0; env[len] != NULL; len++)
		continue;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (new_env == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		new_env[i] = NULL;
	for (i = 0; i < len; i++)
	{
		int j, s_len;

		s_len = _strlen(env[i]);
		new_env[i] = malloc(s_len + 2);
		if (new_env[i] == NULL)
		{
			free_env(new_env);
			return (NULL);
		}
		for (j = 0; j < s_len; j++)
		{
			new_env[i][j] = env[i][j];
		}
		new_env[i][s_len] = '\0';
	}
	new_env[i] = NULL;
	return (new_env);
}


/**
 * free_env - Deallocate memory for an environment
 * @env: Environment to free
 */
void free_env(char **env)
{
	int i;

	if (env == NULL)
		return;
	for (i = 0; env[i] != NULL; i++)
	{
		free(env[i]);
	}
	free(env);
}
