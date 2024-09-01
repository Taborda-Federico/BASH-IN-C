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
Evaluar porque demora tanto en aparecer "mybash>" cuando se activa la terminal y luego al ejecutar
Leaks de memoria revisar, de donde provienen.
*/
struct scommand_s
{
    GList *arguments; // lista de argumentos del comando (lista de gchar*)
    char *input;      // archivo de entrada
    char *output;     // archivo de salida
};

void execute_pipeline(pipeline apipe)
{
    assert(apipe != NULL);
    // Necesario para iterar
    int num_commands = pipeline_length(apipe);
    // Número que usaremos para identificar que no hay una "previous file direction"
    int prev_fd = -1;

    for (int i = 0; i < num_commands; i++)
    {
        scommand current_command = pipeline_front(apipe);
        // Verificación si el proceso actual se ejecutará en primer plano o segundo plano
        if (!pipeline_get_wait(apipe) && i == num_commands - 1)
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
                // Corroboró que el pipe se cree correctamente y lo creo simultaneamente
                if (pipe(pipefd))
                {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }
                // Llamada a función auxiliar para la ejecución en tubería, siendo current_command "el comando actual a ejectura", prev_fd "el input de lectura" y pipedef[1] "el extremo de escritura donde se dirijirá la salida"
                execute_with_pipe(current_command, prev_fd, pipefd[1]);
                // cierro el extremo de escritura en el proceso hijo para pasarlo al proceso padre y así evitar fugas de descriptores de archivo. Al mismo tiempo corroboro que no haya errores al cerrar el archivo
                if (close(pipefd[1]) == -1)
                {
                    perror("close pipefd[1]");
                    exit(EXIT_FAILURE);
                }
                // Actualizo el extremo de lectura para ser usada como parametro de entrada con el proximo pipe
                prev_fd = pipefd[0];
            }
            else
            {
                // Ejecución del último comando en pipeline o único comando, llevando así su outpot a Stdout (la salida estandar).
                execute_with_pipe(current_command, prev_fd, STDOUT_FILENO);
            }
        }
        // Elimino el comando ya ejecutado logrando así el flujo de ejecución
        pipeline_pop_front(apipe);
    }

    // Esperar a los procesos hijos para cuando este sea en primer plano así no perder el flujo entre las entradas y salidas
    if (pipeline_get_wait(apipe))
    {
        int status;
        while (wait(&status) > 0)
            ;
    }
}

void execute_command(scommand cmd)
{
    assert(cmd != NULL);
    // Verifica si es un comando interno ("cd","help","exit")
    if (builtin_is_internal(cmd))
    {
        // Ejecuta el comando interno
        builtin_run(cmd);
        // Fin del proceso
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Guarda el nombre del comando
        char *cmd_name = scommand_front(cmd);
        // Creo un arreglo de cadenas para así poder usarlo con execvp dado que es la sintaxis que este necesita
        char **args = scommand_to_argv(cmd);
        // Uso execvp la cual busca reemplazar el proceso actual con el comando actual, este busca el ejecutable entre todos los directorios especificados por $PATH
        execvp(cmd_name, args);
        perror("execvp");
        // Libero la memoria
        free_memory_scommand_to_argv(args);
        // Fin del proceso
        exit(EXIT_FAILURE);
    }
}

char **scommand_to_argv(scommand cmd)
{
    assert(cmd != NULL);
    // Calculo la longitud saber cuanta memoria necesito asignar
    unsigned int length = scommand_length(cmd);
    // asigno memoria con longitud +1 para poder ponerl valor NULL al final
    char **argv = malloc((length + 1) * sizeof(char *));
    // Iterador para ir recorriendo los argumentos y así agregarlos al arreglo
    GList *iterator = cmd->arguments;
    for (unsigned int i = 0; i < length; i++)
    {
        // Le voy dando valores al arreglo
        argv[i] = (char *)g_list_nth_data(iterator, i);
    }
    // El último elemento debe ser NULL para el uso correcto de execvp
    argv[length] = NULL;

    return argv;
}

void free_memory_scommand_to_argv(char **killme)
{
    // Creo variable para iterar en el arreglo
    unsigned int i = 0;
    // Itero mientras el arreglo indexado en i, no sea NULL, dado que por la necesidad de execvp sabemos que el ultimo elemento de mi arreglo tenía que se NULL
    while (killme[i] != NULL)
    {
        // Libero el espacio de memoria asociado al arreglo en la posición i
        free(killme[i]);
        i++;
    }
    // Libero el espacio de memoria asignado a la cabeza del arreglo
    free(killme);
}

