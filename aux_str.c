#include "holberton.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer to the destination of the copied string
 * @src: const char pointer to the source string
 * Return: the destination string
 */
char *_strcat(char *dest, const char *src)
{
	int y;
	int k;

	/* Find the end of the destination string */
	for (y = 0; dest[y] != '\0'; y++)
		;

	/* Append the source string to the destination */
	for (k = 0; src[k] != '\0'; k++)
	{
		dest[y] = src[k];
		y++;
	}

	dest[y] = '\0';
	return (dest);
}

/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: char pointer to the destination of the copied string
 * @src: char pointer to the source string
 * Return: the destination string
 */
char *_strcpy(char *dest, char *src)
{
	size_t y;

	/* Copy characters from source to destination */
	for (y = 0; src[y] != '\0'; y++)
	{
		dest[y] = src[y];
	}
	dest[y] = '\0';

	return (dest);
}

/**
 * _strcmp - Function that compares two strings.
 * @s1: string compared
 * @s2: string compared
 * Return: 0 if strings are equal, 1 if s1 > s2, -1 if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	int y;

	/* Compare corresponding characters in s1 and s2 */
	for (y = 0; s1[y] == s2[y] && s1[y]; y++)
		;

	/* Return comparison result */
	if (s1[y] > s2[y])
		return (1);
	if (s1[y] < s2[y])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a character in a string
 * @s: string
 * @c: character
 * Return: a pointer to the first occurrence of the character c, or NULL
 */
char *_strchr(char *s, char c)
{
	unsigned int y = 0;

	/* Search for character c in string s */
	while (*(s + y) != '\0')
	{
		if (*(s + y) == c)
			return (s + y);
		y++;
	}

	if (*(s + y) == c)
		return (s + y);

	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: initial segment
 * @accept: accepted bytes
 * Return: the number of accepted bytes
 */
int _strspn(char *s, char *accept)
{
	int y = 0;
	int k;
	int bool;

	/* Check for accepted bytes in the initial segment of s */
	while (*(s + y) != '\0')
	{
		bool = 1;
		for (k = 0; *(accept + k) != '\0'; k++)
		{
			if (*(s + y) == *(accept + k))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
		y++;
	}

	return (y);
}

