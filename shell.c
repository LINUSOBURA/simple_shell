#include "shell.h"

/**
 * display_prompt - displays the shell prompt
*/
void display_prompt(void)
{
	char *prompt = ":) ";

	if (isatty(0))
		write(1, prompt, strlen(prompt));
}

/**
 * process_input - reads and processes user input
 * @line: pointer to the input buffer
 * @n: size of the input buffer
 * @exit_command: flag to determine whether to exit the shell
 * @shell_name: name of the shell program
 */
void process_input(char **line, size_t *n, int *exit_command, char *shell_name)
{
	ssize_t chars_read;
	char **tokens;

	chars_read = getline(line, n, stdin);
		if (chars_read == -1)
		{
			*exit_command = 0;
			return;
		}

	if (chars_read == 1 && (*line)[0] == '\n')
		return;

	tokens = tokenize_input(*line);

		if (tokens == NULL || tokens[0] == NULL)
		{
			free_tokens(tokens);
			return;
		}

		if (strcmp(tokens[0], "exit") == 0)
		{
			*exit_command = 0;
			return;
		}
		else
		{
			execute_command(tokens, shell_name);
			free_tokens(tokens);
		}

}
/**
 * main - entry point of our code
 * @argc: arguments count
 * @argv: Arguments array
 * Return: 0 success
 */
int main(int argc, char **argv)
{
	size_t n = 0;
	char *line = NULL, *shell_name = NULL;
	int exit_command = 1;
	(void)argc;

	shell_name = argv[0];

	while (exit_command)
	{
		display_prompt();
		process_input(&line, &n, &exit_command, shell_name);
	}

	free(line);
	return (0);
}
