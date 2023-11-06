#include "shell.h"
/**
 * exec - function to excetute commands passed to our shell
 * @argv: arguments
*/
void exec(char **argv)
{
	char *command = NULL, *actual_command = NULL;
	pid_t pid;
	int status;

	if (argv)
	{
		command = argv[0];

		actual_command = command_location(command);

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
				perror("Error:");
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
}
