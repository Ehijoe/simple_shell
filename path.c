#include <stdlib.h>
#include <unistd.h>

#include "path.h"
#include "env.h"
#include "string.h"


/**
 * build_path - Builds a linked list of the binary paths
 * @env: The environment that stores the PATH variable
 *
 * Return: A pointer to the first node of the list
 */
path_node_s *build_path(char **env)
{
	int i, j, k;
	char *path_var;
	path_node_s *path_list, *new_node;

	path_var = get_env("PATH", env);
	if (path_var == NULL)
		return (NULL);
	path_list = NULL;
	for (i = 0; path_var[i] != '\0'; i++)
	{
		for (j = 0; path_var[i + j] != ':' && path_var[i + j] != '\0'; j++)
			continue;
		new_node = malloc(sizeof(path_node_s));
		if (new_node == NULL)
		{
			free_path(path_list);
			return (NULL);
		}
		new_node->next = path_list;
		path_list = new_node;
		new_node->path = malloc(j + 1);
		if (new_node->path == NULL)
		{
			free_path(path_list);
			return (NULL);
		}
		for (k = 0; k < j; k++)
			new_node->path[k] = path_var[i + k];
		new_node->path[j] = '\0';
		i += j;
	}
	return (path_list);
}


/**
 * free_path - Frees the memory allocated for the path linked list
 * @list: Pointer to the first node of the list
 */
void free_path(path_node_s *list)
{
	if (list == NULL)
		return;

	free_path(list->next);
	if (list->path != NULL)
		free(list->path);
	free(list);
}


/**
 * search_path - Searches if a program is in the path or is a valid executable
 * @prog_name: Name of the program
 * @path: Pointer to the first node of the path list
 *
 * Return: A pointer to the full path or NULL if the program is invalid
 */
char *search_path(char *prog_name, path_node_s *path)
{
	path_node_s *curr;
	char *full_name, *dir;

	for (curr = path; curr != NULL; curr = curr->next)
	{
		dir = _strcat(curr->path, "/");
		full_name = _strcat(dir, prog_name);
		free(dir);
		if (access(full_name, X_OK) == 0)
		{
			return (full_name);
		}
		free(full_name);
	}
	if (access(prog_name, X_OK) == 0)
	{
		return (prog_name);
	}
	return (NULL);
}
