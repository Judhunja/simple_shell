#include "holberton.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;  // Unsigned integer to store the exit status
	int is_digit;          // Flag indicating if the argument is a digit
	int str_len;           // Length of the argument string
	int big_number;        // Flag indicating if the number is too large

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);       // Convert the argument to an unsigned integer
		is_digit = _isdigit(datash->args[1]);   // Check if the argument is a digit
		str_len = _strlen(datash->args[1]);     // Get the length of the argument string
		big_number = ustatus > (unsigned int)INT_MAX;   // Check if the number is larger than INT_MAX

		// Check if the argument is not a digit or the string length is greater than 10
		// or the number is too large (greater than INT_MAX)
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);    // Display an error message
			datash->status = 2;      // Set the status to 2 (error)
			return (1);              // Return 1 to indicate error
		}

		datash->status = (ustatus % 256);   // Set the status to the exit status modulo 256
	}

	return (0);   // Return 0 to indicate success
}

