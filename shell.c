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
#include "builtins.h"
#include "environment.h"
#include "path.h"
#include "exit.h"


/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: List of arguments
 * @environ: The environment
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv, char **environ)
{
	unsigned int buf_size = 0;
	int nread;
	char **arg_list, *shell_name, **env, *buffer = NULL;
	path_node_s *path_list;

	shell_name = argv[0];
	if (argc > 1)
	{
		errno = 38;
		perror(shell_name);
		exit(1);
	}
	env = copy_env(environ);
	if (env == NULL)
		exit(1);
	path_list = build_path(env);
	safe_exit(-1, &arg_list, &env, &path_list, &buffer);
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
		if (!check_builtins(arg_list, shell_name, &env))
		{
			run_command(arg_list, env, shell_name, path_list);
		}
		del_arglist(arg_list);
	}
	print(STDOUT_FILENO, "\n");
	free(buffer);
	free_env(env);
	free_path(path_list);
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
 * @shell_name: The name of the shell calling the command
 * @path: Linked list of binary paths
 *
 * Return: On success the exit status and on failure -1
 */
int run_command(char **arg_list,
		char **environment,
		char *shell_name,
		path_node_s *path)
{
	pid_t child;
	int status;
	struct stat comm_st = {0};
	char *prog_name;

	prog_name = search_path(arg_list[0], path);
	if (prog_name != NULL)
	{
		stat(arg_list[0], &comm_st);
		if (S_ISDIR(comm_st.st_mode))
		{
			if (prog_name != arg_list[0])
				free(prog_name);
			print(STDERR_FILENO, shell_name);
			print(STDERR_FILENO, ": ");
			errno = EISDIR;
			perror(arg_list[0]);
			return (-1);
		}
		child = fork();
		if (child == -1)
			return (-1);
		if (child == 0)
		{
			execve(prog_name, arg_list, environment);
			exit(126);
		}
		if (prog_name != arg_list[0])
			free(prog_name);
		wait(&status);
		return (status);
	}
	else
	{
		print(STDERR_FILENO, shell_name);
		print(STDERR_FILENO, ": ");
		errno = ENOENT;
		perror(arg_list[0]);
		return (-1);
	}
}
