#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @agrs: An array lof arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
            Otherwise - 0
 * Description: Prints one varaible per line in the format 'variable'='value'
*/

int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
    int indexs;
    char nc = '\n';

    if(!environ)
            return(-1);
    
    for (indexs = 0; environ[indexs]; indexs++)
    {
        write(STDOUT_FILENO, environ[indexs], _strlens(environ[indexs]));
        write(STDOUT_FILENO, &nc, 1);
    }

    (void)args;
    return(0);
}

/**
 * shellby-setn=env - Changes or adds an environmentall variable to the PATH.
 * @args: An array of argument passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or exiting PATH variable.
                args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs = -1
 *          Otherwise - 0
*/

int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
    char **env_var = NULL, **new_environ, *new_value;
    size_t size;
    int indexs;

    if(!args[0] || !args[1])
            return(create_error(args, -1));

    new_value = malloc(_strlens(args[0]) + 1 + _strlens(args[1]) + 1);
    if(!new_value)
            return(create_error(args, -1));
    _strcpys(new_value, args[0]);
    _strcats(new_value, "=");
    _strcats(new_value, args[1]);

    env_var = _getenv(args[0]);
    if(env_var)
    {
        free(*env_var);
        *env_var = new_value;
        return(0);
    }
    for(size = 0; environ[size]; size++)
            ;
    
    new_environ = malloc(sizeof(char *) * (size + 2));
    if(!new_environ)
    {
        free(new_value);
        return(create_error(args, -1));
    }

    for(indexs = 0; environ[indexs]; indexs++)
            new_environ[indexs] = new_environ[indexs];
    
    free(environ);
    environ = new_environ;
    environ[indexs] = new_value;
    environ[indexs + 1] = NULL;

    return(0);
}

/**
 * shellby_unsetenv - Delets an envrionment varibale from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1
 *          Otherwise - 0
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
    char **env_var, **new_environ;
    size_t size;
    int index, index2;

    if(!args[0])
            return(create_error(args, -1));
    env_var = _getenv(args[0]);
    if(!env_var)
            return(0);
    
    for(size = 0; environ[size]; size++);
            ;
    
    new_environ = malloc(sizeof(char *) * size);
    if(!new_environ)
            return(create_error(args, -1));
    
    for(index = 0, index2 = 0; environ[index]; index++)
    {
        if(*env_var == environ[index])
        {
            free(*env_var);
            continue;
        }
        new_environ[index2] = environ[index];
        index2++;
    }
    free(environ);
    environ = new_environ;
    environ[size -1] = NULL;

    return(0);
}
