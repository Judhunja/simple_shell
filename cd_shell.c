#include "holberton.h"

/**
 * cd_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1]; /* Get the directory argument from the command */

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir); /* Check if the argument is "$HOME" */
		ishome2 = _strcmp("~", dir); /* Check if the argument is "~" */
		isddash = _strcmp("--", dir); /* Check if the argument is "--" */
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datash); /* If the argument is NULL or matches "$HOME", "~", or "--", change to the home directory */
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash); /* If the argument is "-", change to the previous directory */
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash); /* If the argument is "." or "..", change to the current or parent directory respectively */
		return (1);
	}

	cd_to(datash); /* Otherwise, change to the specified directory */

	return (1);
}

