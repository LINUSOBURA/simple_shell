#include "shell.h"
/**
 * command_location - fuction to get the path of entered command
 * @command: the command whose PATH is fetched
 * Return: path to the command
*/
void *command_location(char *command)
{
	char *path, *path_cpy, *path_token, *file_path;
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

			strncpy(file_path, path_token, directory_len);
			file_path[directory_len] = '\0';
            strncat(file_path, "/", 2);
            strncat(file_path, command, command_len + 1);


			if (stat(file_path, &buffer) == 0)
			{
				free(path_cpy);
				return (realpath(file_path, NULL));
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
