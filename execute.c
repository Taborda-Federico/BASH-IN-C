#include "execute.h"
#include "builtin.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <glib.h>
#include <signal.h>
#include "command.h"
#include "tests/syscall_mock.h"

// Ejecuta una secuencia de comandos en un pipeline
void execute_pipeline(pipeline apipe) {
    assert(apipe != NULL);

    // Si el pipeline está vacío, no hacer nada
    if (pipeline_is_empty(apipe))
        return;

    // Si solo hay un comando y es interno, ejecutarlo y retornar
    if (builtin_alone(apipe)) {
        builtin_run(pipeline_front(apipe));
        return;
    }

    // Ignorar señales de hijos si no se debe esperar
    if (!pipeline_get_wait(apipe))  // No dejar procesos zombies
        signal(SIGCHLD, SIG_IGN);

    int num_commands = pipeline_length(apipe);
    int prev_fd = -1;  // Descriptor de archivo de entrada previo

    // Arreglo para almacenar los PIDs de los procesos hijos
    int *childpids = malloc(num_commands * sizeof(int)); 
    if (childpids == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_commands; i++) {
        scommand current_command = pipeline_front(apipe);
        int pipefd[2];

        // Crear una tubería si no es el último comando
        if (i < num_commands - 1) {  
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        int pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Proceso hijo
            // Redirigir entrada desde el descriptor previo si es necesario
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Redirigir salida al descriptor de escritura de la tubería si es necesario
            if (i < num_commands - 1) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            // Cerrar todos los descriptores de archivo no utilizados en el hijo
            if (prev_fd != -1) close(prev_fd);
            if (i < num_commands - 1) {
                close(pipefd[0]);
            }

            setup_redirection(current_command);  // Configurar redirecciones de archivos
            execute_command(current_command);  // Ejecutar el comando
            perror("execvp failed");  // Imprimir error si execvp falla
            exit(EXIT_FAILURE);  // Salir si execvp falla
        } else {  // Proceso padre
            childpids[i] = pid;  // Guardar PID del proceso hijo

            // Cerrar descriptores de archivo en el padre que ya no se usan
            if (prev_fd != -1) {
                close(prev_fd);
            }
            if (i < num_commands - 1) {
                close(pipefd[1]);
                prev_fd = pipefd[0];
            }
        }

        pipeline_pop_front(apipe);  // Eliminar el comando ya ejecutado
    }

    // Esperar a todos los procesos hijos si el pipeline se ejecuta en primer plano
    if (pipeline_get_wait(apipe)) {
        int status;
        for (int i = 0; i < num_commands; i++) {
            waitpid(childpids[i], &status, 0);
        }
    }

    free(childpids);  // Liberar memoria del arreglo de PIDs
}

void execute_command(scommand cmd) {
    assert(cmd != NULL);

    char *cmd_name = scommand_front(cmd);
    char **args = scommand_to_argv(cmd);  // Convierte el comando a un arreglo de argumentos

    execvp(cmd_name, args);  // Reemplaza el proceso actual con el comando a ejecutar
    perror("execvp failed");  // Imprimir error si execvp falla
    free_memory_scommand_to_argv(args);  // Liberar memoria
    exit(EXIT_FAILURE);  // Salir si execvp falla
}

char **scommand_to_argv(scommand cmd) {
    assert(cmd != NULL);

    unsigned int scommand_len = scommand_length(cmd);
    char **argv = calloc(scommand_len + 1, sizeof(char *));  // Asignar memoria para el arreglo de argumentos

    unsigned int i = 0;
    while (!scommand_is_empty(cmd)) {
        unsigned int length_com = strlen(scommand_front(cmd)) + 1;
        argv[i] = malloc(length_com * sizeof(char));  // Asignar memoria para cada argumento
        strcpy(argv[i], scommand_front(cmd));  // Copiar el argumento al arreglo
        scommand_pop_front(cmd);  // Eliminar el argumento del comando
        ++i;
    }

    return argv;
}

void free_memory_scommand_to_argv(char **args) {
    unsigned int i = 0;
    while (args[i] != NULL) {
        free(args[i]);  // Liberar cada argumento
        i++;
    }
    free(args);  // Liberar el arreglo de argumentos
}

void setup_redirection(scommand cmd) {
    char* filename_in = scommand_get_redir_in(cmd);
    if (filename_in) {
        int in_redir = open(filename_in, O_RDONLY, S_IRWXU); 
        close(STDIN_FILENO);   // Cerrar STDIN_FILENO antes de redirigir
        dup(in_redir);  // Redirigir entrada a archivo
        close(in_redir);
    }
    
    char* filename_out = scommand_get_redir_out(cmd);
    if (filename_out) {
        int out_redir = open(filename_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);  // Abrir archivo para redirección de salida
        close(STDOUT_FILENO);  // Cerrar STDOUT_FILENO antes de redirigir
        dup(out_redir);  // Redirigir salida a archivo
        close(out_redir);
    }
}
