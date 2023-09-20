#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <string.h>
/**
 * handle_write-this function handles writing something
 * to the STDOUT
 * @x: the string
 * @list: the struct list
 * Return: 0 always
 */
int  handle_write(char *x, struct TOKEN_LIST *list)
{
	if (write(1, x, strlen(x)) == -1)
	{
		token_list_cleaner(list);
		perror("Write failed !");
		return (-1);
	}
	return (0);
}
/**
 * str_eq_to- this function simply checks if two strings are equal
 * NOTE that if the two str1 and str2 are NULL the function will return
 * true , you can change this behaviour in the first if statment
 * @str1: string 1
 * @str2: string 2
 * Return: -1 not equal , 0 if the two strings are equal
 */
int str_eq_to(char *str1, char *str2)
{
	int x;

	if ((str1 == NULL && str2 == NULL))
	{
		return (0);
	}
	else if ((str1 == NULL && str2 != NULL) || (str1 != NULL && str2 == NULL))
	{
		return (-1);
	}
	x = 0;
	while (str1[x] != '\0' && str2[x] != '\0')
	{
		if ((str1[x] != str2[x]) ||
			((str1[x] == '\0' && str2[x] != '\0')) ||
			((str1[x] != '\0' && str2[x] == '\0')))
		{
			return (-1);
		}
		x++;
	}
	if ((str1[x] != str2[x]) ||
		((str1[x] == '\0' && str2[x] != '\0')) ||
		((str1[x] != '\0' && str2[x] == '\0')))
	{
		return (-1);
	}
	return (0);
}
