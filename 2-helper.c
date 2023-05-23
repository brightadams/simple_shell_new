#include "main.h"

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *o_line, *n_line;
	char prev, curr, next;
	size_t p, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	n_line = malloc(new_len + 1);
	if (!n_line)
		return;
	j = 0;
	o_line = *line;
	for (p = 0; o_line[p]; p++)
	{
		curr = o_line[p];
		next = o_line[p + 1];
		if (p != 0)
		{
			prev = o_line[p - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					n_line[j++] = ' ';
					n_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					n_line[j++] = ';';
					n_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					n_line[j++] = ' ';
				n_line[j++] = ';';
				if (next != ' ')
					n_line[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					n_line[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					n_line[j++] = '&';
					n_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					n_line[j++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					n_line[j++] = '|';
					n_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (p != 0 && o_line[p - 1] != ' ')
				n_line[j++] = ' ';
			n_line[j++] = ';';
			if (next != ' ' && next != ';')
				n_line[j++] = ' ';
			continue;
		}
		n_line[j++] = o_line[p];
	}
	n_line[j] = '\0';

	free(*line);
	*line = n_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t p;
	ssize_t new_len = 0;
	char curr, next;

	for (p = 0; line[p]; p++)
	{
		curr = line[p];
		next = line[p + 1];
		if (curr == '#')
		{
			if (p == 0 || line[p - 1] == ' ')
			{
				line[p] = '\0';
				break;
			}
		}
		else if (p != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[p - 1] != ' ' && line[p - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[p - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[p - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[p], &new_len);
		}
		else if (curr == ';')
		{
			if (p != 0 && line[p - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && next != ' ')
			(*new_len)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && next != ' ')
			(*new_len)++;
	}
}

