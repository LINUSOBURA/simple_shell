#include "shell.h"
/**
 * print_environment - function to print enviroment variables
*/
void print_environment(void)
{
	char **env = environ;

	for (env = environ; *env != NULL; env++)
	{
	printf("%s\n", *env);
	}
}
