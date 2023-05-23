#include "holberton.h"

/**
 * aux_help - Help information for the builtin help.
 *            Displays information about builtin commands.
 * Return: no return
 */
void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
}

/**
 * aux_help_alias - Help information for the builtin alias.
 *                  Defines or displays aliases.
 * Return: no return
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
}

/**
 * aux_help_cd - Help information for the builtin cd.
 *               Changes the shell working directory.
 * Return: no return
 */
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help)); // Write help information to STDOUT
}

