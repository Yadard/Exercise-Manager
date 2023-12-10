#pragma once

#include "lista.h"
#include <stdbool.h>

#define VALUE(string) #string
#define TO_LITERAL(string) VALUE(string)

typedef struct lista_t lista_t;

lista_t *create_lista();

bool load_lista(lista_t *lista, const char *path);
void unload_lista(lista_t *lista);
func_exercise_t get_exercise(lista_t *lista, const char *path);
const char *get_error_message(lista_t *lista);
const char *get_loaded_lista(lista_t *lista);

void free_lista(lista_t *lista);
