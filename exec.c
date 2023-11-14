#include "shell.h"

/**
 * exec_comm - executes the given command
 * @command: the command to execute
 * @argv: arguments for the command
 * @env: environment variables
 */
void exec_comm(char *command, char **argv, char **env)
{
	pid_t pid;
	int status, exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(command, argv, env) == -1)
		{
			perror(command);
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Waitpid");
			exit(1);
		}
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
		{
			fprintf(stderr, "Command '%s' failed with the exit status %d\n",
			command, exit_status);

		}
	}
}

/**
 * exec_shell_command - executes shell-specific commands
 * @command: the command to execute
 * @argv: arguments for the command
 * @env: environment variables
 */

void exec_shell_command(char *command, char **argv, char **env)
{
	if (strcmp(command, "env") == 0)
	{
		print_environment();
	}
	else
	{
		char *actual_command = command_location(command);

		if (actual_command == NULL)
		{
			fprintf(stderr, "Failed to find command '%s'\n", command);
			return;
		}

		exec_comm(actual_command, argv, env);
	}
}

/**
 * exec - function to excetute commands passed to our shell
 * @argv: arguments
*/
void exec(char **argv)
{
	char *command = NULL;
	char **env = environ;

	if (argv && argv[0])
	{
		command = argv[0];
		exec_shell_command(command, argv, env);
	}
}
