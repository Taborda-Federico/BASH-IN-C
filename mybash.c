#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "command.h"
#include "execute.h"
#include "parser.h"
#include "parsing.h"
#include "builtin.h"
#include "obfuscated.h"
#include <glib.h>

static void show_prompt(void) {
    printf ("mybash:%s> ",g_get_current_dir());
    fflush (stdout);
}

int main(int argc, char *argv[]) {
    pipeline pipe;
    Parser input;
    bool quit = false;
    char * pass = "NavyBluePeacock";
    input = parser_new(stdin);// Inicializa el parser para leer comandos de stdin; 
    
     if (input == NULL) {
        fprintf(stderr, "Error: faloo en inicializar el parser.\n");
        return EXIT_FAILURE;
    }
    
    while (!quit) {
        ping_pong_loop(pass);  // No more delays :)
        show_prompt();         // Muestra el prompt
        pipe = parse_pipeline(input); // Analiza el input y crea el pipeline
         if (pipe == NULL) {
            fprintf(stderr, "Error: en analizar pipe lines\n");
            continue;
        }
        if (pipe != NULL && !pipeline_is_empty(pipe)) { 
            // Verifica si hay que salir (ejemplo: el comando es 'exit')
            scommand first_command = pipeline_front(pipe);
            if (builtin_is_internal(first_command) && strcmp(scommand_front(first_command), "exit") == 0) {
                quit = true;  // Si es el comando 'exit', establece quit en true
            } else {
                execute_pipeline(pipe);  // Ejecuta el pipeline de comandos
            }
            pipeline_destroy(pipe);  // Limpia el pipeline después de su ejecución
        }

        // Verifica si es necesario salir del shell
        quit = quit || parser_at_eof(input);
    }

    parser_destroy(input); // Libera recursos del parser
    return EXIT_SUCCESS;
}

