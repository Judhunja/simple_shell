/**
 * without_comment - Deletes comments from the input string.
 * @in: Input string.
 * Return: Input string without comments.
 *
 * This function removes comments from the input string. It iterates through
 * each character of the input string and checks if it corresponds to a '#'
 * character. If it does, it checks if the '#' is at the beginning of the
 * string or if the character before '#' is a space, tab, or semicolon. If
 * either condition is met, it marks the position of the '#' character as the
 * end of the input string and truncates the input string there. The modified
 * input string without comments is returned.
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Main loop of the shell.
 * @datash: Data structure containing relevant information.
 * Return: No return.
 *
 * This function represents the main loop of the shell. It continuously prompts
 * for user input, reads the input string, and performs various operations on it.
 * It calls the read_line function to read the input string, then uses without_comment
 * to remove any comments from the input. If the input is valid, it checks for
 * syntax errors using the check_syntax_error function. If there are no syntax errors,
 * it replaces variables using rep_var and splits the commands using split_commands.
 * The loop continues until an end-of-file condition is encountered, indicated by i_eof
 * being -1. The function updates the counter and frees the input string at each iteration.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

