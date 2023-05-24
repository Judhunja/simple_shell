#include "holberton.h"

/**
 * get_sigint - Handle the Ctrl+C signal in the prompt
 * @sig: Signal number received
 *
 * This function is a signal handler for the Ctrl+C signal (SIGINT).
 * It is called when the user presses Ctrl+C in the prompt.
 * The function writes a newline and a custom prompt "^-^ " to the standard output.
 */
void get_sigint(int sig)
{
	(void)sig; /* Unused parameter */
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

