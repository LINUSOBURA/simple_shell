#include "shell.h"

/**
 * execute_child_process - executes the command in the child process
 * @tokens: tokens got from strtok
 * @shell_name: name of the shell program
 */
void execute_child_process(char **tokens, const char *shell_name)
{
	char *command_path;
	int exec_status;

	if (strcmp(tokens[0], "env") == 0)
	{
		print_environment();
		exit(0);
	}
	command_path = command_location(tokens[0]);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", shell_name, tokens[0]);
		if (isatty(0))
		{
			return;
		}
		else
			exit(127);
	}

	exec_status = execve(command_path, tokens, NULL);
	if (exec_status == -1)
	{
		perror("execve failed");
		free(command_path);
		_exit(EXIT_FAILURE);

	}
}

/**
 * handle_child_termination - handles the termination of the child process
 * @child_pid: PID of the child process
 * @child_exit_status: exit status of the child process
 * @tokens: tokens got from strtok
 */

void handle_child_termination(pid_t child_pid, int *child_exit_status,
char **tokens)
{
	int exit_code;

	if (waitpid(child_pid, child_exit_status, 0) == -1)
	{
		perror("Waitpid");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(*child_exit_status))
	{
		exit_code = WEXITSTATUS(*child_exit_status);
		if (exit_code != 0)
		{
			exit(exit_code);
		}
	}
	else if (WIFSIGNALED(*child_exit_status))
	{
		exit_code = 128 + WTERMSIG(*child_exit_status);
		fprintf(stderr, "Command '%s' terminated by signal %d\n",
		tokens[0], WTERMSIG(*child_exit_status));
	}
	else
	{
		fprintf(stderr, "Child process terminated abnormally\n");
		exit(EXIT_FAILURE);
	}
}
/**
 * execute_command - function to execute tokenized commands
 * @tokens: tokens got from strtok
 * @shell_name: name of the shell program
*/
void execute_command(char **tokens, const char *shell_name)
{
	pid_t child_pid;
	int child_exit_status;
	char *command_path;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		return;
	}

	else if (child_pid == 0)
	{
		execute_child_process(tokens, shell_name);
	}
	else
	{
		handle_child_termination(child_pid, &child_exit_status, tokens);
	}
}
