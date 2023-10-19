#include "shell.h"

char *error_126(char ** args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command
 *
 * Return: The error string.
 */

char *error_126(char **args)
{
        char *error, *hist_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        lens = _strlens(name) + _strlens(hist_str) + _strlens(args[0]) + 24;
        error = malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpys(error, name);
        _strcats(error, ": ");
        _strcats(error, hist_str);
        _strcats(error, ": ");
        _strcats(error, args[0]);
        _strcats(error, ": Permission denied\n");

        free(hist_str);
        return(error);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *error_127(char **args)
{
        char *error, *hist_str;
        int lens;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(NULL);
        
        lens = _strlens(name) + _strlens(hist_str) + _strlens(args[0]) + 16;
        error = malloc(sizeof(char) * (lens + 1));
        if(!error)
        {
                free(hist_str);
                return(NULL);
        }

        _strcpys(error, name);
        _strcats(error, ": ");
        _strcats(error, hist_str);
        _strcats(error, ": ");
        _strcats(error, args[0]);
        _strcats(error, ": not found\n");

        free(hist_str);
        return(error);
}
