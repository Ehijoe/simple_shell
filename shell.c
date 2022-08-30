#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "shell.h"
#include "io.h"


/**
 * main - Entry point
 */
int main(int argc, char **argv, char **env)
{
	char *buffer = NULL;
	unsigned int buf_size = 0;
	int nread;

	if (env == NULL)
		exit(1);
	if (argc > 1)
	{
		errno = 38;
		perror(argv[0]);
		exit(1);
	}
	while (1)
	{
		display_prompt();
		nread = readline(&buffer, &buf_size, STDIN_FILENO);
		if (nread == -1)
		{
			perror(argv[0]);
			break;
		}
		if (nread == 0)
			break;
	}
	print(STDOUT_FILENO, "\n");
	free(buffer);
	exit(0);
	return (0);
}


/**
 * display_prompt - Displays the prompt for the user to enter a command
 */
void display_prompt(void)
{
	print(STDOUT_FILENO, "$ ");
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
		execve(arg_list[0], arg_list, environment);
		exit(126);
	}
	wait(&status);
	return (status);
}
