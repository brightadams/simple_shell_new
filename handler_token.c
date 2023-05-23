#include "main.h"

/**
 * token_len - function that locates the delimiter
 * index marking the end of the first token
 * @str: the string that will be searched
 * @delim: delimiter character
 *
 * Return: delimiter index marking the end of
 * initial token pointed to by str
 */
int token_len(char *str, char *delim)
{
	int ind = 0, len = 0;

	while (*(str + ind) && *(str + ind) != *delim)
	{
		len++;
		ind++;
	}

	return (len);
}

/**
 * count_tokens - function that counts the number of
 * delimited words contained in a string
 * @str: string to be searched
 * @delim: delimiter character
 *
 * Return: total count of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int ind, token_count = 0, len = 0;

	for (ind = 0; *(str + ind); ind++)
		len++;

	for (ind = 0; ind < len; ind++)
	{
		if (*(str + ind) != *delim)
		{
			token_count++;
			ind += token_len(str + ind, delim);
		}
	}

	return (token_count);
}

/**
 * _strtok - function that tokenizes a string
 * @line: the string
 * @delim: delimiter character to tokenize the string
 *
 * Return: pointer to array containing tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **tokens;
	int ind = 0, token_count, k, let, l;

	token_count = count_tokens(line, delim);
	if (token_count == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (token_count + 2));
	if (!tokens)
		return (NULL);

	for (k = 0; k < token_count; k++)
	{
		while (line[ind] == *delim)
			ind++;

		let = token_len(line + ind, delim);

		tokens[k] = malloc(sizeof(char) * (let + 1));
		if (!tokens[k])
		{
			for (ind -= 1; ind >= 0; ind--)
				free(tokens[ind]);
			free(tokens);
			return (NULL);
		}

		for (l = 0; l < let; l++)
		{
			tokens[k][l] = line[ind];
			ind++;
		}

		tokens[k][l] = '\0';
	}
	tokens[k] = NULL;
	tokens[k + 1] = NULL;

	return (tokens);
}

