#include "holberton.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 *
 * This function frees the data structure pointed to by datash.
 */
void free_data(data_shell *datash)
{
	unsigned int z;

	/* Iterate over the environment variables and free them. */
	for (z = 0; datash->_environ[z]; z++) {
		free(datash->_environ[z]);
	}

	/* Free the environment variable array and the process ID. */
	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 *
 * This function initializes the data structure pointed to by datash.
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int z;

	/* Set the argument vector, input, arguments, status, and counter members of datash. */
	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	/* Iterate over the environment variables and count them. */
	while (environ[z]) {
		z++;
	}

	/* Allocate memory for an array of environment variables and copy the environment variables to the array. */
	datash->_environ = malloc(sizeof(char *) * (z + 1));

	for (z = 0; environ[z]; z++) {
		datash->_environ[z] = _strdup(environ[z]);
	}

	/* Set the last element of the environment variable array to NULL. */
	datash->_environ[z] = NULL;

	/* Get the process ID and store it in the pid member of datash. */
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * This function is the entry point for the program.
 *
 * Returns: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	/* Set the signal handler for SIGINT. */
	signal(SIGINT, get_sigint);

	/* Initialize the data structure. */
	set_data(&datash, av);

	/* Run the shell loop. */
	shell_loop(&datash);

	/* Free the data structure. */
	free_data(&datash);

	/* Return the status of the shell loop. */
	return (datash.status);
}

