#include <stdlib.h>

#include "exit.h"
#include "path.h"
#include "environment.h"
#include "arguments.h"


/**
 * safe_exit - Exits without any memory leaks
 * @setup: 1 if this is a setup call and 0 if it is an exit call
 * @status: Pointer to the exit status
 * @arglist: Pointer to Argv to be freed
 * @env: Pointer to Environment to be freed
 * @path_list: Pointer to The path list to be freed
 * @buffer: Pointer to The readline buffer to be freed
 *
 * Description: If status is -1 stores the arguments in static variables
 *              Otherwise it frees the allocated memory and exits
 */
void safe_exit(int setup,
	       int *status,
	       char ***arglist,
	       char ***env,
	       path_node_s **path_list,
	       char **buffer)
{
	static int *status_store;
	static char ***arglist_store;
	static char ***env_store;
	static path_node_s **path_list_store;
	static char **buffer_store;

	if (setup == 1)
	{
		status_store = status;
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
	if (status != NULL)
		exit(*status);
	exit(*status_store);
}
