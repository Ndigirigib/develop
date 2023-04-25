#include "main.h"

/**write handling functions**/

/**
 * handle_write_char - prints a string
 * @c: character 
 * @buffer: buffer array 
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: number of printed characters
 */

int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	/*character is stored at the left and paddind at buffer's right*/
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';

		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) + write (1, &buffer[BUFF_SIZE - i - 1], width - 1));

		else

			return (write(1, &buffer[BUFF_SIZE - i - 1],width -1) + write (1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**Write number**/

/**
 * write_number - prints a string
 * @is_negative: list of arguments
 * @ind: character types
 * @buffer: buffer
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: number of printed characters
 */

int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision, length, padd, extra_ch));
}

/**Write number using a buffer**/

/**
 * write_num - prints a string
 * @ind: first index at which the number starts on buffer
 * @buffer: buffer
 * @flags: active flags
 * @width: width
 * @prec: precision
 * @length: length
 * @padd: padding 
 * @extra_c : extra character
 *
 * Return: number of printed characters
 */

int write_num(int ind, char buffer[],
		int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == '0')
		return (0); /**printf(".0d". 0)no printed char**/
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /**width is displayed with padding**/
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

		if (flags & F_MINUS && padd == ' ')/** Assign extra character to buffer**/
		{
			if (extra_c)
				buffer[--ind] = extra_c;

		return(write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}

		else if (!(flags & F_MINUS) && padd == ' ')/**extra char to left of buffer*/
		{
			if (extra_c)
				buffer[--ind] = extra_c;
		return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}

		else if (!(flags & F_MINUS) && padd == '0')/**extra char to padd**/
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
		return (write(1, &buffer[padd_start], i -padd_start) + write(1, &buffer[ind], length -(1 - padd_start)));
		}
	}	
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));

}


/**
 * write_unsgnd - prints an unsigned number
 * @is_negative: number indicating whether the number is negative
 * @ind: inde at which number starts in buffer
 * @buffer: buffer
 * @flags: active flags
 * @width: width
 * @precision: precision
 * @size: size
 *
 * Return: number of printed characters
 */
	
int write_unsgnd(int is_negative, int ind,
		char buffer[], int flags, int width, int precision, int size)
{
	/**number is stored at the buffer's right and starts at position i **/

	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /*printf(".0d", 0) no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length ++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /**assign extra char to left of buffer [buffer>padd]*/
		{
			return(write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /** assign extra char to the left of padding [padd>buffer]**/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - prints a memory address
 * @buffer: array of characters
 * @ind: index at which the number starts in buffer
 * @length: length
 * @flags: active flags
 * @width: width
 * @padd: padding character
 * @extra_c: extra character
 * @padd_start : index where padding stops
 *
 * Return: number of printed characters
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
		if (flags & F_MINUS && padd == ' ') /**assign extra char to the left of the buffer**/
		{

			buffer[--ind] = 'x';
			buffer[--ind] = '0';

			if (extra_c)
				buffer[--ind] = extra_c;
			return(write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/**extra character to the left of the buffer**/
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if(extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/**extra character to the left of the padding**/
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';

			return (write(1, &buffer[padd_start], i - padd_start) + write (1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}

	buffer[--ind] = 'x';
	buffer[--ind] = '0';

	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}			
