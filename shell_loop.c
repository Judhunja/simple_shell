#include "holberton.h"
/**
 * shell_loop - main shell loop
 * @exit_status_no: exit status number returned by the function
 */
void shell_loop(int *exit_status_no)
{
	char prompt[MAX_INPUT_LENGTH];
	char *args[MAX_INPUT_LENGTH / 2 + 1];
	int display_prompt = isatty(STDIN_FILENO);
	int quotes;
	char *commnt_start, previous_char, *k;

	while (1)
	{
		if (display_prompt)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (fgets(prompt, MAX_INPUT_LENGTH, stdin) == NULL)
			break;
		quotes = 0;
		previous_char = '\0';
		commnt_start = NULL;
		for (k = prompt; *k != '\0'; ++k)
		{
			if (*k == '"' && previous_char != '\\')
				quotes = !quotes;
			else if (*k == '#' && !quotes && previous_char != '\\')
			{
				commnt_start = k;
				break;
			}
			previous_char = *k;
		}
		if (commnt_start != NULL)
			*commnt_start = '\0';
		prompt[strcspn(prompt, "\n")] = '\0';
		input_parser(prompt, args);
		if (args[0] == NULL)
			continue;
		if (_strcmp(args[0], "exit") == 0)
			return;
		if (_strcmp(args[0], "env") == 0)
		{
			print_env();
			continue;
		}
		*exit_status_no = exec_command(args);
	}
}

