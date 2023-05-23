#include "holberton.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(data_shell *datash)
{
	int error_length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datash->counter); // Convert counter to string
	msg = ": Unable to add/remove from environment\n"; // Error message
	error_length = _strlen(datash->av[0]) + _strlen(ver_str);
	error_length += _strlen(datash->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (error_length + 1));

	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->av[0]); // Copy program name to error
	_strcat(error, ": ");
	_strcat(error, ver_str); // Append counter string
	_strcat(error, ": ");
	_strcat(error, datash->args[0]); // Append command name
	_strcat(error, msg); // Append error message
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(data_shell *datash)
{
	int error_length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datash->counter); // Convert counter to string
	error_length = _strlen(datash->av[0]) + _strlen(ver_str);
	error_length += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (error_length + 1));

	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datash->av[0]); // Copy program name to error
	_strcat(error, ": ");
	_strcat(error, ver_str); // Append counter string
	_strcat(error, ": ");
	_strcat(error, datash->args[0]); // Append command name
	_strcat(error, ": Permission denied\n"); // Append error message
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
