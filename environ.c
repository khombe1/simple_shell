#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: This structure to store potential function argument
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - the value of an environ variable
 * @info: Structure containing potential argument
 * @name: name of env var
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *d;

	while (node)
	{
		d = starts_with(node->str, name);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize new env variable/
 *              modify existing one
 * @info: Structure with potential arguments to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - take of env variable
 * @info: Structure with potential arguments to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure with potential arguments to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		add_node_end(&node, environ[z], 0);
	info->env = node;
	return (0);
}
