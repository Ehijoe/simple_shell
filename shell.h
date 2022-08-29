#ifndef SHELL_H
#define SHELL_H

void display_prompt(void);
int run_command(char **arg_list, char **environment);

#endif
