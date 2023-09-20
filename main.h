#ifndef MAIN_H
#define MAIN_H
/**
 * struct TOKEN_LIST - the propreties needed to handle
 * the tokens list
 * @max_len: the len of the largest arg
 * @token_count: the number of tokens
 * @token_list: 2D array containing all the tokens
 * @path: this where the path of theprogramme are stored
 * when found
 */
typedef struct TOKEN_LIST
{
	int max_len;
	int token_count;
	char *path;
	char **token_list;
} TKL;

/**
 * struct built_in_command_functions - a data type that maps
 * a builtin command to it's propper function
 * @command_name: the name of the built in command
 * @func: the proper function for the command_name
 */
typedef struct built_in_command_functions
{
	char *command_name;
	void (*func)(struct TOKEN_LIST *list);
} BCF;

void shell_start(char *Pname);

struct TOKEN_LIST *make_list(struct TOKEN_LIST *list);

struct TOKEN_LIST *main_parsser(char *main_buffer, struct TOKEN_LIST *list);

struct TOKEN_LIST *alloc_args_list(struct TOKEN_LIST *list);

int EXECUTE(struct TOKEN_LIST *list);

int token_list_cleaner(struct TOKEN_LIST *list);

int token_list_cleaner_not_token_list(struct TOKEN_LIST *list);

int DIRECT_EXECUTE(char **argv, char *path);

int DIRECT_EXECUTE2(char **argv);

char *check_command(char *command);

int  handle_write(char *x, struct TOKEN_LIST *list);

void handle_fget(char *main_buffer, struct TOKEN_LIST *list);

void NULL_path_handler(struct TOKEN_LIST *list);

int built_in_mapper(char *command, struct TOKEN_LIST *list);

void exit_shell(struct TOKEN_LIST *list);

int str_eq_to(char *str1, char *str2);

struct TOKEN_LIST *PL(struct TOKEN_LIST *list, char *ma_buffer, int s_at);

#endif /*MAIN_H*/
