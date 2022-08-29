#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "shell.h"
#include "io.h"


/**
 * display_prompt - Displays the prompt for the user to enter a command
 */
void display_prompt(void)
{
	print("$ ");
}


/**
 * run_command - Runs a command as a new process
 * @arg_list: The argv for the command
 * @environment: The environment for the command
 *
 * Return: On success the exit status and on failure -1
 */
int run_command(char **arg_list, char **environment)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		execve(arg_list[0], arg_list, environ);
		exit(126);
	}
	wait(&status);
	return (status);
}
