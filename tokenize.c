#include "shell.h"

/**
 * allocate_and_copy - allocates memory and copies a string
 * @str: the string to copy
 * Return: a pointer to the new string
 */
char *allocate_and_copy(const char *str)
{
	char *copy = strdup(str);

	if (copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (copy);
}

/**
 * tokenize_input - tokenizes the input string
 * @input: the input string to tokenize
 * Return: array of tokens
 */

char **tokenize_input(char *input)
{
	const char *delim = " \n";
	char *input_cpy = allocate_and_copy(input);
	char **argv, *token = strtok(input_cpy, delim);
	int num_tokens = 0, i;

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}

	free(input_cpy);

	if (num_tokens == 0)
	{
		return (NULL);
	}

	argv = malloc(sizeof(char *) * (num_tokens + 1));
	if (argv == NULL)
	{
		perror("memory allocation failed");
		exit(EXIT_FAILURE);
	}

	input_cpy = allocate_and_copy(input);
	token = strtok(input_cpy, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = allocate_and_copy(token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	free(input_cpy);
	return (argv);
}
