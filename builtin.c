#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "builtin.h"
#include "command.h"
// cd help exit
bool builtin_is_internal(scommand cmd)
{

    assert(cmd != NULL);
    bool check = false;
    char *str = scommand_front(cmd);            
    if ((str !=NULL) && (strcmp(str, "cd") == 0 || strcmp(str, "help") == 0 || strcmp(str, "exit") == 0))  // Faltaba verificar que *str no sea NULL (caso borde) 
    {
        check = true;
    }
    return check;
}

bool builtin_alone(pipeline p)
{

    assert(p != NULL);
    bool check = false;
    if (pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p)))
    {
        check = true;
    }
    return check;
}

void builtin_run(scommand cmd)
{
    assert(builtin_is_internal(cmd));
    char *str = scommand_front(cmd);
    if (strcmp(str, "cd") == 0)
    {
        if (scommand_length(cmd) > 1)
        {
            scommand_pop_front(cmd);
            if(chdir(scommand_front(cmd))){  //Aca rompimos sentido de encapsulamiento: ANTERIOR-->> g_list_nth_data(cmd->arguments, 1)
                perror("cd");
            }    
        }
        else
        {
            fprintf(stderr, "cd: missing argument. Usage: cd <directory>\n");
        }
    }
    else if (strcmp(str, "help") == 0)
    {
        printf("Mybash\n");
        printf("Authors: Lautaro Deco, Torres Tomas, Federico Taborda, Nehuen Guevara\n");
        printf("Internal commands:\n");
        printf("cd <dir> - Change directory\n");
        printf("help - Display this help message\n");
        printf("exit - Exit the shell\n");
    }
    else if (strcmp(str, "exit") == 0)
    {
        exit(0);
    }
}
