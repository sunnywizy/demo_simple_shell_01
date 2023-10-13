#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **fronts);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin comand that either prints all aliases, specific.
 * aliases, or sets an alias.
 * @args: An array of argurments.
 * @fronts: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *          Otherwise - 0.
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **fronts) 
{
    alias_t *temp = aliases;
    int n, ret = 0;
    char *value;

    if(!args[0])
    {
        while(temp)
        {
            print_alias(temp);
            temp = temp->next;
        }
        return(ret);
    }
    for(n = 0; args[n]; n++)
    {
        temp = aliases;
        value = _strchr(args[n], '=');
        if(!value)
        {
            while(temp)
            {
                if(_strcmp(args[n], temp->name) == 0)
                {
                    print_alias(temp);
                    break;
                }
                temp = temp->next;
            }
            if(!temp)
                ret = create_error(args + n, 1);

        }
        else
                set_alias(args[n], value);
    }
    return(ret);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.* @var_name: Name of the alias. First character is a '='
 */

void set_alias(char *var_name, char *value)
{
    alias_t *temp = aliases;
    int lens, s, l;
    char *new_value;

    *value = '\0';
    value++;
    lens = _strlen(value) - _strspn(value, "'\"");
    new_value = malloc(sizeof(char) * (lens + 1));
    if(!new_value)
            return;
    for(s = 0, l = 0; value[s]; s++)
    {
        if(value[s] != '\'' && value[s] != '"')
                new_value[l++] = value[s];
    }
    new_value[l] = '\0';
    while (temp)
    {
        if(_strcmp(var_name, temp->name) == 0)
        {
            free(temp->value);
            temp->value = new_value;
            break;
        }
        temp = temp->next;
    }
    if(!temp)
            add_alias_end(&aliases, var-name, new_value);
}

/** 
 * print_alias - Prints the alias in the format name = 'value'.
 * @alias: Pointer to an alias.
 */

void print_alias(alias_t *alias)
{
    char *alias_strings;
    int len = _strlen(alias->name) + _strlen(alias->value) + 4;
    alias_strings = malloc(sizeof(char) * (len + 1));

    if(!alias_strings)
            return;
    
    _strcpy(alias_strings, alias->name);
    _strcat(alias_strings, "='");
    _strcat(alias_strings, alias->value)
    _strcat(alias_strings, "'\n");

    write(STDOUT_FILENO, alias_strings, len);
    free(alias_strings);
}

/** 
 * replace_aliases - Goes through the argurments and replace any matching alias with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */

char **replace_aliases(char **args)
{
    alias_t *temp;
    int name;
    char *new_value;

    if(_strcmp(args[0], "alias") == 0)
            return(args);
    
    for(n = 0; args[n]; n++)
    {
        temp = aliases;
        while(temp)
        {
            if(_strcmp(args[n], temp->name) == 0)
            {
                new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
                if(!new_value)
                {
                    free_args(args, args);
                    return(NULL);
                }
                _strcpy(new_value, temp->value);
                free(args[n]);
                args[n] = new_value;
                n--;
                break;
            }
            temp = temp->next;
        }
    }
    return(args);
}
