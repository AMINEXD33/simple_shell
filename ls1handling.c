#include "shell.h"

/**
 * add_rvar_node - Adds a new node to a linked list of replaceable variables.
 *
 * @head: Pointer to a pointer to the head of the linked list.
 * @lvar: The length of the variable to be added.
 * @val: The value of the variable to be added.
 * @lval: The length of the value of the variable to be added.
 *
 * Return: A pointer to the head of the updated linked list.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_rvar_list - Frees the memory allocated for a linked list of replaceable variables.
 *
 * @head: Pointer to a pointer to the head of the linked list.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
