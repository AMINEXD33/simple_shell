#include "shell.h"

/**
 * copy_info - Create a new environment variable string.
 *
 * This function takes a `name` and a `value` and combines them into a new
 * environment variable string in the format "name=value". It allocates memory
 * for the new string and returns it.
 *
 * @name: The name part of the environment variable.
 * @value: The value part of the environment variable.
 *
 * Return: A pointer to the newly created environment variable string.
 *         NULL is returned if memory allocation fails.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - Set or update an environment variable.
 *
 * This function sets or updates an environment variable with the specified `name`
 * and `value` in the `datash->_environ` array. If the variable exists, it updates
 * its value; otherwise, it creates a new variable. Memory management for the
 * `_environ` array is handled accordingly.
 *
 * @name: The name of the environment variable to set/update.
 * @value: The value of the environment variable.
 * @datash: Pointer to the data_shell structure.
 *
 * Return: No return value.
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - Set or update an environment variable.
 *
 * This function is a wrapper for the `set_env` function. It sets or updates an
 * environment variable based on the arguments provided in the `datash->args`
 * array. It checks for the presence of required arguments and handles the
 * environment variable accordingly.
 *
 * @datash: Pointer to the data_shell structure.
 *
 * Return: Always returns 1 (indicating success).
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - Unset an environment variable.
 *
 * This function removes an environment variable specified by name in the
 * `datash->args` array from the `datash->_environ` array. It reallocates
 * memory as needed and updates the environment variables accordingly.
 *
 * @datash: Pointer to the data_shell structure.
 *
 * Return: Always returns 1 (indicating success).
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
