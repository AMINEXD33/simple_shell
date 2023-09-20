#include "shell.h"

/**
 * read_line - Read a line of text from standard input (stdin).
 *
 * This function reads a line of text from the standard input (stdin).
 * It dynamically allocates memory for the input line and updates the
 * buffer size accordingly.
 *
 * @i_eof: Pointer to an integer flag indicating end-of-file (EOF).
 *         It is set to 0 if a line is successfully read, or -1 if EOF is reached.
 *
 * Return: A pointer to the dynamically allocated input line.
 *         NULL is returned if an error occurs or if EOF is reached.
 *         The caller is responsible for freeing the allocated memory.
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
