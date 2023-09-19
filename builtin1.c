#include "shell.h"

/**
 * _myhistory - Display history list, one command by line
 *              with line numbers,beggining from 0.
 * @info: Structure constisting of potential arguments.maintaining
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Alias to string
 * @info: Parameter structure
 * @str: alias string
 *
 * Return: Always 0 on success, on error 1
 */
int unset_alias(info_t *info, char *str)
{
	char *z, y;
	int ret;

	z = _strchr(str, '=');
	if (!z)
		return (1);
	y = *z;
	*z = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*z = y;
	return (ret);
}

/**
 * set_alias -Alias of string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, on error 1
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: alias node
 *
 * Return: Always 0 on success, on error 1
 */
int print_alias(list_t *node)
{
	char *d = NULL, *a = NULL;

	if (node)
	{
		d = _strchr(node->str, '=');
		for (a = node->str; a <= d; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
