#include "holberton.h"

/**
 * get_len - Get the length of a number.
 * @n: Integer number.
 * Return: Length of the number.
 */
int get_len(int n)
{
	unsigned int n1;
	int len = 1;

	if (n < 0)
	{
		len++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}

/**
 * aux_itoa - Convert an integer to a string.
 * @n: Integer number.
 * Return: String representation of the number.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int len = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == NULL)
		return (NULL);

	*(buffer + len) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	len--;

	do {
		*(buffer + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	} while (n1 > 0);

	return (buffer);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: Input string.
 * Return: The converted integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, num_size = 0, converted = 0, sign = 1, multiplier = 1, y;

	while (*(s + count) != '\0')
	{
		if (num_size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if (*(s + count) >= '0' && *(s + count) <= '9')
		{
			if (num_size > 0)
				multiplier *= 10;
			num_size++;
		}
		count++;
	}

	for (y = count - num_size; y < count; y++)
	{
		converted = converted + ((*(s + y) - '0') * multiplier);
		multiplier /= 10;
	}

	return (converted * sign);
}

