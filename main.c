#include "holberton.h"
/**
 * main -start of the function
 * Return: 0
 */
int main(void)
{
	int exit_status_no = 0;

	shell_loop(&exit_status_no);

	return (0);
}

/**
 * exec_command - fork and execute the given command
 * @args: array of arguments (including the command) to execute
 * Return: exit status no of the executed command
 */

int exec_command(char **args)
{
	char errormsg[] = "Command not found.\n";
	char errormsg_fork[] = "Failed to fork.\n";
	pid_t pid;
	int status;
	int exit_status_no = 0;

	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		if (errno == ENOENT)
		{
			char errormsg_file[] = "./hsh: 0: Can't open ";

			write(STDERR_FILENO, errormsg_file, sizeof(errormsg_file) - 1);
			write(STDERR_FILENO, args[0], strlen(args[0]));
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}
		else
		{
			write(STDERR_FILENO, errormsg, sizeof(errormsg));
			exit(127);
		}
	}
	else if (pid < 0)
	{
		write(STDERR_FILENO, errormsg_fork, sizeof(errormsg_fork));
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			exit_status_no = WEXITSTATUS(status);
	}

	return (exit_status_no);
}
