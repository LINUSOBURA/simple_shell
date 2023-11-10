#include "shell.h"
/**
 * command_location - fuction to get the path of entered command
 * @command: the command whose PATH is fetched
 * Return: path to the command
*/
void *command_location(char *command)
{
	char *path, *path_cpy, *path_token, *file_path, *real_path;
	size_t command_len, directory_len;
	struct stat buffer;

	if (command == NULL)
	{
		return (NULL);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}

	if (path)
	{
		path_cpy = strdup(path);

		command_len = strlen(command);

		path_token = strtok(path_cpy, ":");

		while (path_token != NULL)
		{
			directory_len = strlen(path_token);

			file_path = malloc(command_len + directory_len + 2);
			if (file_path == NULL)
			{
				return (NULL);
			}

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);


			if (stat(file_path, &buffer) == 0)
			{
				real_path = realpath(file_path, NULL);
				free(file_path);
				return (real_path);
			}
			else if (errno != ENOENT)
			{
				perror("stat");
				free(file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}

		free(path_cpy);

		if (stat(command, &buffer) == 0)
		{
			return (command);
		}

		return (NULL);
	}

	return (NULL);

}
