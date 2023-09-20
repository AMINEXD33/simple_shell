#include "shell.h"
/**
 * get_error - Handle and display various error messages.
 *
 * This function handles different error scenarios based on the value of `eval`,
 * and displays the corresponding error message to the standard error (stderr).
 * It also updates the `datash->status` with the provided `eval` value.
 *
 * @datash: Pointer to the data_shell structure.
 * @eval: The error code or evaluation value to determine the error type.
 *
 * Return: The same `eval` value passed as a parameter.
 */
int get_error(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
