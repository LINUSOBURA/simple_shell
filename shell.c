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
	char *line = NULL, *line_cpy = NULL, *token = NULL;
	ssize_t chars_read;
	const char *delim = " \n";
	int num_tokens = 0, i, exit_command = 1;
	(void)argc;

	while (1)
	{
		if (!exit_command)
		{
			printf("%s", prompt);
		}

		chars_read = getline(&line, &n, stdin);
		if (chars_read == -1)
		{
			return (-1);
		}

		line_cpy = strdup(line);

		token = strtok(line, delim);
		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		if (num_tokens > 0)
		{
			argv = malloc(sizeof(char *) * num_tokens);
			if (!argv)
			{
				return (-1);
			}
			token = strtok(line_cpy, delim);
			for (i = 0; token != NULL; i++)
			{
				argv[i] = malloc(strlen(token) + 1);
				strcpy(argv[i], token);

				token = strtok(NULL, delim);
			}
			argv[i] = NULL;

			if (strcmp(argv[0], "exit") == 0)
			{
				break;
			}

			/* Execute the command*/
			exec(argv);

		}

	}

	free(line), free(argv), free(line_cpy);
	return (0);
}
