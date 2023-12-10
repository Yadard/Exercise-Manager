#include "lista.h"
#include "loader.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_SHARED_LIB_POSTFIX 2
#define LEN_SHARED_LIB_PREFIX 3
#define AMOUNT_OF_DOTS 1
#define ERROR_MESSAGE_LEN 1024
#define MAX_LISTA_NAME_LEN 1024

typedef struct lista_t {
  void *handle;
  func_get_exercise_t getter;
  char error_msg[ERROR_MESSAGE_LEN];
  char current_lista[MAX_LISTA_NAME_LEN];
} lista_t;

lista_t *create_lista() {
  lista_t *lista = malloc(sizeof(lista_t));
  if (!lista)
    return NULL;

  lista->handle = NULL;
  lista->getter = NULL;
  memset(lista->error_msg, 0, ERROR_MESSAGE_LEN);
  memset(lista->current_lista, 0, MAX_LISTA_NAME_LEN);

  return lista;
}

bool load_lista(lista_t *lista, const char *path) {
  size_t len = strlen(path);

  if (len + 1 > MAX_LISTA_NAME_LEN) {
    snprintf(lista->error_msg, ERROR_MESSAGE_LEN,
             "Lista name exceed the %d limit!", MAX_LISTA_NAME_LEN);
    return false;
  }

  char lib_path[MAX_LISTA_NAME_LEN];
  snprintf(lib_path, MAX_LISTA_NAME_LEN, "./lib%s.so", path);

  if (lista->handle)
    unload_lista(lista);

  lista->handle = dlopen(lib_path, RTLD_LAZY);
  if (!lista->handle) {
    snprintf(lista->error_msg, ERROR_MESSAGE_LEN, "%s", dlerror());
    return NULL;
  }

  lista->getter = NULL;
  memcpy(lista->current_lista, path, len + 1);

  return lista;
}

void unload_lista(lista_t *lista) {
  if (lista->handle) {
    dlclose(lista->handle);
    lista->handle = NULL;
  }
  memset(lista->current_lista, 0, MAX_LISTA_NAME_LEN);
  lista->getter = NULL;
}

func_exercise_t get_exercise(lista_t *lista, const char *path) {
  if (!lista->handle) {
    snprintf(lista->error_msg, ERROR_MESSAGE_LEN,
             "There isn't a \"Lista\" loaded, use \"load <list_name>\" to load "
             "one.");
    return NULL;
  }

  if (!lista->getter) {
    lista->getter =
        (func_get_exercise_t)dlsym(lista->handle, TO_LITERAL(EXERCISE_GETTER));
    if (!lista->getter) {
      snprintf(lista->error_msg, ERROR_MESSAGE_LEN, "%s", dlerror());
      return NULL;
    }
  }

  return lista->getter(path, strlen(path));
}
const char *get_error_message(lista_t *lista) { return lista->error_msg; }

const char *get_loaded_lista(lista_t *lista) { return lista->current_lista; }

void free_lista(lista_t *lista) {
  if (!lista)
    return;

  if (lista->handle)
    dlclose(lista->handle);
  free(lista);
}
