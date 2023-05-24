#include "holberton.h"

/**
 * read_line - Reads the input string from stdin.
 * @i_eof: Pointer to store the return value of getline function
 *
 * This function reads a line of input from the user using the getline function.
 * It dynamically allocates memory to store the input string.
 *
 * @i_eof is used to store the return value of getline, which indicates
 * the number of characters read. If getline encounters the end-of-file (EOF)
 * or encounters an error, it will set @i_eof to -1.
 *
 * Return: The input string read from the user.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;   /* Stores the input string */
	size_t bufsize = 0;   /* Initial buffer size for getline */

	*i_eof = getline(&input, &bufsize, stdin); /* Read input from stdin */

	return (input);
}

