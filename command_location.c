#include "shell.h"

/**
 * check_absolute_path - checks if the command is an absolute path
 * @command: the command to check
 * Return: path to the command if absolute, NULL otherwise
 */
char *check_absolute_path(char *command)
{
	struct stat buffer;

	if (command == NULL)
	{
		return (NULL);
	}

	/*Check if the command is an absolute path*/
	if (command[0] == '/' || command[0] == '.')
	{
		/*If it is, check if the file exists*/
		if (stat(command, &buffer) == 0)
		{
			return (realpath(command, NULL));
		}
	}

	return (NULL);
}

/**
 * search_in_path - searches for the command in the PATH environment variable
 * @command: the command to search for
 * Return: path to the command if found, NULL otherwise
 */

char *search_in_path(char *command)
{
	char *path, *path_cpy, *path_token;
	struct stat buffer;

	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}

	path_cpy = strdup(path);
	path_token = strtok(path_cpy, ":");

	while (path_token != NULL)
	{
		char *file_path = malloc(strlen(path_token) + strlen(command) + 2);

		if (file_path == NULL)
		{
			free(file_path);
			return (NULL);
		}

		strcpy(file_path, path_token);
		if (strlen(path_token) > 0)
			strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buffer) == 0)
		{
			free(path_cpy);
			return (realpath(file_path, NULL));
		}

		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}
/**
 * command_location - fuction to get the path of entered command
 * @command: the command whose PATH is fetched
 * Return: path to the command
*/
void *command_location(char *command)
{
	char *absolute_path = check_absolute_path(command);

	if (absolute_path != NULL)
		return (absolute_path);

	return (search_in_path(command));
}
