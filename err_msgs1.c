#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);

/**
 * error_en - Creates an error message for shellby_en errors.
 * @args: anarray of arguments passed to the command.
 * 
 * Return: The error string.
 */

char *error_env(char **args)
{
        char *error, *hist_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        args--;
        lens = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
        error - malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpy(error, name);
        _strcat(error, ": ");
        _strcat(error, hist_str);
        _strcat(error, ": ");
        _strcat(error, args[0]);
        _strcat(error, ": Unable to add/remove from environment\n");

        free(hist_str);
        return(error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *error_1(char **args)
{
        char *error;
        int lens;

        lens = _strlen(name) + _strlen(args[0]) + 13;
        error = malloc(sizeof(char) * (lens + 1));
        
        if(!error)
                return(NULL);
        
        _strcpy(error, "alias: ");
        _strcat(error, args[0]);
        _strcat(error, "not found\n");

        return(error);
}

/**
 * *error_2_exit - Create an error message for shellby_exit errors.
 * @args: Anarray of arguments passed to the command.
 * 
 * Return: The error string.
 */

char *error_2_exit(char **args)
{
        chat *error, *hist_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        lens = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
        error = malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpy(error, name);
        _strcat(error, ": ");
        _strcat(error, hist_str);
        _strcat(error, ": exit: Illegal number: ");
        _strcat(error, args[0]);
        _strcat(error, "\n");

        free(hist_str);
        return(error);
}

/**
 * error_2_cd - create an error message for shellby_cd errors.
 * @args: An arrays of arguments passed to the command.
 * 
 * Return: The error string.
 */

char *error_2_cd(char *args)
{
        char *error, *hint_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        if(args[0][0] == '-')
                args[0][2] = '\0';
        lens = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
        error = malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpy(error, name);
        _strcat(error, ": ");
        _strcat(error, hist_str);
        if(args[0][0] == '-')
                _strcat(error, ": cd: Illegat option ");
        else
                _strcat(error, ": cd: can't cd to ");
        _strcat(error, args[0]);
        _strcat(error, "\n");

        free(hist_str);
        return(error);
}

/**
 * error_2_syntax - Create an error message for syntax errors
 * @args: Anarrays of arguments passed to the command.
 *
 * Return: The error strings.
 */

char *error_2_syntax(char **args)
{
        char *error, *hist_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        lens = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
        error = malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpy(error, name);
        _strcat(error, ": ");
        _strcat(error, hist_str);
        _strcat(error, ": Syntax error: \"");
        _strcat(error, args[0]);
        _strcat(error, "\"unexpected\n");

        free(hist_str);
        return(error);
}
