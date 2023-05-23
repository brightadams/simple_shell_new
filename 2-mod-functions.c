#include "main.h"

/**
 * _strchr - function that locates a character in a string
 * @str: the string that will be searched
 * @ch: the character that will be located
 *
 * Return: a pointer to the first occurence if ch is
 * found or NULL If ch is not found
 */
char *_strchr(char *str, char ch)
{
	int index;

	for (index = 0; str[index]; index++)
	{
		if (str[index] == ch)
			return (str + index);
	}

	return (NULL);
}

/**
 * _strspn - function that gets the length of a prefix substring
 * @str: the string that will be searched
 * @accept: the prefix that will be measured
 *
 * Return: number of bytes in str which consist
 * only of bytes from accept
 */
int _strspn(char *str, char *accept)
{
	int bytes = 0;
	int index;

	while (*str)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*str == accept[index])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - function that compares two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: positive byte difference if str1 > str2, 0 if str1 = str2
 * and negative byte difference if str1 < str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - function that compare two strings
 * @str1: first pointer to a string
 * @str2: second pointer to a string
 * @length: The first length bytes of the strings to be compared
 *
 * Return: less than 0 if str1 is shorter than str2,
 * greater than 0 is str1 is longer than str2 and 0 if they match
 */
int _strncmp(const char *str1, const char *str2, size_t length)
{
	size_t p;

	for (p = 0; str1[p] && str2[p] && p < length; p++)
	{
		if (str1[p] > str2[p])
			return (str1[p] - str2[p]);
		else if (str1[p] < str2[p])
			return (str1[p] - str2[p]);
	}
	if (p == length)
		return (0);
	else
		return (-15);
}

