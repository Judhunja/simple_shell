#include "holberton.h"

/**
 * _strdup - duplicates a string in the heap memory.
 * @s: pointer to the input string.
 *
 * Return: duplicated string, or NULL on failure.
 */
char *_strdup(const char *s)
{
	char *new;
	size_t length;

	length = _strlen(s);
	new = malloc(sizeof(char) * (length + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, length + 1);
	return (new);
}

/**
 * _strlen - Returns the length of a string.
 * @s: pointer to the input string.
 *
 * Return: the length of the string.
 */
int _strlen(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * cmp_chars - compare characters of strings.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if characters are equal, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by a delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: the next token, or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /* Store first address */
		i = _strlen(str);
		str_end = &str[i]; /* Store last address */
	}
	str_start = splitted;
	if (str_start == str_end) /* Reached the end */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking loop and finding the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* Replacing delimiter with null char */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - checks if a string consists only of digits.
 * @s: pointer to the input string.
 *
 * Return: 1 if the string consists only of digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57) /* ASCII values of digits */
			return (0);
	}
	return (1);
}

