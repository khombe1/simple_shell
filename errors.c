#include "shell.h"

/**
 * _eputs - print string
 * @str: string to print
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_eputchar(str[z]);
		z++;
	}
}

/**
 * _eputchar - write character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno set appropriately.
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - write character c to given fd
 * @c: character to print
 * @fd: filedescriptor to write
 *
 * Return: success 1.
 * On error, -1 is returned, and errno set
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - print input string
 * @str: string to be printed
 * @fd: filedescriptor to write
 *
 * Return: number of chars
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
