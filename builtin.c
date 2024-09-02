#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "builtin.h"
#include "command.h"
#include "tests/syscall_mock.h"

// Verifica si el comando es uno de los comandos internos válidos
bool builtin_is_internal(scommand cmd) {
    assert(cmd != NULL);
    const char* str = scommand_front(cmd);
    
    // Verificación si el comando es uno de los permitidos: cd, help o exit
    if (str != NULL && (strcmp(str, "cd") == 0 || strcmp(str, "help") == 0 || strcmp(str, "exit") == 0)) {
        return true;
    }
    return false;
}

// Verifica si el pipeline solo contiene un comando interno
bool builtin_alone(pipeline p) {
    assert(p != NULL);
    return (pipeline_length(p) == 1) && builtin_is_internal(pipeline_front(p));
}

// Ejecuta el comando interno
void builtin_run(scommand cmd) {
    assert(builtin_is_internal(cmd));
    const char* command = scommand_front(cmd);

    // Manejo del comando 'cd'
    if (strcmp(command, "cd") == 0) {
        scommand_pop_front(cmd);  // Elimina 'cd' del comando
        
        if (scommand_length(cmd) == 0) {  // Si no hay argumentos, cambiar al directorio de inicio del usuario
            char* user_name = getlogin();  // Obtiene el nombre de usuario
            if (user_name) {
                // Construye el directorio de inicio del usuario
                size_t user_dir_size = strlen("/home/") + strlen(user_name) + 1;
                char* user_dir = malloc(user_dir_size);
                if (user_dir) {
                    snprintf(user_dir, user_dir_size, "/home/%s", user_name);
                    scommand_push_back(cmd, user_dir);  // Agrega el directorio al comando
                }
            }
        }

        // Cambia al directorio especificado en el comando
        if (scommand_length(cmd) > 0) {
            int rc = chdir(scommand_front(cmd));
            if (rc == -1) {
                // Manejo de errores al cambiar de directorio
                switch (errno) {
                case EACCES:
                    printf("Permission denied\n");
                    break;
                case ENOENT:
                    printf("No such file or directory\n");
                    break;
                case ENOTDIR:
                    printf("Not a directory\n");
                    break;
                default:
                    printf("Error change directory\n");
                    break;
                }
            }
        } else {
            fprintf(stderr, "cd: missing argument. Usage: cd <directory>\n");
        }
    } 
    // Manejo del comando 'help'
    else if (strcmp(command, "help") == 0) {
        printf("Mybash\n");
        printf("Authors: Lautaro Deco, Torres Tomas, Federico Taborda, Nehuen Guevara\n");
        printf("Internal commands:\n");
        printf("cd <dir> - Change directory\n");
        printf("help - Display this help message\n");
        printf("exit - Exit the shell\n");
    } 
    // Manejo del comando 'exit'
    else {
        exit(EXIT_SUCCESS);
    }
}
