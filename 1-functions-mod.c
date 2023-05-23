#include "main.h"

/**
 * str_length - Returns the length of a string
 * @str: Pointer to the string
 *
 * Return: Length of the string
 */
int str_length(const char *str)
{
	int len = 0;

	if (!str)
		return (len);

	for (len = 0; str[len]; len++)
		;

	return (len);
}

/**
 * str_copy - Copies the contents of the source string to the destination buffer
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 *
 * Return: Pointer to the destination buffer
 */
char *str_copy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';
	return (dest);
}

/**
 * str_concat - Concatenates two strings
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 *
 * Return: Pointer to the destination string
 */
char *str_concat(char *dest, const char *src)
{
	char *dest_ptr = dest;
	const char *src_ptr = src;

	while (*dest_ptr != '\0')
		dest_ptr++;

	while (*src_ptr != '\0')
		*dest_ptr++ = *src_ptr++;

	*dest_ptr = '\0';
	return (dest);
}

/**
 * str_nconcat - Concatenates two strings up to n characters from source
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 * @n: Number of characters to copy from source
 *
 * Return: Pointer to the destination string
 */
char *str_nconcat(char *dest, const char *src, size_t n)
{
	size_t dest_len = str_length(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}

