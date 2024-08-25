#include "command.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct scommand_s
{
    GList *arguments; // lista de argumentos del comando (lista de gchar*)
    gchar *input;     // archivo de entrada
    gchar *output;    // archivo de salida
};

struct pipeline_s
{
    GList *commands; // lista de scommand
    bool wait;       // indicador de si esperar la ejecución
};

scommand scommand_new(void)
{
    scommand comando = malloc(sizeof(struct scommand_s));
    comando->arguments = NULL;
    comando->input = NULL;
    comando->output = NULL;
    return comando;
}

scommand scommand_destroy(scommand self)
{
    assert(self != NULL);
    if (self != NULL)
    {
        g_list_free_full(self->arguments, free);
        free(self->input);
        free(self->output);
        free(self);
    }
    assert(self == NULL);
    return NULL;
}

void scommand_push_back(scommand self, char *argument)
{
    assert(self != NULL && argument != NULL);
    self->arguments = g_list_append(self->arguments, argument);
    assert(!scommand_is_empty(self));
}

void scommand_pop_front(scommand self)
{
    assert(self != NULL && !scommand_is_empty(self));
    GList *first_arg = g_list_first(self->arguments);
    self->arguments = g_list_delete_link(self->arguments, first_arg);
}

void scommand_set_redir_in(scommand self, char *filename)
{
    assert(self != NULL);
    if (self->input != NULL)
    {
        free(self->input);
    }
    self->input = filename;
}
void scommand_set_redir_out(scommand self, char *filename)
{
    assert(self != NULL);
    if (self->output != NULL)
    {
        free(self->output);
    }
    self->output = filename;
}

bool scommand_is_empty(const scommand self)
{
    assert(self != NULL);
    return (g_list_length(self->arguments) == 0);
}

unsigned int scommand_length(const scommand self)
{
    assert(self != NULL);

    int length = g_list_length(self->arguments);
    unsigned int lengt_f;
    lengt_f = (unsigned int)length;
    assert((scommand_length(self) == 0) == scommand_is_empty(self));
    return lengt_f;
}

char *scommand_front(const scommand self)
{
    assert(self != NULL && !scommand_is_empty(self));
    return ((char *)(g_list_first(self->arguments)->data));
}

char *scommand_get_redir_in(const scommand self)
{
    assert(self != NULL);
    return self->input;
}

char *scommand_get_redir_out(const scommand self)
{
    assert(self != NULL);
    return self->output;
}

char *scommand_to_string(const scommand self)
{
    assert(self != NULL);

    GString *str = g_string_new(NULL);

    for (GList *i = self->arguments; i != NULL; i = i->next)
    {
        g_string_append_printf(str, "%s ", (char *)i->data);
    }

    if (self->input != NULL)
    {
        g_string_append_printf(str, "< %s ", self->input);
    }

    if (self->output != NULL)
    {
        g_string_append_printf(str, "> %s ", self->output);
    }

    char *result = g_string_free(str, FALSE);
    g_strchomp(result);
    return result;
}

pipeline pipeline_new(void);

pipeline pipeline_destroy(pipeline self);

void pipeline_push_back(pipeline self, scommand sc);

void pipeline_pop_front(pipeline self);

void pipeline_set_wait(pipeline self, const bool w);

bool pipeline_is_empty(const pipeline self);

unsigned int pipeline_length(const pipeline self);

scommand pipeline_front(const pipeline self);

bool pipeline_get_wait(const pipeline self);

char *pipeline_to_string(const pipeline self);
