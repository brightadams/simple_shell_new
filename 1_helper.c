#include "main.h"

void free_args(char **args, char **front)
{
    size_t p;

    for (p = 0; args[p] || args[p + 1]; p++)
        free(args[p]);

    free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replaces the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
    size_t p = 0;
    char *buffer;
    ssize_t file;

    file = open("/proc/self/stat", O_RDONLY);
    if (file == -1)
    {
        perror("Can't read file");
        return NULL;
    }
    buffer = malloc(120);
    if (!buffer)
    {
        close(file);
        return NULL;
    }
    read(file, buffer, 120);
    while (buffer[p] != ' ')
        p++;
    buffer[p] = '\0';

    close(file);
    return buffer;
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @var_name: The environmental variable to search for.
 * @var_name_len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found, an empty string.
 *         Otherwise, the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *var_name, int var_name_len)
{
    char **var_addr;
    char *value = NULL, *temp, *var;

    var = malloc(var_name_len + 1);
    if (!var)
        return NULL;
    var[0] = '\0';
    _strncat(var, var_name, var_name_len);

    var_addr = _getenv(var);
    free(var);
    if (var_addr)
    {
        temp = *var_addr;
        while (*temp != '=')
            temp++;
        temp++;
        value = malloc(_strlen(temp) + 1);
        if (value)
            _strcpy(value, temp);
    }

    return value;
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exit_status: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and environmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exit_status)
{
    int i, k = 0, var_name_len;
    char *replacement = NULL, *old_line = NULL, *new_line;

    old_line = *line;
    for (i = 0; old_line[i]; i++)
    {
        if (old_line[i] == '$' && old_line[i + 1] && old_line[i + 1] != ' ')
        {
            if (old_line[i + 1] == '$')
            {
                replacement = get_pid();
                k = i + 2;
            }
            else if (old_line[i + 1] == '?')
            {
                replacement = _itoa(*exit_status);
                k = i + 2;
            }
            else if (old_line[i + 1])
            {
                /* extract the variable name to search for */
                for (k = i + 1; old_line[k] && old_line[k] != '$' && old_line[k] != ' '; k++)
                    ;
                var_name_len = k - (i + 1);
                replacement = get_env_value(&old_line[i + 1], var_name_len);
            }
            new_line = malloc(i + _strlen(replacement) + _strlen(&old_line[k]) + 1);
            if (!new_line)
                return;
            new_line[0] = '\0';
            _strncat(new_line, old_line, i);
            if (replacement)
            {
                _strcat(new_line, replacement);
                free(replacement);
                replacement = NULL;
            }
            _strcat(new_line, &old_line[k]);
            free(old_line);
            *line = new_line;
            old_line = new_line;
            i = -1;
        }
    }
}

