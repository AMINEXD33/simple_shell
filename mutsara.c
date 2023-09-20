#include "shell.h"

/**
 * exec_line - Execute a command line in the custom shell.
 *
 * @datash: Pointer to a data_shell structure containing shell data.
 *
 * Return: 0 on success, 1 on empty command, -1 on failure.
 */
int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
