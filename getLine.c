#include "shell.h"

/**
 * input_buf - buffer commands.
 * @info: structure of the parameter
 * @buf: buffer address
 * @len: len var address
 *
 * Return: The bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets line minus the newline
 * @info: structure of parameter
 *
 * Return: The bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t a, q, len;
	ssize_t z = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(info, &buf, &len);
	if (z == -1)
		return (-1);
	if (len)
	{
		q = a;
		p = buf + a;

		check_chain(info, buf, &q, a, len);
		while (q < len)
		{
			if (is_chain(info, buf, &q))
				break;
			q++;
		}

		a = q + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (z);
}

/**
 * read_buf - read buffer
 * @info: structure of parameter
 * @buf:The buffer
 * @x:The size
 *
 * Return: i
 */
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
	ssize_t i = 0;

	if (*x)
		return (0);
	i = read(info->readfd, buf, READ_BUF_SIZE);
	if (i >= 0)
		*x = i;
	return (i);
}

/**
 * _getline - get next line of input
 * @info: structure of the parameter
 * @ptr: the address of pointer to buffer, preallocated/ NULL
 * @length: the size of preallocated ptr buffer if not NULL
 *
 * Return: z
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t i;
	ssize_t r = 0, z = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		z = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	i = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, z, z ? z + i : i + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat(new_p, buf + j, i - j);
	else
		_strncpy(new_p, buf + j, i - j + 1);

	z += i - j;
	j = i;
	p = new_p;

	if (length)
		*length = z;
	*ptr = p;
	return (z);
}

/**
 * sigintHandler - block ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
