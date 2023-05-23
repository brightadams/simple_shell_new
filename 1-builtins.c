#include "main.h"

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: This is an array of arguments.
 * @fr: A double pointer that begins args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **fr)
{
	alias_t *tmp = aliases;
	int m, ret = 0;
	char *val;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return ret;
	}
	for (m = 0; args[m]; m++)
	{
		tmp = aliases;
		val = _strchr(args[m], '=');
		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(args[m], tmp->name) == 0)
				{
					print_alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + m, 1);
		}
		else
			set_alias(args[m], val);
	}
	return ret;
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'
 * @var_name: Should be the Name of the alias
 * @value: The Value of the alias. First character is an '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int le, j, k;
	char *new_val;

	*value = '\0';
	value++;
	le = _strlen(value) - _strspn(value, "'\"");
	new_val = malloc(sizeof(char) * (le + 1));
	if (!new_val)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_val[k++] = value[j];
	}
	new_val[k] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_val;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&aliases, var_name, new_val);
}

/**
 * print_alias - This Prints the alias in the format name='value'.
 * @alia: Pointer to an alias.
 */
void print_alias(alias_t *alia)
{
	char *alias_str;
	int le = _strlen(alia->name) + _strlen(alia->value) + 4;

	alias_str = malloc(sizeof(char) * (le + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alia->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alia->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, le);
	free(alias_str);
}

/**
 * replace_aliases - This Goes through all the arguments and replace any matching alias
 * with their value.
 * @args: All 2D pointer to the arguments.
 *
 * Return: All 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *tmp;
	int m;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return args;
	for (m = 0; args[m]; m++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmp(args[m], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return NULL;
				}
				_strcpy(new_val, tmp->value);
				free(args[m]);
				args[m] = new_val;
				m--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return args;
}

