#include "holberton.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int index = 0, y, k; /* Initialize index, y, and k */
	char *str, temp;

	while (index >= 0)
	{
		if (s[index] == '\0') /* Find the end of the string */
			break;
		index++;
	}
	str = s; /* Assign the pointer to the start of the string to str */

	for (y = 0; y < (index - 1); y++) /* Iterate over the string */
	{
		for (k = y + 1; k > 0; k--) /* Reverse the string */
		{
			temp = *(str + k); /* Swap characters */
			*(str + k) = *(str + (k - 1));
			*(str + (k - 1)) = temp;
		}
	}
}

