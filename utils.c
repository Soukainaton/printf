#include "main.h"

/**
 * is_printable - check if a char is printable
 * @c: Character
 * Return: 1 if c is printable, if it fails 0
 */
int is_printable(char c)
{
if (c >= 32 && c < 127)
{
return (1);
}
return (0);
}

/**
 * append_hexa_code - Append ASSCI code in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @i: Index at which to start appending
 * @ascii_code: ASSCI CODE
 * Return: always return 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
char map[] = "0123456789ABCDEF";
if (ascii_code < 0)
{
ascii_code *= -1;
}

buffer[i++] = '\\';
buffer[i++] = 'x';

buffer[i++] = map[ascii_code / 16];
buffer[i] = map[ascii_code % 16];

return (3);
}

/**
 * is_digit - Verifies if a char given is a digit
 * @c: Char to be checked
 *
 * Return: 1 if it is a digit, if it fails 0
 */
int is_digit(char c)
{
if (c >= '0' && c <= '9')
{
return (1);
}

return (0);
}

/**
 * convert_size_number - casts a number to a specified size
 * @num: integer to be casted.
 * @size: integerer indicating the type to be casted in
 * Return: casted value
 */
long int convert_size_number(long int num, int size)
{
if (size == S_LONG)
{
return (num);
}
else if (size == S_SHORT)
{
return ((short)num);
}

return ((int)num);
}
/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
if (size == S_LONG)
{
return (num);
}
else if (size == S_SHORT)
{
return ((unsigned short)num);
}
return ((unsigned int)num);
}
