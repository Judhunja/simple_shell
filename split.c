/**
 * swap_char - Swaps '|' and '&' characters for non-printed characters.
 * @input: Input string.
 * @bool: Type of swap (0 for replacement, 1 for restoration).
 * Return: Swapped string.
 *
 * This function swaps the '|' character with a non-printed character (16)
 * if it is not followed by another '|'. Similarly, it swaps the '&' character
 * with a non-printed character (12) if it is not followed by another '&'.
 * The 'bool' parameter determines whether the swap is for replacement (0)
 * or restoration (1). If 'bool' is 0, the function iterates through the input
 * string and performs the swap. If 'bool' is 1, the function restores the
 * original characters by replacing the non-printed characters with '|' or '&'.
 * The modified input string is returned.
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		i = 0;
		while (input[i])
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (input[i])
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
			i++;
		}
	}
	return (input);
}

/**
 * add_nodes - Adds separators and command lines to the respective lists.
 * @head_s: Head of the separator list.
 * @head_l: Head of the command lines list.
 * @input: Input string.
 * Return: No return.
 *
 * This function adds separators and command lines to their respective lists.
 * It first calls the swap_char function to replace '|' and '&' characters
 * with non-printed characters for easier processing. Then, it iterates through
 * the input string and adds separators to the separator list based on the
 * presence of ';' or '|', '&'. It also extracts command lines using _strtok
 * function and adds them to the command lines list. The function continues
 * until all command lines are processed and added to the list.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	i = 0;
	while (input[i])
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
		i++;
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_next - Moves to the next command line stored.
 * @list_s: Separator list.
 * @list_l: Command line list.
 * @datash: Data structure.
 * Return: No return.
 *
 * This function moves to the next command line stored in the command line list.
 * It takes the separator list, command line list, and data structure as inputs.
 * The function iterates through the separator list and command line list until
 * it finds the next appropriate command line based on the status of the previous
 * command execution. If the status is 0, it looks for '&' or ';' separators. If
 * the status is non-zero, it looks for '|' or ';' separators. Once the next
 * command line is found, the function updates the list pointers accordingly.
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits command lines according to separators (;, |, &) and executes them.
 * @datash: Data structure.
 * @input: Input string.
 * Return: 0 to exit, 1 to continue.
 *
 * This function splits the command lines based on separators (;, |, &) and executes them.
 * It takes the data structure and input string as parameters. The function first creates
 * and initializes lists for separators and command lines. It then calls the add_nodes
 * function to populate the lists based on the input string. The function iterates through
 * the command lines list, executes each command line using exec_line, and updates the
 * data structure accordingly. After executing each command line, it moves to the next
 * appropriate command line using the go_next function. The loop continues until all
 * command lines are processed. Finally, the function frees the memory allocated for
 * the separator and command line lists.
 */
int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - Tokenizes the input string.
 * @input: Input string.
 * Return: String split into tokens.
 *
 * This function tokenizes the input string using the _strtok function.
 * It takes the input string as a parameter and returns an array of strings
 * representing the tokens. The tokens are split based on the delimiter characters
 * specified by the TOK_DELIM macro. The function dynamically allocates memory
 * for the tokens and adjusts the token array size as needed using _reallocdp.
 * If there is a memory allocation error, an error message is printed, and
 * the program exits with a failure status.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

