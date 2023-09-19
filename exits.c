#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination for the copied string
 *@src: source string
 *@n: quantity of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int b, f;
	char *s = dest;

	b = 0;
	while (src[b] != '\0' && b < n - 1)
	{
		dest[b] = src[b];
		b++;
	}
	if (b < n)
	{
		f = b;
		while (f < n)
		{
			dest[f] = '\0';
			f++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: string number 1
 *@src: string number 2
 *@y: total bytes to be utilized
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int y)
{
	int b, f;
	char *s = dest;

	b = 0;
	f = 0;
	while (dest[b] != '\0')
		b++;
	while (src[f] != '\0' && f < y)
	{
		dest[b] = src[f];
		b++;
		f++;
	}
	if (f < y)
		dest[b] = '\0';
	return (s);
}

/**
 **_strchr - finds the position of a character in a string
 *@m: string to be parsed
 *@v: the character to look for
 *Return: (m)area m memory pointer
 */
char *_strchr(char *m, char v)
{
	do {
		if (*m == v)
			return (m);
	} while (*m++ != '\0');

	return (NULL);
}
