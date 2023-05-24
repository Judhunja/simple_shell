#include "holberton.h"

/**
 * get_error - calls the error according to the builtin, syntax, or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datash);                // Get error message for environment-related error
		break;
	case 126:
		error = error_path_126(datash);           // Get error message for command not executable error
		break;
	case 127:
		error = error_not_found(datash);          // Get error message for command not found error
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);     // Get error message for exit command error
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);         // Get error message for cd command error
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));  // Write the error message to stderr
		free(error);                                  // Free the allocated error message memory
	}

	datash->status = eval;                          // Set the status of the shell to the error value
	return (eval);                                  // Return the error value
}

