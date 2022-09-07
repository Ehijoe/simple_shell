#include <stdlib.h>

#include "exit.h"
#include "path.h"
#include "environment.h"
#include "arguments.h"


/**
 * safe_exit - Exits without any memory leaks
 * @status: The exit status or -1
 * @arglist: Pointer to Argv to be freed
 * @env: Pointer to Environment to be freed
 * @path_list: Pointer to The path list to be freed
 * @buffer: Pointer to The readline buffer to be freed
 *
 * Description: If status is -1 stores the arguments in static variables
 *              Otherwise it frees the allocated memory and exits
 */
void safe_exit(int status,
	       char ***arglist,
	       char ***env,
	       path_node_s **path_list,
	       char **buffer)
{
	static char ***arglist_store;
	static char ***env_store;
	static path_node_s **path_list_store;
	static char **buffer_store;

	if (status == -1)
	{
		arglist_store = arglist;
		env_store = env;
		path_list_store = path_list;
		buffer_store = buffer;
		return;
	}

	free(*buffer_store);
	free_env(*env_store);
	free_path(*path_list_store);
	del_arglist(*arglist_store);
	exit(status);
}
