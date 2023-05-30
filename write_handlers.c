#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: character
 * @buffer: Buffer array to handle print
 * @flags:  integer calculates active flags.
 * @width: integer
 * @precision: integer
 * @size: integer
 *
 * Return: number of characters printed.
 */
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
/* char is stored at left and padding at buffer's right */
int i = 0;
char pad = ' ';

UNUSED(precision);
UNUSED(size);

if (flags & F_ZERO)
	pad = '0';
buffer[i++] = c;
buffer[i] = '\0';

if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
	buffer[BUFF_SIZE - i - 2] = pad;

if (flags & F_MINUS)
	return (write(1, &buffer[0], 1) +
	write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
else
	return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
	write(1, &buffer[0], 1));
}

return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - prints a string
 * @is_negative: integer
 * @ind: characters
 * @buffer: Buffer array
 * @flags:  integer calculates active flags
 * @width: integer
 * @precision: integer
 * @size: integer
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int l = BUFF_SIZE - ind - 1;
char pad = ' ', cha = 0;

UNUSED(size);

if ((flags & F_ZERO) && !(flags & F_MINUS))
	pad = '0';
if (is_negative)
	cha = '-';
else if (flags & F_PLUS)
	cha = '+';
else if (flags & F_SPACE)
	cha = ' ';

return (write_num(ind, buffer, flags, width, precision, l, pad, cha));
}

/**
 * write_num - Write a number
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: integer
 * @width: integer
 * @prec: integer
 * @length: integer
 * @padd:integer
 * @extra_c: Extra character
 *
 * Return: Number of printed characters
 */
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
int i, pad = 1;

if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
	return (0); /* printf(".0d", 0)  no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
	padd = ' ';
while (prec > length)
	buffer[--ind] = '0', length++;
if (extra_c != 0)
	length++;
if (width > length)
{
	for (i = 1; i < width - length + 1; i++)
		buffer[i] = padd;
	buffer[i] = '\0';
	if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
	{
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
	}
	else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
	{
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
	}
	else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
	{
		if (extra_c)
			buffer[--pad] = extra_c;
		return (write(1, &buffer[pad], i - pad) +
			write(1, &buffer[ind], length - (1 - pad)));
	}
}
if (extra_c)
	buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - writes an unsigned number
 * @is_negative: Number
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: integer
 * @width: integer
 * @precision: integer
 * @size: integer
 * Return: Number of written characters.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
int length = BUFF_SIZE - ind - 1, i = 0;
char pad = ' ';

UNUSED(is_negative);
UNUSED(size);

if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	return (0); /* printf(".0d", 0)  no char is printed */

if (precision > 0 && precision < length)
	pad = ' ';

while (precision > length)
{
	buffer[--ind] = '0';
	length++;
}

if ((flags & F_ZERO) && !(flags & F_MINUS))
	pad = '0';

if (width > length)
{
	for (i = 0; i < width - length; i++)
		buffer[i] = pad;

	buffer[i] = '\0';

	if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>pad]*/
	{
		return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
	}
	else /* Asign extra char to left of padding [pad>buffer]*/
	{
	return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
	}
}

return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of characters
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: integer
 * @flags: integer
 * @padd: Character representing the padding
 * @extra_c: Character representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
int i;

if (width > length)
{
	for (i = 3; i < width - length + 3; i++)
		buffer[i] = padd;
	buffer[i] = '\0';
	if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
	{
		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
	}
	else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
	{
		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
	}
	else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
	{
		if (extra_c)
			buffer[--padd_start] = extra_c;
		buffer[1] = '0';
		buffer[2] = 'x';
		return (write(1, &buffer[padd_start], i - padd_start) +
			write(1, &buffer[ind], length - (1 - padd_start) - 2));
	}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
	buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
