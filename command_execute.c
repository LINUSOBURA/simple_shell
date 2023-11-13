#include "shell.h"

/**
 * execute_command - function to execute tokenized commands
 * @tokens: tokens got from strtok
 * @shell_name: name of the shell program
*/
void execute_command(char **tokens, const char *shell_name)
{
	pid_t child_pid;
	int child_exit_status, exec_status, exit_code;
	char *command_path;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		free_tokens(tokens);
		return;
	}

	else if (child_pid == 0)
	{
		if (strcmp(tokens[0], "env") == 0)
		{
			print_environment();
			free_tokens(tokens);
			exit(0);
		}
		command_path = command_location(tokens[0]);

		if (command_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", shell_name, tokens[0]);
			free_tokens(tokens);
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
			free_tokens(tokens);
			free(command_path);
			_exit(EXIT_FAILURE);

		}
	}
	else
	{
		 if (waitpid(child_pid, &child_exit_status, 0) == -1)
        {
            perror("Waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(child_exit_status))
        {
            exit_code = WEXITSTATUS(child_exit_status);
            if (exit_code != 0)
            {
				exit(exit_code);
            }
        }
        else if (WIFSIGNALED(child_exit_status))
        {
            exit_code = 128 + WTERMSIG(child_exit_status);
            fprintf(stderr, "Command '%s' terminated by signal %d\n", tokens[0], WTERMSIG(child_exit_status));
        }
        else
        {
            fprintf(stderr, "Child process terminated abnormally\n");
            exit(EXIT_FAILURE);
        }

        free_tokens(tokens);
    }
}
