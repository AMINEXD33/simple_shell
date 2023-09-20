#include "shell.h"

/**
 * get_builtin - Find and return a pointer to a built-in shell function
 *
 * This function takes a command string and searches for a corresponding
 * built-in shell function. If the command is found, it returns a pointer
 * to the corresponding function; otherwise, it returns NULL.
 *
 * @cmd: The command string to look for in the list of built-in commands.
 *
 * Return: A pointer to the built-in shell function if found, otherwise NULL.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
