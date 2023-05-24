#include "holberton.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @datash: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd)); /* Get the current working directory */
	cp_pwd = _strdup(pwd); /* Create a copy of the current working directory */

	set_env("OLDPWD", cp_pwd, datash); /* Set the environment variable OLDPWD */

	dir = datash->args[1]; /* Get the directory to navigate to */
	if (_strcmp(".", dir) == 0) /* If the directory is ".", no change is needed */
	{
		set_env("PWD", cp_pwd, datash); /* Set the environment variable PWD */
		free(cp_pwd); /* Free the memory allocated for the copied current working directory */
		return;
	}
	if (_strcmp("/", cp_pwd) == 0) /* If the current directory is the root directory, no change is needed */
	{
		free(cp_pwd); /* Free the memory allocated for the copied current working directory */
		return;
	}

	cp_strtok_pwd = cp_pwd; /* Create a copy of the current working directory for tokenization */
	rev_string(cp_strtok_pwd); /* Reverse the copy of the current working directory */

	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/"); /* Tokenize the copy of the current working directory */
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0"); /* Get the last token of the reversed directory path */

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd); /* Reverse the last token to obtain the desired directory name */
	}

	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd); /* Change the current directory to the desired directory */
		set_env("PWD", cp_strtok_pwd, datash); /* Set the environment variable PWD */
	}
	else
	{
		chdir("/"); /* Change the current directory to the root directory */
		set_env("PWD", "/", datash); /* Set the environment variable PWD */
	}

	datash->status = 0; /* Set the status to indicate successful execution */
	free(cp_pwd); /* Free the memory allocated for the copied current working directory */
}

/**
 * cd_to - changes to a directory given by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd)); /* Get the current working directory */

	dir = datash->args[1]; /* Get the directory to navigate to */
	if (chdir(dir) == -1) /* Change the current directory to the desired directory */
	{
		get_error(datash, 2); /* Display an error message if the directory change fails */
		return;
	}

	cp_pwd = _strdup(pwd); /* Create a copy of the current working directory */
	set_env("OLDPWD", cp_pwd, datash); /* Set the environment variable OLDPWD */

	cp_dir = _strdup(dir); /* Create a copy of the desired directory */
	set_env("PWD", cp_dir, datash); /* Set the environment variable PWD */

	free(cp_pwd); /* Free the memory allocated for the copied current working directory */
	free(cp_dir); /* Free the memory allocated for the copied desired directory */

	datash->status = 0; /* Set the status to indicate successful execution */

	chdir(dir); /* Change the current directory to the desired directory */
}

/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd)); /* Get the current working directory */
	cp_pwd = _strdup(pwd); /* Create a copy of the current working directory */

	p_oldpwd = _getenv("OLDPWD", datash->_environ); /* Get the value of the environment variable OLDPWD */

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd; /* If OLDPWD is not set, use the current working directory as the previous directory */
	else
		cp_oldpwd = _strdup(p_oldpwd); /* Create a copy of the previous directory */

	set_env("OLDPWD", cp_pwd, datash); /* Set the environment variable OLDPWD */

	if (chdir(cp_oldpwd) == -1) /* Change the current directory to the previous directory */
		set_env("PWD", cp_pwd, datash); /* If the directory change fails, set PWD to the current working directory */
	else
		set_env("PWD", cp_oldpwd, datash); /* Set the environment variable PWD to the previous directory */

	p_pwd = _getenv("PWD", datash->_environ); /* Get the value of the environment variable PWD */

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd)); /* Write the current directory to the standard output */
	write(STDOUT_FILENO, "\n", 1); /* Write a newline character */

	free(cp_pwd); /* Free the memory allocated for the copied current working directory */
	if (p_oldpwd)
		free(cp_oldpwd); /* Free the memory allocated for the copied previous directory */

	datash->status = 0; /* Set the status to indicate successful execution */

	chdir(p_pwd); /* Change the current directory to the value of PWD */
}

/**
 * cd_to_home - changes to the home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd)); /* Get the current working directory */
	p_pwd = _strdup(pwd); /* Create a copy of the current working directory */

	home = _getenv("HOME", datash->_environ); /* Get the value of the environment variable HOME */

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash); /* If HOME is not set, set OLDPWD to the current working directory */
		free(p_pwd); /* Free the memory allocated for the copied current working directory */
		return;
	}

	if (chdir(home) == -1) /* Change the current directory to the home directory */
	{
		get_error(datash, 2); /* Display an error message if the directory change fails */
		free(p_pwd); /* Free the memory allocated for the copied current working directory */
		return;
	}

	set_env("OLDPWD", p_pwd, datash); /* Set the environment variable OLDPWD */
	set_env("PWD", home, datash); /* Set the environment variable PWD to the home directory */

	free(p_pwd); /* Free the memory allocated for the copied current working directory */
	datash->status = 0; /* Set the status to indicate successful execution */
}

