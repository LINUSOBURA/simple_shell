#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

/*Tokenization*/
char **tokenize_input(char *input);

/*Custom strtok*/
char *custom_strtok(char *str, const char *delimiters);

/*Execute command entered*/
void free_tokens(char **tokens);
void execute_command(char **tokens, const char *shell_name);

void exec(char **argv);
void *command_location(char *command);
/*Print enviroment*/
extern char **environ;
void print_environment(void);

#endif
