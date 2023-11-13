#include "shell.h"
/**
 * free_tokens - function to free memmory allocated to tokens
 * @tokens: tokens obtained from strtok
 */
void free_tokens(char **tokens)
{
	int i;

	if (tokens == NULL)
		return;

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}

	free(tokens);
}
