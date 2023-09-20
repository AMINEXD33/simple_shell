#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <string.h>
/**
 *main_parsser- the main parser is the step one to process the
 * command passed as (main_buffer), the function separate eatch
 * token inside the main_buffer with ETX (end of text)(asscci value = 3)
 * and keeps track of the longest token found , and the number of tokes
 * found.
 * var explaination:
 *	index: tracker for the main buffer
 *	space_flag: is space detected? (1 yes | 0 no)
 *	letters_flag: is a character? (SPACE NOT INCLUDED)(1 yes | 0 no)
 *	letters_count: len of every token in the main buffer
 *
 * @main_buffer: the buffer containing the command passed to the program
 * @list: the list struct
 *Return: the address of the list struct
 */
struct TOKEN_LIST *main_parsser(char *main_buffer, struct TOKEN_LIST *list)
{
	int index, space_flag, letters_flag, letters_count, start_at;

	index = 0, space_flag = 1, start_at = 0;
	letters_flag = 0, letters_count = 0;
	while (main_buffer[start_at] == ' ')
		start_at++;
	while (main_buffer[index] != '\0')
	{
		if (main_buffer[index] == ' ')
		{
			space_flag = 1;
			letters_flag = 0;
		}
		else
		{
			letters_flag = 1;
			letters_count += 1;
		}
		if (space_flag == 1 && letters_flag == 1)
		{
			if (index != 0)
				main_buffer[index - 1] = '~';
			list->token_count++;
			space_flag = 0;
			letters_flag = 0;
			if (letters_count > list->max_len)
				list->max_len  = letters_count;
			letters_count = 0;
		}
		index++;
	}
	if (letters_count > list->max_len)
		list->max_len  = letters_count;
	list->max_len++;/*add one to count for the 0 at the begining*/
	list->max_len++;/*margin error in case*/
	list = alloc_args_list(list);
	list = PL(list, main_buffer, start_at);
	return (list);
}
/**
 *alloc_args_list- this fucntion will enitialize the 2D
 * array inside the list struct , with respect to the
 * width = the count of the tokens found
 * cell_length = the max length token found
 *
 * Description: execve usually work with a list of args terminated
 * with a (char*)0 which is NULL, if not added , the function
 * return bad address
 *
 * @list: the address of the list struct
 * Return: the address of the list struct after
 * enitializing the 2D array
 */
struct TOKEN_LIST *alloc_args_list(struct TOKEN_LIST *list)
{
	int args_count2;/*track position*/

	args_count2 = 0;
	/*malloc the width of the list*/
	list->token_list = NULL;
	list->token_list = malloc(sizeof(char *) * (list->token_count + 1));
	list->token_list[list->token_count] = (char *)0;/*add null,see description*/
	if (list->token_list == NULL)
	{
		free(list->token_list);
		free(list);
		exit(400);/*cant allocate*/
	}
	while (args_count2 < list->token_count)
	{
		/*malloc the length of eatch memorie part*/
		list->token_list[args_count2] = NULL;
		list->token_list[args_count2] = malloc(sizeof(char) * list->max_len + 1);
		if (list->token_list[args_count2] == NULL)
		{
			for (int i = 0; i < args_count2; i++)
			{
				free(list->token_list[i]);
			}
			free(list->token_list);
			free(list);
			exit(500);/*cant allocate*/
		}
		args_count2++;
	}
	return (list);
}
/**
 * PL- this function will take care of populating
 * the 2D array with the tokens passed previously.
 * it goes trought the main buffer and adds a token to its
 * coresponding place in the array.
 * @list: the struct list
 * @ma_buffer: the buffer containing the command
 * @s_at: the index from which the function need to start reading
 * basically to dodge some problems that comes with leading white
 * spaces
 *struct TOKEN_LIST - see main.h
 * Return: the address of list struct
 */
struct TOKEN_LIST *PL(struct TOKEN_LIST *list, char *ma_buffer, int s_at)
{
	int arg_tracker = 0;
	int arg_index = 0;
	int main_buffer_index = 0;

	arg_tracker = 0;
	arg_index = 0;
	main_buffer_index = s_at;
	while (ma_buffer[main_buffer_index] != '\0')
	{
		if (ma_buffer[main_buffer_index] != ' ' && ma_buffer[main_buffer_index]
		!= '~')
		{
			list->token_list[arg_tracker][arg_index] = ma_buffer[main_buffer_index];
			arg_index++;
		}
		else if (ma_buffer[main_buffer_index] == '~')
		{
			list->token_list[arg_tracker][arg_index] = '\0';
			arg_index = 0;
			arg_tracker++;
		}
		main_buffer_index++;
	}
	list->token_list[arg_tracker][arg_index] = '\0';
	return (list);
}
/**
 * token_list_cleaner- is a clean up function
 * after the command is dealt with , this function
 * takes care of cleaning the current list struct
 * @list: the list struct
 * Return: always (1)
 */
int token_list_cleaner(struct TOKEN_LIST *list)
{
	int x;

	x = 0;
	x = list->token_count;
	while (x > 0)
	{
		printf("freeing cell N: %d\n", x);
		free(list->token_list[x]);
		x--;
	}
	free(list->token_list[x]);
	printf("[+]freeing list token_list and list\n");
	free(list->token_list);
	list->token_count = 0;
	list->max_len = 0;
	free(list);
	return (1);
}
/**
 * token_list_cleaner_not_token_list - same as token_lis_cleaner
 * but it doesnt fee the list->token_list[x] after the while loop
 * @list: the list struct
 * Return: 1 always
 */
int token_list_cleaner_not_token_list(struct TOKEN_LIST *list)
{
	int x;

	x = 0;
	x = list->token_count;
	while (x > 0)
	{
		free(list->token_list[x]);
		x--;
	}
	free(list->token_list);
	list->token_count = 0;
	list->max_len = 0;
	free(list);
	return (1);
}
