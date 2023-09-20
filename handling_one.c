#include "shell.h"

/**
 * aux_help - Display help information for the 'help' command.
 *
 * This function displays help information for the 'help' command, explaining
 * its usage and purpose.
 *
 * Return: void
 */
void aux_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * aux_help_alias - Display help information for the 'alias' command.
 *
 * This function displays help information for the 'alias' command, explaining
 * its usage and purpose.
 *
 * Return: void
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * aux_help_cd - Display help information for the 'cd' command.
 *
 * This function displays help information for the 'cd' command, explaining
 * its usage and purpose.
 *
 * Return: void
 */
void aux_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
