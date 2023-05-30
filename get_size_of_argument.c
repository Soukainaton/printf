#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int current_index = *i + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = S_LONG;
	else if (format[current_index] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_index - 1;
	else
		*i = current_index;

	return (size);
}	
