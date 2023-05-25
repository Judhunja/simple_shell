#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 256

extern char **environ;

void shell_exit(void);
void input_parser(char *input, char **args);
ssize_t imp_getline(char **lineptr, size_t *k, FILE *strm);
int _strcmp(char *str1, char *str2);
char *str_trim(char *str);
char *find_path(char *command);
void handle_error(char *command_name, int status);
void print_env(void);
int exec_command(char **args);
void shell_loop(int *exit_status);
#endif /* SHELL_H */
