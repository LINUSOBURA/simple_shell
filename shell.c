#include "shell.h"
/**
 * main - entry point of our code
 * @argc: arguments count
 * @argv: Arguments array
 * Return: 0 sucess
*/
int main(int argc, char **argv)
{
	char *prompt = ":) ";
	size_t n = 0;
	char *line = NULL, *line_cpy = NULL, *token = NULL, *shell_name = NULL;
	ssize_t chars_read;
	const char *delim = " \n";
	int num_tokens = 0, i, exit_command = 1, child_exit_status, exec_status;
	pid_t child_pid;
	(void)argc;

	if (argc > 0)
		{
			shell_name = argv[0];
		}

	while (exit_command)
	{
		if (isatty(0))
			printf("%s", prompt);

		chars_read = getline(&line, &n, stdin);
		if (chars_read == -1)
		{
			break;
		}

		if (chars_read == 1 && line[0] == '\n')
			continue;

		line_cpy = strdup(line);

		token = strtok(line, delim);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		if (num_tokens == 0)
		{
			free(line_cpy);
			continue;
		}

		if (num_tokens > 0)
		{
			argv = malloc(sizeof(char *) * (num_tokens + 1));
			if (argv == NULL)
			{
				perror("memmory allocation failed");
				return (-1);
			}
			token = strtok(line_cpy, delim);
			for (i = 0; token != NULL; i++)
			{
				argv[i] = malloc(strlen(token) + 1);
				if (argv[i] == NULL)
				{
					perror("malloc");
					return (-1);
				}
				strcpy(argv[i], token);

				token = strtok(NULL, delim);
			}
			argv[i] = NULL;

			if (argv[0] == NULL)
			{
				continue;
			}

			if (strcmp(argv[0], "exit") == 0)
			{
				exit_command = 0;
				break;
			}

			/* Execute the command*/
			child_pid = fork();
			if (child_pid == 0)
			{
				exec_status = execvp(argv[0], argv);
				if (exec_status == -1)
				{
					fprintf(stderr, "%s: 1: %s: not found\n", shell_name, argv[0]);
					exit(1);
				}
			}

			waitpid(child_pid, &child_exit_status, 0);
			if (child_exit_status != 0)
			{
				exit(127);
			}

			for (i = 0; argv[i] != NULL; i++)
			{
				free(argv[i]);
			}
			free(argv);

		}
		else
		{
			exit_command = 1;
		}

	}
	free(line);
	free(line_cpy);
	return (0);
}
