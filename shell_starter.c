#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
/**
 *make_list- a function that initialize the list struct
 *and its int variables
 *@list: the struct list
 *Return: the initialized list
 */
struct TOKEN_LIST *make_list(struct TOKEN_LIST *list)
{
	list = malloc(sizeof(TKL));
	if (list == NULL)
		exit(999);
	list->max_len = 0;/*initialize the var*/
	list->token_count = 0;/*initialize the var*/
	list->path = NULL;
	list->token_list = NULL;
	return (list);
}
/**
 * shell_start- is the user interface fucntion(prompt)
 * @Pname: the programe name
 */
void shell_start(char *Pname)
{
	char main_buffer[3024];
	struct TOKEN_LIST *list = NULL;
	char *tmp = NULL;

	while (1)
	{
		list = make_list(list);
		if (handle_write("$", list) == -1)
			exit(99);
		if (!fgets(main_buffer, sizeof(main_buffer), stdin))
		{
			free(list);
			return;
		}
		main_buffer[strlen(main_buffer) - 1] = '\0';
		if (main_buffer[0] != '\0')
		{
			list = main_parsser(main_buffer, list);
			list->path = check_command(list->token_list[0]);
			if (list->path == NULL)
			{
				built_in_mapper(list->token_list[0], list);
				NULL_path_handler(list);
				token_list_cleaner(list);
			}
			else
			{
				built_in_mapper(list->token_list[0], list);
				tmp = list->token_list[0];
				list->token_list[0] = list->path;
				EXECUTE(list);
				free(list->path), free(tmp);
				token_list_cleaner_not_token_list(list);
			}
			write(1, "\n", 1);
		}
		else
			free(list);
	}
}
/**
 * main- Entry point
 * @argc: count of arguments
 * @argv: list of args passed
 * Return: 0 if succsess , -1 otherwise
 */
int main(int argc, char **argv)
{
	char *path = NULL;
	/*if the user didnt enter any args directlly >> prompt mode*/
	if (argc <= 1)
		shell_start(argv[0]);
	/*if the user entered some args >> EXECUTE directly*/
	else
	{
		path = check_command(argv[1]);
		if (path == NULL)
		{
			DIRECT_EXECUTE2(argv);
			return (-1);
		}
		DIRECT_EXECUTE(argv, path);
	}
	return (0);
}
