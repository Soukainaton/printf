#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int current_index = *i + 1;
	int prec = -1;

	if (format[current_index] != '.')
		return (prec);

	prec = 0;

	for (current_index += 1; format[current_index] != '\0'; current_index++)
	{
		if (is_digit(format[current_index]))
		{
			prec *= 10;
			prec += format[current_index] - '0';
		}
		else if (format[curr_i] == '*')
		{
			current_index++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (prec);
}
