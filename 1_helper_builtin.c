#include "main.h"

/**
 * display_all_commands - Displays all possible builtin Shellby commands.
 */
void display_all_commands(void)
{
    char *mess = "Shellby\nThese shell commands are defined internally.\n";

    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "Type 'help' to see this list.\nType 'help name' to find ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "out more about the function 'name'.\n\n  alias   \t";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "unsetenv [VARIABLE]\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * display_alias_help - Displays information on the Shellby builtin command 'alias'.
 */
void display_alias_help(void)
{
    char *mess = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "\n\talias: Prints a list of all aliases, one per line, in ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " the aliases name, name2, etc. one per line, in the ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " an alias for each NAME whose VALUE is given. If NAME ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "is already an alias, replace its value with VALUE.\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * display_cd_help - Displays information on the Shellby builtin command 'cd'.
 */
void display_cd_help(void)
{
    char *mess = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "command is interpreted as cd $HOME. If the argument '-' is";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " given, the command is interpreted as cd $OLDPWD.\n\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "\tThe environment variables PWD and OLDPWD are updated ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "after a change of directory.\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * display_exit_help - Displays information on the Shellby builtin command 'exit'.
 */
void display_exit_help(void)
{
    char *mess = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "STATUS argument is the integer used to exit the shell.";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " If no argument is given, the command is interpreted as";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = " exit 0.\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
}

/**
 * display_help_help - Displays information on the Shellby builtin command 'help'.
 */
void display_help_help(void)
{
    char *mess = "help: help\n\tSee all possible Shellby builtin commands.\n";

    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
    write(STDOUT_FILENO, mess, _strlen(mess));
    mess = "builtin command.\n";
    write(STDOUT_FILENO, mess, _strlen(mess));
}

