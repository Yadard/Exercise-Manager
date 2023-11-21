#pragma once
#include "lista.h"

typedef struct lista_t lista_t;

lista_t *load_lista(const char *path);

func_exercise_t get_exercise(lista_t *lista, const char *path);

void free_lista(lista_t *lista);