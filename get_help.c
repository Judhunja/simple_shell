#include "holberton.h"

/**
 * get_help - function that retrieves help messages according to the builtin
 * @datash: data structure (args and input)
 * Return: Return 0
 */
int get_help(data_shell *datash)
{
	if (datash->args[1] == 0)
		aux_help_general();                          // Display general help message
	else if (_strcmp(datash->args[1], "setenv") == 0)
		aux_help_setenv();                           // Display help message for setenv builtin
	else if (_strcmp(datash->args[1], "env") == 0)
		aux_help_env();                              // Display help message for env builtin
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		aux_help_unsetenv();                         // Display help message for unsetenv builtin
	else if (_strcmp(datash->args[1], "help") == 0)
		aux_help();                                  // Display help message for help builtin
	else if (_strcmp(datash->args[1], "exit") == 0)
		aux_help_exit();                             // Display help message for exit builtin
	else if (_strcmp(datash->args[1], "cd") == 0)
		aux_help_cd();                               // Display help message for cd builtin
	else if (_strcmp(datash->args[1], "alias") == 0)
		aux_help_alias();                            // Display help message for alias builtin
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));             // Write the command name to stderr

	datash->status = 0;                              // Set the shell status to 0 (success)
	return (1);                                      // Return 1 indicating success
}

