#include "shell.h"
/**
 * shell_cd - function to handle builtin cd
 * @argv: array of arguments
 * Return: 0 success, -1 failure
*/
int shell_cd(char **argv)
{
	char *home_dir = getenv("HOME");
	char *current_dir = NULL;
	char *old_dir = NULL;

	if (home_dir == NULL)
	{
		perror("cd: No home directory");
		return (-1);
	}

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("cd: getcwd error");
		return (-1);
	}

	if (argv[1] == NULL)
	{
		if (chdir(home_dir) != 0)
		{
			perror("cd: chdir error");
			free(current_dir);
			return (-1);
		}
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		old_dir = getenv("OLDPWD");
		if (old_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(current_dir);
			return (-1);
		}
		if (chdir(old_dir) != 0)
		{
			perror("cd: chdir error");
			free(current_dir);
			return (-1);
		}
		printf("%s\n", old_dir);
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd: chdir error");
			free(current_dir);
			return (-1);
		}
	}

	if (setenv("OLDPWD", current_dir, 1) != 0)
	{
		perror("cd: setenv error");
		free(current_dir);
		return (-1);
	}

	free(current_dir);

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("cd: getcwd error");
		return (-1);
	}

	if (setenv("PWD", current_dir, 1) != 0)
	{
		perror("cd: setenv error");
		free(current_dir);
		return (-1);
	}

	free(current_dir);

	return (0);
}
