#include "main.h"

/**
 * reallocate - function that reallocates a memory
 * block using malloc and free
 * @ptr: pointer to previously allocated memory
 * @o_size: size in bytes of allocated space for ptr
 * @n_size: size in bytes for new memory block
 *
 * Return: ptr if n_size == o_size, NULL
 * if n_size == 0 and ptr is not NULL and
 * a pointer to reallocated memory block if otherwise
 */
void *reallocate(void *ptr, unsigned int o_size, unsigned int n_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (n_size == o_size)
		return ptr;

	if (ptr == NULL)
	{
		mem = malloc(n_size);
		if (mem == NULL)
			return NULL;

		return mem;
	}

	if (n_size == 0 && ptr != NULL)
	{
		free(ptr);
		return NULL;
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * n_size);
	if (mem == NULL)
	{
		free(ptr);
		return NULL;
	}

	filler = mem;

	for (index = 0; index < o_size && index < n_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return mem;
}

/**
 * assign_lineptr - function that reassigns the lineptr
 * variable for _getline
 * @lineptr: a buffer to store input string
 * @n: size of lineptr
 * @buff: string to assign to the lineptr
 * @b: buffer size
 */
void assign_lineptr(char **lineptr, size_t *n, char *buff, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buff;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}

/**
 * _getline - function that reads input from a stream
 * @lineptr: buffer to store input
 * @n: The size of lineptr
 * @stream: stream to read from
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t i_size;
	ssize_t r;
	char c = 'x', *buff;
	int p;

	if (i_size == 0)
		fflush(stream);
	else
		return -1;
	i_size = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return -1;

	while (c != '\n')
	{
		p = read(STDIN_FILENO, &c, 1);
		if (p == -1 || (p == 0 && i_size == 0))
		{
			free(buff);
			return -1;
		}
		if (p == 0 && i_size != 0)
		{
			i_size++;
			break;
		}

		if (i_size >= 120)
			buff = reallocate(buff, i_size, i_size + 1);

		buff[i_size] = c;
		i_size++;
	}
	buff[i_size] = '\0';

	assign_lineptr(lineptr, n, buff, i_size);

	r = i_size;
	if (p != 0)
		i_size = 0;
	return r;
}

