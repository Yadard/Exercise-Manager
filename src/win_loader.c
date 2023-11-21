#include "loader.h"
#include <Windows.h>
#include <stdio.h>

#define LEN_LIB_PREFIX 3
#define LEN_DLL_SUFFIX 3

#define VALUE(string) #string
#define TO_LITERAL(string) VALUE(string)

typedef struct lista_t {
    HINSTANCE handle;
    func_get_exercise_t getter;
} lista_t;

lista_t *load_lista(const char *path) {
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista)
        return NULL;

    size_t len = strlen(path);
    size_t size = len + 2 + LEN_DLL_SUFFIX + LEN_LIB_PREFIX;
    char *lib_path = malloc(size);

    snprintf(lib_path, size, "lib%s.dll", path);

    lista->handle = LoadLibrary(lib_path);
    if (!lista->handle) {
        free_lista(lista);
        return NULL;
    }

    lista->getter = NULL;

    return lista;
}

func_exercise_t get_exercise(lista_t *lista, const char *path) {
    if (!lista->getter) {
        lista->getter = (func_get_exercise_t)GetProcAddress(lista->handle, TO_LITERAL(EXERCISE_GETTER));
        if (!lista->getter)
            return NULL;
    }

    return lista->getter(path);
}

void free_lista(lista_t *lista) {
    if (lista) {
        if (lista->handle)
            FreeLibrary(lista->handle);
        free(lista);
    }
}