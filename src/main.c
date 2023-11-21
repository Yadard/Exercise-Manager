#include <stdio.h>
#include <stdlib.h>

#include "loader.h"

void print_usage(void);

int main(int argc, const char **argv) {
    if (argc < 3) {
        print_usage();
        return EXIT_FAILURE;
    }

    lista_t *lista = load_lista(argv[1]);

    if (!lista) {
        fprintf(stderr, "Invalid list inputted!");
        return EXIT_FAILURE;
    }

    func_exercise_t ex = get_exercise(lista, argv[2]);
    if (!ex) {
        fprintf(stderr, "Invalid exercise inputted!");
        return EXIT_FAILURE;
    }

    printf("%s:%s\n", argv[1], argv[2]);
    ex();

    return EXIT_SUCCESS;
}

void print_usage(void) {
    printf("USAGE: \n"
           "\t./main <lista> <exercise>\n");
}