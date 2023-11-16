#include "shell.h"
/**
 * shell_cd - function to handle builtin cd
 * @argv: array of arguments
 * Return: 0 success
*/
int shell_cd(char **argv)
{
	char *home_dir = getenv("HOME");
	char *current_dir = NULL;

	if (argv[1] == NULL || strcmp(argv[1], "-") == 0)
	{
		current_dir = getcwd(NULL, 0);
		if (current_dir == getcwd(NULL, 0))
		{
			return (-1);
		}

		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
			{
				return (-1);
			}
		}
		else
		{
			fprintf(stderr, "cd: No home directory.\n");
			return (-1);
		}
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			return (-1);
		}
	}
	free(current_dir);
	return (0);
}
