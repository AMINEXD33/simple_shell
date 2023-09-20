#include "shell.h"

/**
 * get_sigint - Handle the SIGINT signal.
 *
 * This function is a signal handler for the SIGINT signal (typically generated
 * when the user presses Ctrl+C). It simply writes a newline character to the
 * standard output to provide a clean line break in the shell.
 *
 * @sig: The signal number (unused, required by the signal handler prototype).
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}
