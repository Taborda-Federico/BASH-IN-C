#include <stdlib.h>
#include <stdbool.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

static scommand parse_scommand(Parser p) {
    scommand cmd = scommand_new();
    arg_kind_t type_arg;
    char* arg;

    while (!parser_at_eof(p)) {
        arg = parser_next_argument(p, &type_arg);

        if (arg != NULL) {
            switch  (type_arg) {
                case ARG_NORMAL:
                    scommand_push_back(cmd, arg);
                    break;
                case ARG_INPUT:
                    scommand_set_redir_in(cmd, arg);
                    break;
                case ARG_OUTPUT:
                    scommand_set_redir_out(cmd, arg);
                    break;
            }
        } else if  (type_arg == ARG_INPUT || type_arg == ARG_OUTPUT) {
            return NULL;
        } else {
            break;
        }
    }

    return cmd;
}


pipeline parse_pipeline(Parser p) {
    pipeline result = pipeline_new();
    scommand cmd = NULL;
    bool error = false, another_pipe=true;

    cmd = parse_scommand(p);
    error = (cmd==NULL); /* Comando inválido al empezar */
    while (another_pipe && !error) {

        pipeline_push_back(result,cmd);
        bool found_pipe;
        parser_op_pipe(p,&found_pipe);
            if (found_pipe) {
                cmd = parse_scommand(p);
                error = (cmd == NULL);
            } else {
                another_pipe = false;
            }
        }
    //  Manejo del operador de background, si existe
    if (!error) {
        bool is_background;
        parser_op_background(p, &is_background);
        pipeline_set_wait(result, !is_background);
    }


    // Si hubo error, hacemos cleanup
    // Limpieza en caso de error
    if (error) {
        pipeline_destroy(result);
        result = NULL;
    }

    // Tolerancia a espacios posteriores
    // Consumir todo lo que hay inclusive el \n
    bool garbage;
    parser_garbage(p, &garbage);

    if (pipeline_length(result) == 1 && scommand_length(pipeline_front(result)) == 0) {
        pipeline_destroy(result);
        return NULL;
    }

    if (garbage) {
        printf("Error: invalid command.\n");
        pipeline_destroy(result);
        return NULL;
    }
    return result;
}

