#include "holberton.h"

/**
 * check_env - Checks if the typed variable is an environment variable.
 * @h: Head of the linked list to store variable information.
 * @in: Input string containing the variable.
 * @data: Data structure containing relevant information.
 *
 * This function checks if the typed variable in the input string is an environment
 * variable. It searches for the variable in the data->_environ array and extracts
 * its value. If found, it adds a new node to the linked list with the variable name
 * and its corresponding value.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Check if the typed variable is $$ or $?
 * @h: Head of the linked list to store variable information.
 * @in: Input string containing the variable.
 * @st: Last status of the Shell.
 * @data: Data structure containing relevant information.
 * Return: The number of characters processed.
 *
 * This function checks if the typed variable in the input string is either $$ (current
 * process ID) or $? (last exit status). If found, it adds a new node to the linked list
 * with the corresponding value. It also handles cases where the variable is followed by
 * specific characters, such as newline, space, tab, or semicolon, by adding a node with
 * NULL value. For any other case, it calls check_env to determine if it's an environment
 * variable.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - Replaces variables in the input string.
 * @head: Head of the linked list containing variable information.
 * @input: Input string to be replaced.
 * @new_input: New input string with variables replaced.
 * @nlen: New length of the input string.
 * Return: The replaced input string.
 *
 * This function replaces variables in the input string with their corresponding
 * values. It iterates through each character of the input string and checks if
 * it corresponds to a variable. If it does, it replaces the variable with its
 * value in the new input string. If the variable doesn't have a value, it is
 * skipped. The replaced input string is returned.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - Replaces variables in the input string.
 * @input: Input string to be replaced.
 * @datash: Data structure containing relevant information.
 * Return: The replaced input string.
 *
 * This function replaces variables in the input string with their corresponding
 * values. It calls check_vars to identify and process variables in the input string.
 * Then, it calculates the new length of the input string after variable replacement.
 * It allocates memory for the new input string and calls replaced_input to perform
 * the actual replacement. The original input string is freed along with the variable
 * linked list. The replaced input string is returned.
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}

