#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include "main.h"
#include <string.h>
#include <errno.h>
/**
 * check_command- this function takes care of checking
 * if the command is in the PATH var or not
 * @command: the command passed
 * Return: the path to the executable if found, NULL if not
 */
char *check_command(char *command)
{
	char *path_copy;
	char *path = getenv("PATH");
	char *dir = NULL;
	char *command_path = NULL;
	int command_found = 0;
	size_t len = 0;

	if (path == NULL)
	{
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return (NULL);
	}
	path_copy = strdup(path);

	if (path_copy == NULL)
		return (NULL);
	for (dir = strtok(path_copy, ":"); dir != NULL; dir = strtok(NULL, ":"))
	{
		len = strlen(dir) + strlen(command) + 2;
		command_path = malloc(len);
		if (command_path == NULL)
		{
			break;
		}
		snprintf(command_path, len, "%s/%s", dir, command);
		if (access(command_path, X_OK) == 0)
		{
			command_found = 1;
			break;
		}
		free(command_path);
	}
	free(path_copy);
	if (!command_found)
	{
		return (NULL);
	}
	return (command_path);
}

/**
 *EXECUTE- is a function that executes the command
 * parsed in the list struct
 * @list: the list struct
 * Return: 0 SUCCESS, -1 FAILURE, exit failure if fork failed
 */
int EXECUTE(struct TOKEN_LIST *list)
{
	pid_t child_pid, terminated_child_pid;
	int status;

	child_pid = 0, terminated_child_pid = 0;
	status = 0;
	child_pid = fork();
	if (child_pid == -1)
	{
		dprintf(2, "%s\n", strerror(errno));/*err print*/
		token_list_cleaner(list);
		exit(-1);
	}
	if (child_pid == 0)
	{
		if (execve(list->token_list[0], list->token_list, NULL) == -1)
		{
			dprintf(2, "%s\n", strerror(errno));/*err print*/
			exit(EXIT_FAILURE);
			return (-1);
		}
		return (0);
	}
	else
	{
		terminated_child_pid = wait(&status);
		if (terminated_child_pid == -1)
		{
			token_list_cleaner(list);
			dprintf(2, "%s\n", strerror(errno));/*err print*/
			exit(-1);
		}

		if (WIFEXITED(status))
		{
			if (terminated_child_pid && WEXITSTATUS(status))
				WEXITSTATUS(status);
		}
	}
	return (0);
}

/**
 * DIRECT_EXECUTE- is the same as EXECUTE with a minor deff
 * this function takes the argv passed from the user directlly
 * to the program
 * @argv: arg list
 * @path: the path to the executble
 * Return: 0 allways on success, exit faikure if fork didnt work
 */
int DIRECT_EXECUTE(char **argv, char *path)
{
	pid_t child_pid;
	int status;


	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		free(path);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(path, argv + 1, NULL) == -1)
		{
			free(path);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		pid_t terminated_child_pid = wait(&status);

		if (terminated_child_pid == -1)
		{
			perror(argv[0]);
			free(path);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			WEXITSTATUS(status);
		}
	}
	free(path);
	return (0);
}
/**
 *DIRECT_EXECUTE2-try and execute the argv[0]
 * @argv: the listof passed args
 * Return: 0 if success , exit otherwise
 */
int DIRECT_EXECUTE2(char **argv)
{
	pid_t child_pid;
	int status;


	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(argv[1], argv + 1, NULL) == -1)
		{
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		pid_t terminated_child_pid = wait(&status);

		if (terminated_child_pid == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			WEXITSTATUS(status);
		}
	}
	return (0);
}

/**
 * NULL_path_handler- if a command is not found in the
 * path , this function will check if the command is a file
 * if the file is accessble , it will try and execute it
 * @list: the list struct
 */
void NULL_path_handler(struct TOKEN_LIST *list)
{
	struct stat buffer;
	int status;
	pid_t child_pid, terminated_child_pid;

	terminated_child_pid = 0;
	status = lstat(list->token_list[0], &buffer);
	if (status == -1)
	{
		dprintf(2, "%s\n", strerror(errno));/*err print*/
		return;
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			token_list_cleaner(list);
			dprintf(2, "%s\n", strerror(errno));/*err print*/
			exit(-1);
		}
		else if (child_pid == 0)
		{
			if (execve(list->token_list[0], list->token_list, NULL) == -1)
				dprintf(2, "%s\n", strerror(errno));/*errp*/
		}
		else
		{
			terminated_child_pid = wait(&status);
			if (terminated_child_pid == -1)
			{
				token_list_cleaner(list);
				dprintf(2, "%s\n", strerror(errno));/*err*/
				exit(-1);
			}
			if (WIFEXITED(status))
				if (terminated_child_pid && WEXITSTATUS(status))
					WEXITSTATUS(status);
		}
	}
}
