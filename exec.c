#include "shell.h"
/**
 * exec - function to excetute commands passed to our shell
 * @argv: arguments
*/
void exec(char **argv)
{
	char *command = NULL, *actual_command = NULL, **env;
	int status, exit_status = 0, signal;
	pid_t pid;
	extern char **environ;

	if (argv && argv[0])
	{
		command = argv[0];

		if (strcmp(command, "env") == 0)
		{
			for (env = environ; *env != NULL; env++)
			printf("%s\n", *env);
		}

		actual_command = command_location(command);
		if (actual_command == NULL)
		{
			fprintf(stderr, "Failed to find command '%s'\n", command);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(actual_command, argv, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free(actual_command);
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("Waitpid");
				exit(1);
			}

			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{
					fprintf(stderr, "Command '%s' failed with the exit status %d\n", command, exit_status);
					exit(exit_status);
				}
			}
			else if (WIFSIGNALED(status))
			{
				signal = WTERMSIG(status);
				fprintf(stderr, "Command '%s' terminated by signal %d\n", command, signal);
			}
		}

	}
}