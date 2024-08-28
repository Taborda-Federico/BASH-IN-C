#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#include "command.h"

bool builtin_is_internal(scommand cmd) {
    
    assert(cmd != NULL);
    bool check = false;
    char *str = scommand_front(cmd);
    if (strcmp(str, "cd") == 0 
    || strcmp(str, "help") == 0 
    || strcmp(str, "exit") == 0) {
        check = true;
    }
    return check;
}

bool builtin_alone(pipeline p) {

    assert(p != NULL);
    bool check = false;
    if (pipeline_length(p) == 1 && builtin_is_internal(pipeline_front(p))) {
        check = true;
    }
    return check;
}
/*
 * Indica si el pipeline tiene solo un elemento y si este se corresponde a un
 * comando interno.
 *
 * REQUIRES: p != NULL
 *
 * ENSURES:
 *
 * builtin_alone(p) == pipeline_length(p) == 1 &&
 *                     builtin_is_internal(pipeline_front(p))
 *
 *
 */

void builtin_run(scommand cmd) {


    if (builtin_is_internal(cmd)) {
        char *str = scommand_front(cmd);
        if (strcmp(str, "cd") == 0) {
            if (scommand_length(cmd) > 1) { 
                chdir(g_list_nth_data(cmd->arguments, 1));
            } else {
                fprintf(stderr, "cd: incomplete argument");
            }
        } else if (strcmp(str, "help") == 0) {
            printf("Mybash\n");
            printf("Authors: Lautaro Deco, Torres Tomas, Federico Taborda, Nehuen Guevara\n");
            printf("Internal commands:\n");
            printf("cd <dir> - Change directory\n");
            printf("help - Display this help message\n");
            printf("exit - Exit the shell\n");
        } else if (strcmp(str, "exit") == 0) {
            exit(0);
        }
    }
}
/*
 * Ejecuta un comando interno
 *
 * REQUIRES: {builtin_is_internal(cmd)}
 *
 */


