#include "shell.h"

/**
 * interactive - true when shell is in interactive mode
 * @info: address structure
 *
 * Return: 1 when it is interactive mode, 0 if not so
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks delimeter status
 * @t: char to check
 * @delim: string for the delimeter
 * Return: 1 iin case its true, 0 if false
 */
int is_delim(char t, char *delim)
{
	while (*delim)
		if (*delim++ == t)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabeticals
 * @h: Input character
 * Return: 1 incase c is alphabetical, 0 if not
 */

int _isalpha(int h)
{
	if ((h >= 'a' && h <= 'z') || (h >= 'A' && h <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string to integer converter
 * @q: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *q)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; q[i] != '\0' && flag != 2; i++)
	{
		if (q[i] == '-')
			sign *= -1;

		if (q[i] >= '0' && q[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (q[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
