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

	path = getenv("PATH");

	if (path)
	{
		/* Duplicate the path string for srttok use */
		path_cpy = strdup(path);

		/* Getting the length of the passed command */
		command_len = strlen(command);

		/* Break down the path variable and get all the directories available*/
		path_token = strtok(path_cpy, ":");

		while (path_token != NULL)
		{
			/* Get the length of the directory*/
			directory_len = strlen(path_token);

			/* allocating memory for storing the command name together with the directory name */
			file_path = malloc(command_len + directory_len + 2);

			/* to build the path for the command, copy the directory path and concatenate the command to it */
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			/* test if this file path actually exists and return it if it does, otherwise try the next directory */
			if (stat(file_path, &buffer) == 0)
			{
				/* return value of 0 means success implying that the file_path is valid*/
                /* free up allocated memory before returning the file_path */
				free(path_cpy);
				return (file_path);
			}
			else
			{
				 /* free up the file_path memory so we can check for another path*/
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}

		/* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */
		free(path_cpy);

		/* before we exit without luck, let's see if the command itself is a file_path that exists */
		if (stat(command, &buffer) == 0)
		{
			return (command);
		}

		return (NULL);
	}

	return (NULL);

}
