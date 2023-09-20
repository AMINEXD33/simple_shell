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
 * built_in_mapper- this function maps a built in command
 * passed by the user to its respective function
 * @command: the command passed
 * @list: the struct list
 * Return:0 always
 */
int built_in_mapper(char *command, struct TOKEN_LIST *list)
{
	int count;
	struct built_in_command_functions built_in_commands[] = {
		{"exit", exit_shell},
	};
	count = 0;
	while (count < 1)
	{
		if (str_eq_to(built_in_commands[count].command_name, command) == 0)
		{
			built_in_commands[count].func(list);
		}
		count++;
	}
	return (0);
}
/**
 *exit_shell- this function exit the shell
 *@list: struct list
 */
void exit_shell(struct TOKEN_LIST *list)
{
	token_list_cleaner(list);
	exit(0);
}
