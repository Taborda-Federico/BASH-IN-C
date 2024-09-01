/* Ejecuta comandos simples y pipelines.
 * No toca ningún comando interno.
 */

#ifndef EXECUTE_H
#define EXECUTE_H

#include "command.h"


void execute_pipeline(pipeline apipe);
/*
 * Ejecuta un pipeline, identificando comandos internos, forkeando, y
 *   redirigiendo la entrada y salida. puede modificar `apipe' en el proceso
 *   de ejecución.
 *   apipe: pipeline a ejecutar
 * Requires: apipe!=NULL
 */

void execute_command(scommand cmd);
//Función auxiliar para ejecutar un comando simple


char **scommand_to_argv(scommand cmd);
//Función auxiliar para crear un arreglo de cadena de caracteres para así poder usar execvp dado las exigencias de su sintaxis


void free_memory_scommand_to_argv(char**killme);
//Función auxiliar para liberar la memoria de scommand_to_argv


void execute_with_pipe(scommand cmd, int input_fd, int output_fd);
//Función auxiliar para ejecutar un comando con redirección de entrada/salida y pipes


void execute_background(pipeline apipe);
// Función auxiliar para manejar la ejecución en segundo plano

void setup_redirection(scommand cmd);
// Función auxiliar para configurar redirecciones de entrada y salida
#endif /* EXECUTE_H */
