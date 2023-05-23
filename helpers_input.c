#include "main.h"

/**
 * get_args - function that gets a command from standard input
 * @line: buffer to store the command
 * @exe_ret: return value of last command executed
 *
 * Return: NULL if an error occurs or, a pointer
 * to the stored command if otherwise
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - function that partitions operators from commands
 * @args: array of arguments
 * @front: double pointer to beginning of args
 * @exe_ret: return value of parent process last executed command
 *
 * Return: return value of the last executed command
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int r, ind;

	if (!args[0])
		return (*exe_ret);
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			r = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (r);
			}
		}
		else if (_strncmp(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			r = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (r);
			}
		}
	}
	args = replace_aliases(args);
	r = run_args(args, front, exe_ret);
	return (r);
}

/**
 * run_args - function that calls the execution of a command
 * @args: array of arguments
 * @front: double pointer to beginning of args
 * @exe_ret: return value of parent process last executed command
 *
 * Return: return value of the last executed command
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int r, p;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		r = builtin(args + 1, front);
		if (r != EXIT)
			*exe_ret = r;
	}
	else
	{
		*exe_ret = execute(args, front);
		r = *exe_ret;
	}

	hist++;

	for (p = 0; args[p]; p++)
		free(args[p]);

	return (r);
}

/**
 * handle_args - function that gets, calls, and
 * runs the execution of command
 * @exe_ret: return value of the parent process
 * last executed command
 *
 * Return: END_OF_FILE (-2) if an end-of-file is read
 * and -1 If the input cannot be tokenized or the
 * exit value of the last executed command if otherwise
 */
int handle_args(int *exe_ret)
{
	int r = 0, ind;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (r);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], ";", 1) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			r = call_args(args, front, exe_ret);
			args = &args[++ind];
			ind = 0;
		}
	}
	if (args)
		r = call_args(args, front, exe_ret);

	free(front);
	return (r);
}

/**
 * check_args - function that checks if there are
 * any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: 2 if a ';', '&&', or '||' is placed at an
 * invalid position or  0 if Otherwise
 */
int check_args(char **args)
{
	size_t p;
	char *current, *n;

	for (p = 0; args[p]; p++)
	{
		current = args[p];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (p == 0 || current[1] == ';')
				return (create_error(&args[p], 2));
			n = args[p + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
				return (create_error(&args[p + 1], 2));
		}
	}
	return (0);
}