void execute_with_pipe(scommand cmd, int input_fd, int output_fd)
{
    // Separo en proceso padre y proceso hijo
    int pid = fork();
    // Evaluo el proceso es hijo
    if (pid == 0)
    {
        // Corroboró si en la llamada hay una orden de entrada especifica
        if (input_fd != -1)
        {
            // La dirección del directorio de entrada correspondiente la envió a STDIN_FILENO para que el la información recibida sea la esperada y al mismo tiempo se previene un posible error
            if (dup2(input_fd, STDIN_FILENO) == -1)
            {
                perror("dup2 input_fd");
                exit(EXIT_FAILURE);
            }
            // Se cierra el directorio input_fd para que no haya duplicados innecesarios dado que su información ya se encuentra en STDIN_FILENO y al mismo tiempo se previene un posible error
            if (close(input_fd) == -1)
            {
                perror("close input_fd");
                exit(EXIT_FAILURE);
            }
        }
        // Corroboró si en la llamada hay una orden de salida especifica
        if (output_fd != STDOUT_FILENO)
        {
            // La dirección del directorio de salida correspondiente la envió a STDOUT_FILENO para que el la información enviada sea en el mismo lugar y al mismo tiempo se previene un posible error
            if (dup2(output_fd, STDOUT_FILENO) == -1)
            {
                perror("dup2 output_fd");
                exit(EXIT_FAILURE);
            }
            // Se cierra el directorio output_fd para que no haya duplicados innecesarios dado que su información ya se encuentra en STDOUT_FILENO y al mismo tiempo se previene un posible error
            if (close(output_fd) == -1)
            {
                perror("close input_fd");
                exit(EXIT_FAILURE);
            }
        }
        // Se llama a setup_redirection para darles los valores a STDOUT_FILENO o STDIN_FILENO correspondientes si llegará a ser necesario
        setup_redirection(cmd);
        // Se ejecuta el comando ya dandole los valores correspondientes a STDIN_FILENO Y A STDOUT_FILENO
        execute_command(cmd);
    }
    // Evaluo el proceso padre
    else if (pid > 0)
    {
        // Corroboró si en la llamada hay una orden de entrada especifica
        if (input_fd != -1)
        {
            //Se cierra el directorio input y así se evita posibles errores no serán necesarios para el proceso padre y al mismo tiempo se previene posible errores
            if (close(input_fd) == -1)
            {
                perror("close input_fd");
                exit(EXIT_FAILURE);
            };
        }
    }
    else
    {
        //Si la llamada a fork falla se previene y se manda mensaje de error
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void execute_background(pipeline apipe)
{
    int pid = fork();
    //Evaluo proceso hijo
    if (pid == 0)
    {
        //Separo el comando a ejecutar
        scommand cmd = pipeline_front(apipe);
        //Redireccion  STDIN_FILENO o STDOUT_FILENO de ser necesario
        setup_redirection(cmd);
        //Ejecuto el comando 
        execute_command(cmd);
    }
    //Evaluo proceso padre
    else if (pid > 0)
    {
        // Devuelvo el PID del proceso padre, (un chiche que estaría bueno que sea predeterminado en terminales bash script)
        printf("[Proceso en segundo plano, PID: %d]\n", pid);
    }
    // Prevengo posible error de la llamada a fork()
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void setup_redirection(scommand cmd)
{
    //Recibo dirección de entrada correspondiente para cmd
    char *input_file = scommand_get_redir_in(cmd);
    //Recibo dirección de salida correspondiente para cmd
    char *output_file = scommand_get_redir_out(cmd);
    //Si el redireccionamiento de entrada no está vacio
    if (input_file != NULL)
    {
        //Abro el archivo relaccionado con la redirección de entrada en modo de solo lectura y guardo su vakir eb file direction en fd_in
        int fd_in = open(input_file, O_RDONLY);
        //Prevengo posible error en la apertura de la redirección 
        if (fd_in == -1)
        {
            perror("open input_file");
            exit(EXIT_FAILURE);
        }
        //Asocio STDIN_FILENO con la redirección de entrada fd_in
        dup2(fd_in, STDIN_FILENO);
        //Cierro la redirección para evitar posibles problemas su información ya se encuentra en STDIN_FILENO
        close(fd_in);
    }
    //Si la redirección de salida no es nula
    if (output_file != NULL)
    {
        //Abro el archivo de redirección de salida, en modo de escritura, creación por si fuera necesario o truncado por si tenía escrito algo así reemplazarlo
        int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        //Prevengo posibles errores en la apertura
        if (fd_out == -1)
        {
            perror("open output_file");
            exit(EXIT_FAILURE);
        }
        //Asocio STDOUT_FILENO con la redirección de salida fd_out
        dup2(fd_out, STDOUT_FILENO);
        //Cierro la redirección para evitar posibles problemas su información ya se encuentra en STDOUT_FILENO
        close(fd_out);
        
    }
}
