#include "shell.h"

int num_lens(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_lens - Create the digit length of a number.
 @num: The number to measure.
 * 
 * Return: The digit length
 */

int num_lens(int num)
{
        unsigned int num1;
        int lens = 1;

        if(num < 0)
        {
                lens++;
                num1 = num * -1;
        }
        else
        {
                num1 = num;
        }
        while(num1 > 9)
        {
                lens++;
                num1 /= 10;
        }

        return(lens);
}

/**
 * _itoa _ Converts an integer to a string.
 * @num: The integer
 *
 * Return: The converted string.
 */

char *_itoa(int num)
{
        char *buffer;
        int lens = num_lens(num);
        unsigned int num1;

        buffer = malloc(sizeof(char) * (lens + 1));
        if(!buffer)
                return(NULL);
        
        buffer[lens] = '\0';

        if(num < 0)
        {
                num1 = num * -1;
                buffer[0] = '-';
        }
        else 
        {
                num1 = num;
        }

        lens--;
        do {
                buffer[lens] = (num1 % 10) + '0';
                num1 /= 10;
                lens--;
        } while (num1 > 0);

        return(buffer);
}

/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */

int create_error(char **args, int err)
{
        char *error;
        
        switch(err)
        {
        case -1: 
                error = error_env(args);
                break;
        case 1:
                error = error_1(args);
                break;
        case 2:
                if(*(args[0]) == 'e')
                        error = error_2_exit(++args);
                else if(args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
                        error = error_2_syntax(args);
                else
                        error = error_2_cd(args);
                break;
        case 126:
                error = error_126(args);
                break;
        case 127:
                error = error_127(args);
                break;
        }
        write(STDRR_FILENO, error, _strlen(error));
        
        if(error)
                free(error);
        return(err);
}
