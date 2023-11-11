#include "shell.h"
/**
 * exec - function to excetute commands passed to our shell
 * @argv: arguments
*/
void exec(char **argv)
{
	char *command = NULL, *actual_command = NULL, **env;
	pid_t pid;
	int status, exit_status;

	env = __environ;
	if (argv && argv[0])
	{
		command = argv[0];

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
			if (strcmp(actual_command, "env") == 0)
			{
				while (*env != NULL)
				{
					printf("%s\n", *env);
				}
			}
			else
			{
				if (execve(actual_command, argv, NULL) == -1)
				{
					perror("execve");
					exit(1);
				}
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
				fprintf(stderr, "Command '%s' failed with the exit status %d\n", command, exit_status);
			}
		}
		if (execve(actual_command, argv, NULL) == 0)
		{
			free(actual_command);
		}
	}
}
