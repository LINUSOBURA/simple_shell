#include "shell.h"

char **tokenize_input(char *input)
{
	char *input_cpy = NULL, *token = NULL, **argv;
	const char *delim = " \n";
	int num_tokens = 0, i, j;

	if (input == NULL)
	{
		return (NULL);
	}

	input_cpy = strdup(input);

	token = strtok(input_cpy, delim);
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;

	if (num_tokens == 0)
	{
		free(input_cpy);
		return (NULL);
	}

	if (num_tokens > 0)
	{
		argv = malloc(sizeof(char *) * (num_tokens + 1));
		if (argv == NULL)
		{
			perror("memmory allocation failed");
			free(input_cpy);
			return (NULL);
		}
		token = strtok(input, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(strlen(token) + 1);
			if (argv[i] == NULL)
			{
				perror("malloc");
				free(input);
				for (j = 0; j < i; j++)
				{
					free(argv[j]);
				}
				free(argv);
				return (NULL);
			}
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
	}
	free(input_cpy);
	return (argv);
}
