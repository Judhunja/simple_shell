#include "holberton.h"

/**
 * is_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	// Check if the current character is a ':'
	if (path[*i] == ':')
		return (1);

	// Iterate through the path until a ':' or null character is found
	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	// Increment the index if a non-null character is found after ':'
	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	// Get the value of the PATH environment variable
	path = _getenv("PATH", _environ);

	if (path)
	{
		// Create a duplicate of the PATH value
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);

		// Tokenize the PATH value using ':' as the delimiter
		token_path = _strtok(ptr_path, ":");

		i = 0;
		while (token_path != NULL)
		{
			// Check if the current token is the current directory
			if (is_cdir(path, &i))
				// Check if the command exists in the current directory
				if (stat(cmd, &st) == 0)
					return (cmd);

			// Get the length of the current token
			len_dir = _strlen(token_path);

			// Allocate memory for the directory path
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");

			// Check if the command exists in the current directory
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}

			free(dir);
			token_path = _strtok(NULL, ":");
		}

		free(ptr_path);

		// Check if the command exists in the current directory
		if (stat(cmd, &st) == 0)
			return (cmd);

		return (NULL);
	}

	// Check if the command is an absolute path
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);

	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datash: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		// Check for relative path indicators
		if (input[i] == '.')
		{
			// Check for parent directory indicator
			if (input[i + 1] == '.')
				return (0);

			// Check for current directory indicator
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			// Check for parent directory indicator after '/'
			if (input[i + 1] == '.')
				continue;

			// Increment index to skip '/'
			i++;
			break;
		}
		else
			break;
	}

	// Check if the command is an executable
	if (i == 0)
		return (0);

	// Check if the command exists in the current directory
	if (stat(input + i, &st) == 0)
	{
		return (i);
	}

	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data_shell *datash)
{
	// Check if the directory path is NULL
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	// Check if the command path is different from the directory path
	if (_strcmp(datash->args[0], dir) != 0)
	{
		// Check if the user has execute permissions for the directory
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		// Check if the user has execute permissions for the command
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	// Check if the command is executable
	exec = is_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		// Find the location of the command
		dir = _which(datash->args[0], datash->_environ);
		// Check for errors related to command access
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	// Fork a child process
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		// Wait for the child process to finish
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}

