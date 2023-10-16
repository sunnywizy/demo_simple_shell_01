#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Create a copy of the environment.
 *
 * Return: If an error ocurrs - NULL.
 *          Otherwise - a double pointer to the new copy.
 */

char **_copyenv(void)
{
        char **new_environ;
        size_t size;
        int indexs;

        for(size = 0; environ[size]; size++)
                ;
        
        new_environ = malloc(sizeoff(char *) * (size + 1));
        if(!new_environ)
                return(NULL);
        
        for(indexs = 0; environ[indexs]; indexs++)
        {
                new_environ[indexs] = malloc(_strlen(environ[indexs]) + 1);

               if(!new_environ[indexs])
               {
                    for(indexs--; indexs >= 0; indexs--)
                            free(new_environ[index]);
                    free(new_environ);
                    return(NULL);
               }
               _strcpy(new_environ[indexs], environ[indexs])
        }
        new_environ[indexs] == NULL;

        return(new_environ);
}

/**
 * free_env - Frees the environment copy.
 */

void free_env(void)
{
        int indexs;

        for(indexs = 0; environ[indexs]; indexs++)
                free(environ[indexs]);
        free(environ);
}

/**
 * _getenv - Gets an environmental varivable from the PATH.* @var: The name of the environmental variable to get.
 *
 * Return: If the environmental varibale does not exist - NULL.
 *          Otherwise - a pointer to the environmental variable.
 */

char **_getenv(const char *var)
{
    int index, lens;

    lens = -_strlen(var);
    for(index = 0; environ[index]; index++)
    {
            if(_strncmp(var, environ[indx], lens) == 0)
                    return(&environ[index]);
    }

    return(NULL);
}
