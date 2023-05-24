#include "holberton.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	// If there are no arguments, return success
	if (datash->args[0] == NULL)
		return (1);

	// Check if the command is a builtin
	builtin = get_builtin(datash->args[0]);

	// If the command is a builtin, execute it
	if (builtin != NULL)
		return (builtin(datash));

	// If the command is not a builtin, execute it as an external command
	return (cmd_exec(datash));
}

