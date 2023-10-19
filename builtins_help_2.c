#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 *help_env - Display information on the shellby builtin command 'env'.
 */

void help_env(void)
{
   char *msgs = "env: env\n\tPrints the current environment.\n";

   write(STDOUT_FILENO, msgs, _strlens(msgs));
}

/**
 * help_setenv - Display information on the shellby builtin command 'setenv'.
 */

void help_setenv(void)
{
   char *msgs = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

   write(STDOUT_FILENO, msgs, _strlens(msgs));
   msgs = "environment variable, or modifies an exiting one. \n\n";
   write(STDOUT_FILENO, msgs, _strlens(msgs));
   msgs = "\tUpon failure, prints a message to stderr.\n";
   write(STDOUT_FILENO, msgs, _strlens(msgs));
}

/**
 * help_unsetenv - Display information on the shellby builtin command
 * unsetenv
 */

void help_unsetenv(void)
{
   char *msgs = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

   write(STDOUT_FILENO, msgs, _strlens(msgs));
   msgs = "environment variable.\n\n\tUpon failure, prints a ";
   write(STDOUT_FILENO, msgs, _strlens(msgs));
   msgs = "message to stderr.\n";
   write(STDOUT_FILENO, msgs, _strlens(msgs));
}
