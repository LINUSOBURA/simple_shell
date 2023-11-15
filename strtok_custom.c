#include "shell.h"
/**
 * custom_strtok - a custom tokenization fuction like strtok
 * @str: string pointer of what is entered by a user
 * @delimiters: delimeters used in tokenization
 * Return: Token start
*/
char *custom_strtok(char *str, const char *delimiters)
{
	static char *lastToken;
	char *tokenStart;

	if (str == NULL && lastToken == NULL)
	{
		return (NULL);
	}
	if (str != NULL)
	{
		lastToken = str;
	}
	else if (lastToken == NULL)
	{
		return (NULL);
	}

	tokenStart = lastToken;

	while (*lastToken != '\0' && strchr(delimiters, *lastToken) != NULL)
	{
		lastToken++;
	}

	if (*lastToken == '\0')
	{
		lastToken = NULL;
		return (NULL);
	}

	while (*lastToken != '\0' && strchr(delimiters, *lastToken) == NULL)
	{
		lastToken++;
	}

	if (*lastToken != '\0')
	{
		*lastToken = '\0';
		lastToken++;
	}
	return (tokenStart);
}
