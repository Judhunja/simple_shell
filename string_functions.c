#include "holberton.h"
/**
 * str_trim - removes trailing whitespace from end of string
 * @string: string
 *
 * Return: string
 */

char *str_trim(char *string)
{
	char *end_of_string;

	while (isspace((unsigned char)*string))
		string++;
	if (*string == '\0')
		return (string);
	end_of_string = string + strlen(string) - 1;
	while (end_of_string > string && isspace((unsigned char)*end_of_string))
		end_of_string--;
	end_of_string[1] = '\0';
	return (string);
}

/**
 * _strtok - tokenizes a string
 * @str: the string to be tokenized
 * @delimeter: the delimiter to use
 * Return: a pointer to the next token
 */
char *_strtok(char *string, const char *delimeter)
{
	static char *last_char;
	char *token;
	const char *delimeter_pos;

	if (string)
		last_char = string;
	if (!*last_char)
		return (NULL);
	token = last_char;
	while (*last_char)
	{
		delimeter_pos = delimeter;
		while (*delimeter_pos)
		{
			if (*last_char == *delimeter_pos)
			{
				*last_char = '\0';
				last_char++;
				if (*token)
					return (token);
				token = last_char;
				break;
			}
			delimeter_pos++;
		}
		last_char++;
	}
	return (token);
}

/**
  * _strcmp - Compares two strings
  * @str1: The first string
  * @str2: The second string
  *
  * Return: integer
  */
int _strcmp(char *str1, char *str2)
{
	int i = 0, j = 0, k = 0, r = 0, limit;

	while (str1[i])
	{
		i++;
	}
	while (str2[j])
	{
		j++;
	}
	if (i <= j)
	{
		limit = i;
	}
	else
	{
		limit = j;
	}
	while (k <= limit)
	{
		if (str1[k] == str2[k])
		{
			k++;
			continue;
		}
		else
		{
			r = str1[k] - str2[k];
			break;
		}
	}
	return (r);
}
