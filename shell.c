#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "shell.h"
#include "io.h"
#include "arguments.h"


/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: List of arguments
 * @env: The environment
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv, char **env)
{
	char *buffer = NULL;
	unsigned int buf_size = 0;
	int nread;
	struct stat comm_st;
	char **arg_list;

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
		arg_list = parse(buffer);
		stat(arg_list[0], &comm_st);
		if (access(arg_list[0], X_OK) == 0 && S_ISREG(comm_st.st_mode))
			run_command(arg_list, env);
		else
			perror(arg_list[0]);
		del_arglist(arg_list);
	}
	print(STDOUT_FILENO, "\n");
	free(buffer);
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
