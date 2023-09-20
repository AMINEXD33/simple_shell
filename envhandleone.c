#include "shell.h"

/**
 * cmp_env_name - Compare the beginning of an environment variable name with a string.
 *
 * This function compares the characters in the `nenv` string with the characters in
 * the `name` string until the '=' character is encountered in the `nenv` string.
 *
 * @nenv: The environment variable string to compare.
 * @name: The name to compare against.
 *
 * Return: The number of characters successfully compared, or 0 if there is no match.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - Retrieve the value of an environment variable.
 *
 * This function searches for an environment variable with the specified `name`
 * in the `_environ` array and returns a pointer to the value part of the variable.
 *
 * @name: The name of the environment variable to retrieve.
 * @_environ: The array of environment variables.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Init ptr_env val */
	ptr_env = NULL;
	mov = 0;
	/* */
	/*  */
	for (i = 0; _environ[i]; i++)
	{
		/* comments here */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - Display the environment variables.
 *
 * This function displays the environment variables stored in the `datash->_environ`
 * array, printing each variable followed by a newline character to standard output.
 *
 * @datash: Pointer to the data_shell structure.
 *
 * Return: Always returns 1 (indicating success).
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
