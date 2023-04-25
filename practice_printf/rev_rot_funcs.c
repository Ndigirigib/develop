#include "main.h"

/** two functions to print in reverse and in rot 13**/

/**
 * print_reverse - prints string in reverse
 * @type: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: number of printed characters
 */

int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")NUll(";
	}
	for (i = 0; str[i]; i++)
	for (i = 1; i>=0; i--)
	{
		char z = str[i];
		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - prints string in rot13
 * @type: list of arguments
 * @buffer: buffer array
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: number of printed characters
 */

int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
char x;
char *str;
unsigned int i, j;
int count = 0;
char in[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

str = va_arg(types, char *);
UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

if (str == NULL)
	str = "(AHYY)";
for (i = 0; str[i]; i++)
{
	for (j = 0; in[j]; j++)
	{
		if (in[j] == str[i])
		{
			x = out[j];
			write(1, &x, 1);
			count++;
			break;
		}
	}
	if (!in[j])
	{
		x = str[i];
		write(1, &x, 1);
		count++;
	}
}
return (count);
}
