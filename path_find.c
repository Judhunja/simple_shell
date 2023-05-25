/**
* path_find - finds command's full path in directories listed in PATH.
* return: full path if command is found and is executable, else returns NULL.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PATH_LENGTH 4096

char *path_find(char *command)
{
	char *path = getenv("PATH");
	char *direct = strtok(path, ":");
	char *path_buff = malloc(MAX_PATH_LENGTH * sizeof(char));
	int path_length;
	char *full_path;
	struct stat buff;

	while (direct != NULL)
	{
	path_length = strlen(direct) + strlen(command) + 2;
	full_path = malloc(path_length * sizeof(char));
	sprintf(full_path, "%s/%s", direct, command);

	if (stat(full_path, &buff) == 0 && S_ISREG(buff.st_mode)
			&& (buff.st_mode & S_IXUSR))
	{
	free(path_buff);
	return (full_path);
	}

	free(full_path);
	direct = strtok(NULL, ":");
	}

	free(path_buff);
	return (NULL);
}
