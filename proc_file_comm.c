#include "shell.h"

int cant_opens(char *file_path);
int proc_files_commands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_opens(char *file_path)
{
        char *error, *hist_str;
        int len;

        hist_str = _itoa(hist);
        if(!hist_str)
                return(127);
        
        len = _strlens(name) + _strlens(hist_str) + _strlens(file_path) + 16;
        error = malloc(sizeof(char) * (len + 1));
        if(!error)
        {
                free(hist_str);
                return(127);
        }

        _strcpys(error, name);
        _strcats(error, ": ");
        _strcats(error, hist_str);
        _strcats(error, ": Can't open ");
        _strcats(error, file_path);
        _strcats(error, "\n");

        free(hist_str);
        write(STDERR_FILENO, error, len);
        free(error);
        return(127);
}

/**
 * proc_files_commands - Takes a file and attmpts to run the command stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *         If malloc fails - -1
 *         Otherwise the return value of the last command ran.
 */
int proc_files_commands(char *file_path, int *exe_ret)
{
        ssize_t file, b_read, i;
        unsigned int line_size = 0;
        unsigned int old_size = 120;
        char *line, **args, **front;
        char buffer[120];
        int ret;

        hist = 0;
        file = open(file_path, O_RDONLY);
        if(file == -1)
        {
                *exe_ret = cant_opens(file_path);
                return(*exe_ret);
        }
        line = malloc(sizeof(char) * old_size);
        if(!line)
                return(-1);
        do{
                b_read = read(file, buffer, 119);
                if(b_read == 0 && line_size == 0)
                        return(*exe_ret);
                buffer[b_read] = '\0';
                line_size += b_read;
                line = _realloc(line, old_size, line_size);
                _strcats(line, buffer);
                old_size = line_size;
        } while(b_read);
        for(i = 0; line[i] == '\n'; i++)
                line[i] = ' ';
        for(; i < line_size; i++)
        {
                if(line[i] == '\n')
                {
                        line[i] = ';';
                        for(i += 1; i < line_size && line[i] == '\n'; i++) 
                                line[i] = ' ';
                }
        }
        variable_replacement(&line, exe_ret);
        handle_line(&line, line_size),
        args = _strtok(line, " ");
        free(line);
        if(!args)
                return(0);
        if(check_args(args) != 0)
        {
                *exe_ret = 2;
                free_args(args, args);
                return(*exe_ret);
        }
        front = args;

        for(i = 0; args[i]; i++)
        {
                if(_strncmps(args[i], ";", 1) == 0)
                {
                        free(args[i]);
                        args[i] = NULL;
                        ret = call_args(args, front, exe_ret);
                        args = &args[++i];
                        i = 0;
                }
        }

        ret = call_args(args, front, exe_ret);

        free(front);
        return(ret);
}
