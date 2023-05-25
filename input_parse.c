#include "holberton.h"

/**
 * input_parser - splits given input into multiple words
 * @input: given input
 * @args: stores parsed input
 *
 * Return: nothing
 */

void input_parser(char *input, char **args)
{
	char *ar;
	int j = 0;
	int is_space = 1;

	for (j = 0; input[j]; j++)
	{
		if (!isspace(input[j]))
		{
			is_space = 0;
			break;
		}
	}
	if (is_space)
	{
		args[0] = NULL;
		return;
	}
	j = 0;
	ar = strtok(input, " ");
	while (ar)
	{
		args[j++] = ar;
		ar = strtok(NULL, " ");
	}
	args[j] = NULL;
	if (_strcmp(args[0], "exit") == 0)
		exit(0);
}
