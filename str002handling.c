#include "shell.h"

/**
 * _strdup - Duplicate a string in memory.
 *
 * @s: The string to duplicate.
 *
 * Return: Pointer to the newly allocated string or NULL on failure.
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Calculate the length of a string.
 *
 * @s: The string to measure.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}


/**
 * cmp_chars - Compare characters in a string with a delimiter.
 *
 * @str: The string to compare.
 * @delim: The delimiter string to compare against.
 *
 * Return: 1 if all characters in str match any character in delim, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - Split a string into tokens based on a delimiter.
 *
 * @str: The string to tokenize.
 * @delim: The delimiter string to use for tokenization.
 *
 * Return: Pointer to the next token in the string, or NULL if no more tokens.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; 
		i = _strlen(str);
		str_end = &str[i]; 
	}
	str_start = splitted;
	if (str_start == str_end) 
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) 
			bool = 1;
	}
	if (bool == 0) 
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - Check if a string consists of only digits.
 *
 * @s: The string to check.
 *
 * Return: 1 if the string contains only digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
