#include "main.h"

/**
 * _copyenv - A function that creates a copy of the environment.
 *
 * Return: If an error occurs, return NULL.
 *         Otherwise, return a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **n_env;
	size_t size;
	int ind;

	for (size = 0; environ[size]; size++)
		;

	n_env = malloc(sizeof(char *) * (size + 1));
	if (!n_env)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		n_env[ind] = malloc(_strlen(environ[ind]) + 1);

		if (!n_env[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(n_env[ind]);
			free(n_env);
			return (NULL);
		}
		_strcpy(n_env[ind], environ[ind]);
	}
	n_env[ind] = NULL;

	return (n_env);
}

/**
 * free_env - A function that frees the copy of the environment.
 */
void free_env(void)
{
	int ind;

	for (ind = 0; environ[ind]; ind++)
		free(environ[ind]);
	free(environ);
}

/**
 * _getenv - A function that gets an environmental variable from the PATH.
 * @var: The environmental variable name.
 *
 * Return: NULL if the environmental variable does not exist,
 *         or a pointer to the environmental variable otherwise.
 */
char **_getenv(const char *var)
{
	int ind, len;

	len = _strlen(var);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(var, environ[ind], len) == 0)
			return (&environ[ind]);
	}

	return (NULL);
}

