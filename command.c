#include "command.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct scommand_s {
    GList *arguments;  // lista de argumentos del comando (lista de gchar*)
    char* input;      // archivo de entrada 
    char* output;     // archivo de salida 
};

struct pipeline_s {
    GList *commands;   // lista de scommand
    bool wait;         // indicador de si esperar la ejecución
};

scommand scommand_new(void){
    scommand comando = malloc(sizeof(struct scommand_s));
    comando->arguments = NULL;
    comando->input = NULL;
    comando->output = NULL;
    return comando;
}

scommand scommand_destroy(scommand self){
    assert(self!=NULL);
    
        g_list_free_full(self->arguments, free);
        free(self->input);
        free(self->output);
        free(self);  
    self=NULL;
    assert(self == NULL);
    return NULL;
    
}

void scommand_push_back(scommand self, char * argument) {
    assert(self != NULL && argument != NULL);
    self->arguments = g_list_append(self->arguments, argument);
   
    assert(!scommand_is_empty(self));
}


void scommand_pop_front(scommand self){
    assert(self!=NULL && !scommand_is_empty(self));
    GList  *first_arg = g_list_first(self->arguments);
    self->arguments= g_list_remove_link(self->arguments, first_arg);
}

void scommand_set_redir_in(scommand self, char *filename) {
    assert(self != NULL);
    if (self->input != NULL) {
        free(self->input);
    }
    self->input = filename;
}

void scommand_set_redir_out(scommand self, char *filename) {
    assert(self != NULL);
    if (self->output != NULL) {
        free(self->output);
    }
    self->output = filename; 
}

bool scommand_is_empty(const scommand self) {
    assert(self != NULL);
    return (g_list_length(self->arguments) == 0);
}

unsigned int scommand_length(const scommand self){
    assert(self != NULL);
    unsigned int length = 0;
    length  = g_list_length(self->arguments);
   // assert((scommand_length(self)==0) == scommand_is_empty(self));
    return length;
}

char *scommand_front(const scommand self) {
    assert(self != NULL && !scommand_is_empty(self));
     return g_list_nth_data(self->arguments,0);       //Rompimos abstracción usamos función para g_list_nth_data para recuperar, antes estaba: return self->arguments->data;
}

char * scommand_get_redir_in(const scommand self){
    assert(self != NULL);
    return self->input;
}

char *scommand_get_redir_out(const scommand self) {
    assert(self != NULL);
    return self->output;
}

char *scommand_to_string(const scommand self) {
    assert(self != NULL);
    
    GString *str = g_string_new(NULL);  
    
    for (GList *i = self->arguments; i != NULL; i = i->next) {
        g_string_append_printf(str, "%s ", (char *)g_list_nth_data(i,0)); // Aca se rompio abstracción anterior: (char *)i->data);
    }
    
    if (self->input != NULL) {
        g_string_append_printf(str, "< %s ", self->input);
    }
    
    if (self->output != NULL) {
        g_string_append_printf(str, "> %s ", self->output);
    }
    
    char *result = g_string_free(str, FALSE);
    g_strchomp(result);
    return result;
}


pipeline pipeline_new(void){

    pipeline new_comand = malloc(sizeof(struct pipeline_s));
    new_comand->commands= NULL;
    new_comand->wait = true;
    return new_comand;
    

}

pipeline pipeline_destroy(pipeline self) {
    assert(self!=NULL);
    if (self != NULL) {
        // Primero, asegúrate de que todos los comandos sean destruidos
        while ((g_list_length(self->commands)!=0  )) {
            GList *first_node = g_list_first(self->commands);
            self->commands = g_list_remove_link(self->commands, first_node);
            scommand_destroy((scommand)g_list_nth_data(first_node,0));          //Aca habíamos roto la abstracción lo correjimos codigo anterior:first_node->data
            g_list_free(first_node);
        }
        // Finalmente, libera la memoria del propio pipeline
        free(self);
    }
    return NULL;
}

void pipeline_push_back(pipeline self, scommand sc){

    assert(sc !=NULL && self !=NULL);
    self->commands= g_list_append(self->commands, sc); // fun que agrega el elemneto al final de la lista
}

void pipeline_pop_front(pipeline self){

    assert(self !=NULL && !pipeline_is_empty(self));
    scommand kill_me =g_list_nth_data(self->commands,0);  // asigno el primer elmento, se había roto la abtracción anterior: self->commands->data;
    self->commands = g_list_remove(self->commands, kill_me);
    scommand_destroy(kill_me); // lo elimino

}

void pipeline_set_wait(pipeline self, const bool w){
assert(self!=NULL);
if (self == NULL)
{
    return; //si es null corta
}

self->wait = w;


}

bool pipeline_is_empty(const pipeline self){
    assert(self != NULL);
    return (g_list_length(self->commands) == 0);

}

unsigned int pipeline_length(const pipeline self){
    assert(self != NULL);
    return g_list_length(self->commands) ;


}

scommand pipeline_front(const pipeline self){
    assert(self!=NULL && !pipeline_is_empty(self));
        if (self == NULL || self->commands == NULL) {
        return NULL; // Si el pipeline es NULL o no tiene comandos, devuelve NULL.
    }

     return g_list_nth_data(self->commands,0);    //Se rompio la abstracción anterior:  self->commands->data 
}



bool pipeline_get_wait(const pipeline self){
    assert(self!=NULL);

    if (self == NULL)
    {
        return false;   
    }
    
    return self->wait;

}

char * pipeline_to_string(const pipeline self){
      assert(self!=NULL);
      if (self == NULL ) {
        return g_strdup(""); // Devuelve una cadena vacía si el pipeline es NULL o no tiene comandos.
    }  
    GList *i = self->commands;
    int index = 0;
    GString *str = g_string_new(NULL);
     int length = g_list_length(i);
    for (; i!=NULL ; i = i->next, index++)
    {
        scommand comando = g_list_nth_data(i,0); // i->data a un tipo scommand, se había roto la abstracción anterior: (scommand)i->data;
        char *comando_str = scommand_to_string(comando); //comvierte un scomand a una cadena
        g_string_append(str , comando_str);
        free(comando_str);

      if (index < length -1)
      {
        g_string_append(str, "|");
      }
      
    }
        if (!self->wait) { 
        g_string_append(str, " &");
    }
 return g_string_free(str,false);

}
