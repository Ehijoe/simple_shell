#ifndef EXIT_H
#define EXIT_H

#include "path.h"

void safe_exit(int status,
	  char ***arglist,
	  char ***env,
	  path_node_s * *path_list,
	  char **buffer);

#endif
