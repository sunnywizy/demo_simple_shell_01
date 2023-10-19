#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Display a possible builtin shelby commands
*/

void help_all(void)
{
    char *msgs = "Shellby\nThese shell commands are defined internally.\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "Type 'help' to see this list.\nType 'help name' to find";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "out more about the function 'name'.\n\n alias \t";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "alias [NAME[='VALUE']...]\n cd \tcd  ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "[DIRECTORY]\n exit     \texit [STATUS]\n env     \tenv";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "\n setenv  \tsetenv [VARIABLE] [VALUE]\n unsetenv\t";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "unsetenv [VARIABLE]\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
}

/**
 * help_alias - Display information on the shellby builtin command 'alias'.
 */

void help_alias(void)
{
    char *msgs = "alias: alias [NAME[='VALUE']...]\n\tHandles aliases.\n";

    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "\n\talias: Prints a list of all aliases, one per line, in ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " the aliases name, name2, etc. one per line, in the ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "from NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " an alias for each NAME whose VALUE is given. if NAME ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "is already an alias, replace its value with VALUE.\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
}

 /**
  * help_cd - Display information on the shellby builtin command 'cd'.
  */

void help_cd(void)
{
    char *msgs = "cd: cd [DIRECTORY]\n\tChanges the current dierctory of the";

    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "command is interpreted as cd $HOME. If the argument '-' is";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " given, the command is interpreted as cd $OLDPWD.\n\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "\tThe environment varibles PWD abd OLDPWD are updated ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "after a change of directory.\n";
}

/**
 * help_exit - Displays information on the shellby builtin command 'eixt'
 */

void help_exit(void)
{
    char *msgs = "exit: exit [STATUS]\n\texits the shell.'n'n'tThe ";

    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "STATUS argument is the integer used to exit the shell.";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " If no argument is given, the cmaonnd is intrepreted as";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = " exit 0.\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
}

/** 
 * help_help - Display information on the shellby builtin command 'help'.
 */

void help_help(void)
{
    char *msgs = "help: help\n\tSee all possible Shellby builtin commands.\n";

    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "\n      help[BUILTIN NAME]\n\tSee specific information on each ";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
    msgs = "builtin command.\n";
    write(STDOUT_FILENO, msgs, _strlens(msgs));
}
