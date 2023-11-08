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
			exit(exit_status);
		}
	}
}
