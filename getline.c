#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
/**
* imp_getline - reads a line from the given input stream
* @lineptr: pointer to pointer to character array that stores input line
* @k: pointer to size_t variable that holds size of the character array
* @strm: a pointer to the stdin stream
* Return: number of characters read including the terminating null operand
*/

ssize_t imp_getline(char **lineptr, size_t *k, FILE *strm)
{
	static char buff[BUFFER_SIZE];
	static size_t buff_pos;
	size_t line_pos = 0;
	char j;

	buff_pos = 0;

	if (*lineptr == NULL)
		*lineptr = malloc(*k);
	if (*lineptr == NULL)
		return (-1);
	while (1)
	{
		if (buff_pos == 0)
		{
			size_t bytes_read = fread(buff, 1, BUFFER_SIZE, strm);

			if (bytes_read == 0)
			return (-1);
		}
		j = buff[buff_pos++];

		if (j == '\n' || buff_pos == BUFFER_SIZE)
		{
			(*lineptr)[line_pos++] = '\0';
			*k = line_pos;
			buff_pos = 0;
			return (line_pos);
		}
		(*lineptr)[line_pos++] = j;

		if (line_pos >= *k)
		{
			*k += BUFFER_SIZE;
			*lineptr = realloc(*lineptr, *k);

			if (*lineptr == NULL)
			return (-1);
		}
	}
}
