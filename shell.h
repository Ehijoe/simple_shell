#ifndef SHELL_H
#define SHELL_H

#include "path.h"

void display_prompt(void);
int run_command(char **arg_list,
		char **environment,
		char *shell_name,
		path_node_s *path_list);

#endif
