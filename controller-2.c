#include "main.h"

/**
 * num_len - Function that counts the digit
 * length of a number.
 * @number: The number to be measured.
 *
 * Return: The digit length.
 */
int num_len(int number)
{
	unsigned int n;
	int length = 1;

	if (number < 0)
	{
		length++;
		n = number * -1;
	}
	else
	{
		n = number;
	}

	while (n > 9)
	{
		length++;
		n /= 10;
	}

	return (length);
}

/**
 * _itoa - Function that converts an
 * integer to a string.
 * @number: The integer to be converted.
 *
 * Return: The converted string.
 */
char *_itoa(int number)
{
	char *buff;
	int length = num_len(number);
	unsigned int n;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);

	buff[length] = '\0';

	if (number < 0)
	{
		n = number * -1;
		buff[0] = '-';
	}
	else
	{
		n = number;
	}

	length--;
	do {
		buff[length] = (n % 10) + '0';
		n /= 10;
		length--;
	} while (n > 0);

	return (buff);
}


/**
 * create_error - Function that writes a custom
 * error message.
 * @args: Array of arguments.
 * @err: Value of the error.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);
}

