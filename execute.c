#include "execute.h"
#include "builtin.h"
#include <stdio.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include "command.h"


/*FALTA: Ver la forma de que no se necesite esta estructura aca para que lea de manera adecuada el codigo
Correjir en builtin_run la ejecución del exit, no sale de mybash al ejecutar
Evaluar porque demora tanto en aparecer "mybash>" cuando se activa la terminal y luego al ejecutar
Leaks de memoria revisar, de donde provienen.
*/
struct scommand_s {
    GList *arguments;  // lista de argumentos del comando (lista de gchar*)
    char* input;      // archivo de entrada 
    char* output;     // archivo de salida 
};

void execute_pipeline(pipeline apipe)
{
    assert(apipe != NULL);
    //Necesario para iterar
    int num_commands = pipeline_length(apipe);
    //Número que usaremos para identificar que no hay una "previous file direction"
    int prev_fd = -1;

    for (int i = 0; i < num_commands; i++)
    {
        scommand current_command = pipeline_front(apipe);
        //Verificación si el proceso actual se ejecutará en primer plano o segundo plano 
        if (!pipeline_get_wait(apipe) && i == num_commands -1)
        {
            // Si el comando es el último y debe ejecutarse en segundo plano
            execute_background(apipe);
        }
        else
        {
            // Ejecución de comandos con o sin pipe
            if (i < num_commands - 1)
            {
                // Crear pipe si no es el último comando: pipefd[0] de lectura y pipefd[1] de escritura
                int pipefd[2];
                // Corroboró que el pipe se cree correctamente
                if (pipe(pipefd))
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
                //Llamada a función auxiliar para la ejecución en tubería, siendo current_command "el comando actual a ejectura", prev_fd "el input de lectura" y pipedef[1] "el extremo de escritura donde se dirijirá la salida"
                execute_with_pipe(current_command, prev_fd, pipefd[1]);
                // cierro el extremo de escritura en el proceso padre para pasarlo al proceso hijo y así evitar fugas de descriptores de archivo.
                close(pipefd[1]);
                //Actualizo el extremo de lectura para ser usada como parametro de entrada con el proximo pipe
                prev_fd = pipefd[0];
            }
            else
            {
                // Ejecución del último comando en pipeline o único comando, llevando así su outpot a Stdout (la salida estandar).
                execute_with_pipe(current_command, prev_fd, STDOUT_FILENO);
            }
        }
        //Elimino el comando ya ejecutado logrando así el flujo de ejecución
        pipeline_pop_front(apipe);
    }

    // Esperar a los procesos hijos para cuando este sea en primer plano así no pedrder el flujo entre las entradas y salidas
    if (pipeline_get_wait(apipe))
    {
        int status;
        while (wait(&status) > 0);
    }
}

void execute_command(scommand cmd)
{
    assert(cmd != NULL);
    //Verifica si es un comando interno ("cd","help","exit")
    if (builtin_is_internal(cmd))
    {   
        //Ejecuta el comando interno 
        builtin_run(cmd);
        //Fin del proceso
        exit(EXIT_SUCCESS);
    }
    else
    {   
        //Guarda el nombre del comando
        char *cmd_name = scommand_front(cmd);
        //Creo un arreglo de cadenas para así poder usarlo con execvp dado que es la sintaxis que este necesita
        char **args = scommand_to_argv(cmd);
        //Uso execvp la cual busca reemplazar el proceso actual con el comando actual, este busca el ejecutable entre todos los directorios especificados por $PATH
        execvp(cmd_name, args);
        perror("execvp");
        //Libero la memoria
        free_memory_scommand_to_argv(args);
        //Fin del proceso
        exit(EXIT_FAILURE);
    }
}

char **scommand_to_argv(scommand cmd) {
    assert(cmd != NULL);
    
    unsigned int length = scommand_length(cmd);
    char **argv = malloc((length + 1) * sizeof(char *)); // +1 para NULL al final
    
    GList *iterator = cmd->arguments;
    for (unsigned int i = 0; i < length; i++) {
        argv[i] = (char *)g_list_nth_data(iterator, i);
    }
    argv[length] = NULL;  // El último elemento debe ser NULL para execvp

    return argv;
}

void free_memory_scommand_to_argv(char**killme){
     unsigned int i = 0;
    while (killme[i] != NULL) {
        free(killme[i]);
        i++;
    }
    free(killme);
}



void execute_with_pipe(scommand cmd, int input_fd, int output_fd)
{
    int pid = fork();
    if (pid == 0)
    {
        // Proceso hijo
        if (input_fd != -1)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        setup_redirection(cmd);
        execute_command(cmd);
    }
    else if (pid > 0)
    {
        // Proceso padre
        if (input_fd != -1)
        {
            close(input_fd);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void execute_background(pipeline apipe)
{
    int pid = fork();
    if (pid == 0)
    {
        // Proceso hijo
        scommand cmd = pipeline_front(apipe);
        setup_redirection(cmd);
        execute_command(cmd);
    }
    else if (pid > 0)
    {
        // Proceso padre
        printf("[Proceso en segundo plano, PID: %d]\n", pid);
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}


void setup_redirection(scommand cmd)
{
    char *input_file = scommand_get_redir_in(cmd);
    char *output_file = scommand_get_redir_out(cmd);

    if (input_file != NULL)
    {
        int fd_in = open(input_file, O_RDONLY);
        if (fd_in == -1)
        {
            perror("open input_file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    if (output_file != NULL)
    {
        int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            perror("open output_file");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}
