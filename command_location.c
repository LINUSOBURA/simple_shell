#include "shell.h"
/**
 * command_location - fuction to get the path of entered command
 * @command: the command whose PATH is fetched
 * Return: path to the command
*/
void *command_location(char *command)
{
	char *path, *path_cpy, *path_token;
	struct stat buffer;

	    if (command == NULL)
    {
        return NULL;
    }

    /*Check if the command is an absolute path*/
    if (command[0] == '/' || command[0] == '.')
    {
        /*If it is, check if the file exists*/
        if (stat(command, &buffer) == 0)
        {
            return realpath(command, NULL);
        }
        else
        {
            return NULL;
        }
    }

    path = getenv("PATH");
    if (path == NULL)
    {
        return NULL;
    }

    path_cpy = strdup(path);
    path_token = strtok(path_cpy, ":");

    while (path_token != NULL)
    {
        char *file_path = malloc(strlen(path_token) + strlen(command) + 2);
        if (file_path == NULL)
        {
            free(path_cpy);
            return NULL;
        }

        strcpy(file_path, path_token);
		if (strlen(path_token) > 0)
        	strcat(file_path, "/");
        strcat(file_path, command);

        if (stat(file_path, &buffer) == 0)
        {
            free(path_cpy);
            return realpath(file_path, NULL);
        }

        free(file_path);
        path_token = strtok(NULL, ":");
    }

    free(path_cpy);

    /*If the command is not found in PATH, return NULL*/
    return NULL;
}