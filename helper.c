#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *begnning, int lens);
void variabale_replacement(char **args, int * exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @fronts: a double pointer to the beginnning of args.
 */
void free_args(char **args, char **front)
{
        size_t i;

        for(i = 0; args[i] || args[i + 1]; i++)
                free(args[i]);   
        
        free(front);
}

/**
 * get_pif - Gets the current process ID
 * Description: Open the stat file, a space-delimited file containing information about the current process. The pID is the first word in the file. The function reads the PID into a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or FULL on failure.
 */
char *get_pid(void){
        size_t i = 0;
        char *buffer;
        ssize_t file;

        file = open("/proc/self/stat", O_RDONLY);
        if(file == -1)
        {
                perror("Cant read file");
                return(NULL);
        }
        buffer = malloc(120);
        if(!buffer)
        {
                close(file);
                return(NULL);
        }
        read(file, buffer, 120);
        while(buffer[i] != ' ')
                i++;
        buffer[i] = '\0';

        close(file);
        return(buffer);
}

/**
 * get__env_value - Gets the value coresponding to an environmental variable
 * @beginning: The environmental variable to search for.
 * @len: the length of the environmental variable to serach for.
 *
 * Return: If the variable is not found - an empty string.*         Otherwise - The value of the environment variable.
 *
 * Description: Variables aresorted in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
        char **var_addr;
        char *replacement = NULL, *temp, *var;

        var = malloc(len + 1);
        if(!var)
                return(NULL);
        var[0] = '\0';
        _strncats(var, beginning, len);

        var_addr = _getenv(var);
        free(var);
        if(var_addr)
        {
                temp = *var_addr;
                while(*temp != '=')
                        temp++;
                temp++;
                replacement = malloc(_strlens(temp) + 1);
                if(replacement)
                        _strcpys(replacement, temp);
        }

        return(replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and aguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 * Description: Replaces $$ with the current PID, $? with the return value of the last executed program, and environmental variables preceded by $ with their corresponding value.
 */
void variabale_replacement(char **line, int *exe_ret)
{
        int j, k = 0, len;
        char *replacement = NULL, *old_line = NULL, *new_line;

        old_line = *line;
        for(j = 0; old_line[j]; j++)
        {
                if(old_line[j] == '$' && old_line[j + 1] && old_line[j + 1] != ' ')
                {
                        if(old_line[j + 1]  == '$')
                        {
                                replacement = get_pid();
                                k = j + 2;
                        }
                        else if (old_line[j + 1] == '?')
                        {
                                replacement = _itoa(*exe_ret);
                                k = j + 2;
                        }
                        else if(old_line[j + 1])
                        {
                                /* extract the variable name to search for */
                                for(k = j + 1; old_line[k] && old_line[k] != '$' && old_line[k] != ' '; k++)
                                        ;
                                len = k - (j + 1);
                                replacement = get_env_value(&old_line[j + 1], len);
                        }
                        new_line = malloc(j + _strlens(replacement) + _strlens(&old_line[k]) + 1);
                        if(!line)
                                return;
                        new_line[0] = '\0';
                        _strncats(new_line, old_line, j);
                        if(replacement)
                        {
                                _strcats(new_line, replacement);
                                free(replacement);
                                replacement = NULL;
                        }
                        _strcats(new_line, &old_line[k]);
                        free(old_line);
                        *line = new_line;
                        old_line = new_line;
                        j = 1;
                }       
        }  
}
