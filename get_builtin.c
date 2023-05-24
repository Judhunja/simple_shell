#include "holberton.h"

/**
 * get_builtin - builtin that pairs the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },              // Builtin command: env
		{ "exit", exit_shell },       // Builtin command: exit
		{ "setenv", _setenv },        // Builtin command: setenv
		{ "unsetenv", _unsetenv },    // Builtin command: unsetenv
		{ "cd", cd_shell },           // Builtin command: cd
		{ "help", get_help },         // Builtin command: help
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;                   // Exit the loop if the command is found
	}

	return (builtin[i].f);           // Return the function pointer of the builtin command
}

