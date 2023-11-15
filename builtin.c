#include "shell.h"

/**
 * shell_exit - Exit the shell
 * @argv: Array of command arguments
 * @shell_name: name of the program
 * Return: -1 to signal the shell to exit
 */

int shell_exit(char **argv, const char *shell_name)
{
	char *endptr;
	int exit_status;

	if (argv[1] != NULL)
	{
		exit_status = strtol(argv[1], &endptr, 10);

		if (*endptr == '\0' && exit_status >= 0)
		{
			exit(exit_status);
		}
		else
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", shell_name, argv[1]);
			exit(2);
		}
	}
	else
	{
		exit(0);
	}
	return (0);
}

/**
 * is_builtin - Check if a command is a built-in command
 * @command: The command to check
 * Return: 1 if built-in, 0 otherwise
 */

int is_builtin(char *command)
{
	if (strcmp(command, "cd") == 0 || strcmp(command, "exit") == 0)
	{
		return (1);
	}

	return (0);
}

/**
 * execute_builtin - Execute a built-in command
 * @tokens: Array of command tokens
 * @shell_name: Name of the shell program
 * Return: 0 on success, -1 on failure
 */
int execute_builtin(char **tokens, const char *shell_name)
{
	(void)shell_name;

	if (strcmp(tokens[0], "cd") == 0)
	{
		return (shell_cd(tokens));
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
		return (shell_exit(tokens, shell_name));
	}

	return (-1);
}
