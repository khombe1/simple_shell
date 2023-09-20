#include "shell.h"

/**
 * get_environ - returns a copy of the environ array
 * @info: Structure with potential argument (not used here)
 * Return: 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || (info->environ = list_to_strings(info->env)))
	info->env_changed = 0;

	return info->environ;
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: The environment variable to remove.
 * Return: 1 on success, 0 otherwise
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = starts_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set or modify an environment variable
 * @info: Struct containing potential arguments (unused).
 * @var: The name of the environment variable.
 * @value: The value to assign to the environment variable.
 * Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *i;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		i = starts_with(node->str, var);
		if (i && *i == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
