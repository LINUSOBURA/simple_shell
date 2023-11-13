#include "shell.h"

/**
 * main - entry point of our code
 * @argc: arguments count
 * @argv: Arguments array
 * Return: 0 success
 */
int main(int argc, char **argv)
{
	char *prompt = ":) ";
	size_t n = 0;
	char *line = NULL, *shell_name = NULL;
	char **tokens;
	ssize_t chars_read;
	int exit_command = 1;
	(void)argc;

	shell_name = argv[0];

	while (exit_command)
	{
		if (isatty(0))
			write(1, prompt, strlen(prompt));

		chars_read = getline(&line, &n, stdin);
		if (chars_read == -1)
		{
			break;
		}

		if (chars_read == 1 && line[0] == '\n')
			continue;

		tokens = tokenize_input(line);

		if (tokens == NULL || tokens[0] == NULL)
		{
			free_tokens(tokens);
			continue;
		}

		if (strcmp(tokens[0], "exit") == 0)
		{
			exit_command = 0;
			free_tokens(tokens);
			break;
		}
		
		execute_command(tokens, shell_name);
	}

	free(line);
	return 0;
}
