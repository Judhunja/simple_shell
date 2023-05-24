#include "holberton.h"

/**
 * bring_line - Assigns the line variable for get_line
 * @lineptr: Buffer that stores the input string
 * @n: Size of line
 * @buffer: String that is being assigned to lineptr
 * @j: Size of buffer
 *
 * This function checks the conditions to determine whether to assign the buffer
 * to lineptr or copy the contents of the buffer to lineptr.
 * If lineptr is NULL, it assigns the buffer to lineptr and updates the size (n) accordingly.
 * If the size (n) is less than j, it assigns the buffer to lineptr and updates the size (n).
 * Otherwise, it copies the contents of the buffer to lineptr, frees the buffer, and returns.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Read input from stream
 * @lineptr: Buffer that stores the input
 * @n: Size of lineptr
 * @stream: Stream to read from
 * Return: The number of bytes
 *
 * This function reads input from the specified stream and stores it in the lineptr buffer.
 * It reads characters one by one until a newline character is encountered.
 * The input is dynamically allocated and resized as needed.
 * The function returns the number of bytes read.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	/* If input is already in progress, return -1 */
	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);

	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

