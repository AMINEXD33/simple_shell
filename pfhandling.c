#include "shell.h"

/**
 * _memcpy - Copy a block of memory from one location to another.
 *
 * @newptr: Pointer to the destination memory location.
 * @ptr: Pointer to the source memory location.
 * @size: Number of bytes to copy.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - Reallocate memory for a previously allocated block.
 *
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: The size (in bytes) of the old memory block.
 * @new_size: The size (in bytes) of the new memory block.
 *
 * Return: Pointer to the reallocated memory block on success, or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - Reallocate memory for an array of character pointers.
 *
 * @ptr: Pointer to the previously allocated array of character pointers.
 * @old_size: The size (in number of pointers) of the old array.
 * @new_size: The size (in number of pointers) of the new array.
 *
 * Return: Pointer to the reallocated array on success, or NULL on failure.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
