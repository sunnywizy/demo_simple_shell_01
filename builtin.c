#include "shell.h"

int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding shellby builtin function.
 * @command: The command to match.
 * 
 * Return: A function pointer to the corresponding builtin.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
    builtin_t funcs[] = {
        { "exit", shellby_exit },
        { "env", shellby_env },
        { "setenv", shellby_setenv },
        { "unsetenv", shellby_unsetenv },
        { "cd", shellby_cd },
        { "alias", shellby_alias },
        { "help", shellby_help },
        { NULL, NULL}
    };

    int n;
    
    for(n = 0; funcs[n].name; n++)
    {
        if(_strcmps(funcs[n].name, command) == 0)
                break;
    }
    return(funcs[n].f);
}

/** 
 * shellby_exit - Causes normal process termination for the shellbt=y shell.
 * @args: An array of arugments containing the exit value.
 * @front: Adouble pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
            If the given exit  value is invalid -2
            O/W - exits with the given status value.
 * Description: Upon returning -3, the program exits back in the main function
 */

int shellby_exit(char **args, char **front)
{
    int n, lens_of_int = 10;
    unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

    if(args[0])
    {
        if(args[0][0] == '+')
        {
            n = 1;
            lens_of_int++;
        }
        for(; args[0][n]; n++)
        {
            if(n <= lens_of_int && args[0][n] >= '0' && args[0][n] <= '9')
                    num = (num * 10) + (args[0][n] - '0');
            else   
                    return(create_error(--args, 2));
        }
    }
    else
    {
        return(-3);
    }
    
    if(num > max - 1)
            return(create_error(--args, 2));
    
    args -= 1;
    free_args(args, front);
    free_env();
    free_alias_list(aliases);
    exit(num);
}

/**
 * shellby_cd Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * 
 * Return: If the given strings is not a directory -2 .
            If an error occurs - -1.
            Otherwise - 0.
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{
    char **dir_info, *new_line = "\n";
    char *oldpwd = NULL, *pwd = NULL;
    struct stat dir;

    oldpwd = getcwd(oldpwd, 0);
    if(!oldpwd)
            return(-1);

    if(args[0])
    {
        if(*(args[0]) == '-' || _strcmps(args[0], "--") == 0)
        {
            if((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
            {
                if(_getenv("OLDPWD") != NULL)
                        (chdir(*_getenv("OLDPWD") + 7));
            }
            else
            {
                free(oldpwd);
                return(create_error(args, 2));
            }
        }
        else
        {
            if(stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) && ((dir.st_mode & S_IWUSR) != 0))
                    chdir(args[0]);
            else
            {
                free(oldpwd);
                return(create_error(args, 2));
            }
        }
    }
    else 
    {
        if(_getenv("HOME") != NULL)
                chdir(*(_getenv("HOME")) + 5);
    }

    pwd =getcwd(pwd, 0);
    if(!pwd)
            return(-1);
    
    dir_info = malloc(sizeof(char *) * 2);
    if(!dir_info)
            return(-1);
    
    dir_info[0] = "OLDPWD";
    dir_info[1] = oldpwd;
    if(shellby_setenv(dir_info, dir_info) == -1)
            return(-1);
    
    dir_info[0] = "PWD";
    dir_info[1] = pwd;
    if(shellby_setenv(dir_info, dir_info) == -1)
            return(-1);
    if(args[0] && args[0][0] == '-' && args[0][1] != '-')
    {
        write(STDOUT_FILENO, pwd, _strlens(pwd));
        write(STDOUT_FILENO, new_line, 1);
    }

    free(oldpwd);
    free(pwd);
    free(dir_info);
    return(0);
}

/**
 * shellby_help - Displays information about shellby builtin commands.
 * @args: Anarray of arguments.
 *
 * Return: If an error ouccurs - -1.
            Otherwise - 0
 */

int shellby_help(char **args, char __attribute__((__unused__)) **front)
{
    if(!args[0])
            help_all();
    else if(_strcmps(args[0], "alias") == 0)
            help_alias();
    else if(_strcmps(args[0], "cd") == 0)
            help_cd();
    else if(_strcmps(args[0], "exit") == 0)
            help_exit();
    else if(_strcmps(args[0], "env") == 0)
            help_env();
    else if(_strcmps(args[0], "setenv") == 0)
            help_setenv();
    else if(_strcmps(args[0], "unsetenv") == 0)
            help_unsetenv();
    else if(_strcmps(args[0], "help") == 0)
            help_help();
    else
            write(STDERR_FILENO, name, _strlens(name));
    
    return(0);
}
