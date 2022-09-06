#ifndef PATH_H
#define PATH_H

/**
 * struct path_node - A node on the path list
 * @path: A path that contains binaries
 * @next: The next node on the list or NULL
 */
typedef struct path_node
{
	char *path;
	struct path_node *next;
} path_node_s;

path_node_s *build_path(char **env);
void free_path(path_node_s *list);

#endif
