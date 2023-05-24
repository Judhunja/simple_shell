#include "holberton.h"

/**
 * cmp_env_name - compares env variables names with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	// Compare characters of the environment variable name until '=' is encountered
	for (i = 0; nenv[i] != '='; i++)
	{
		// Check if the characters are not equal
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	// Return the position after the '=' character
	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if found. Otherwise, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	// Initialize ptr_env value
	ptr_env = NULL;
	mov = 0;

	// Compare name with all environment variables in _environ
	for (i = 0; _environ[i]; i++)
	{
		// Call cmp_env_name to compare names
		mov = cmp_env_name(_environ[i], name);

		// If names are equal, assign the pointer to the environment variable
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	// Return the value of the environment variable (after the '=' character)
	return (ptr_env + mov);
}

/**
 * _env - prints the environment variables
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int _env(data_shell *datash)
{
	int i, j;

	// Iterate through each environment variable in _environ
	for (i = 0; datash->_environ[i]; i++)
	{
		// Calculate the length of the environment variable
		for (j = 0; datash->_environ[i][j]; j++)
			;

		// Write the environment variable to stdout
		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	// Set the status to 0 (success)
	datash->status = 0;

	return (1);
}

