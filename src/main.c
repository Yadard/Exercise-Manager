#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "loader.h"
#include "pretty_print.h"

#define MAX_CMD_LEN 255

enum CMD_ID { CMDID_LOAD, CMDID_UNLOAD, CMDID_RUN, CMDID_EXIT, CMDID_HELP };

const char CMDS[][MAX_CMD_LEN] = {"load", "unload", "run", "exit", "help"};
const char CMDS_HELP[][MAX_CMD_LEN] = {
    "load <lista_name>: loads the lista",
    "unload: unloads the lista, but it is unnecessary.",
    "run <exercise_index>: fetch and run the exercise",
    "exit: terminate application", "help: get help :)"};
const size_t CMDS_AMOUNT = sizeof(CMDS) / MAX_CMD_LEN;

void print_help(void);
void loop(lista_t *lista);
void get_data_from_argv(lista_t *lista, int argc, const char **argv);
void sanitize_input(char *buff, size_t buff_size);
void print_state(lista_t *lista);
int get_cmd_id(const char *cmd);

int main(int argc, const char **argv) {
  lista_t *lista = create_lista();
  if (!lista) {
    fprintf(stderr, ANSI_BOLD ANSI_FORE_RED
            "[ERROR]: Couldn't allocate memory for \"lista_t\"!\n");
    return EXIT_FAILURE;
  }

  if (argc > 1)
    get_data_from_argv(lista, argc, argv);

  loop(lista);
  free_lista(lista);
}

void print_help(void) {
  for (size_t i = 0; i < CMDS_AMOUNT; i++) {
    puts(CMDS_HELP[i]);
  }
}

void loop(lista_t *lista) {
  char cmd[MAX_CMD_LEN];
  bool running = true;

  while (running) {
    print_state(lista);
    fgets(cmd, MAX_CMD_LEN, stdin);
    sanitize_input(cmd, MAX_CMD_LEN);
    char *sep = strchr(cmd, ' ');
    if (sep)
      *sep = '\0';

    int id = get_cmd_id(cmd);

    switch (id) {
    case CMDID_EXIT:
      running = false;
      break;
    case CMDID_LOAD:
      if (!load_lista(lista, ++sep))
        fprintf(stderr,
                ANSI_FORE_RED
                "Couldn't load \"Lista\": \"%s\"\n\tREASON: %s\n" ANSI_RESET,
                sep, get_error_message(lista));
      else
        fprintf(stdout,
                ANSI_FORE_GREEN
                "Sucessfully loaded \"Lista\": \"%s\"\n" ANSI_RESET,
                sep);
      break;

    case CMDID_RUN: {
      func_exercise_t ex = get_exercise(lista, ++sep);
      if (!ex)
        fprintf(
            stdout,
            ANSI_FORE_YELLOW
            "[%s]: couldn't load exercise \"%s\"!\n\r REASON: %s\n" ANSI_RESET,
            get_loaded_lista(lista), sep, get_error_message(lista));
      else
        ex();
      break;
    }
    case CMDID_UNLOAD:
      unload_lista(lista);
      break;
    case CMDID_HELP:
      print_help();
      break;
    }
  }
}

void get_data_from_argv(lista_t *lista, int argc, const char **argv) {}

void sanitize_input(char *buff, size_t buff_size) {
  for (size_t i = 0; buff[i] && i < buff_size; i++) {
    buff[i] = tolower(buff[i]);
    if (buff[i] == '\n' || buff[i] == '\r')
      buff[i] = '\0';
  }
}

void print_state(lista_t *lista) {
  const char *name = get_loaded_lista(lista);
  if (name[0] == '\0') {
    name = "Null";
    fprintf(stdout, "[" ANSI_FORE_CYAN "%s" ANSI_RESET "]# ", name);
  } else {
    fprintf(stdout, "[" ANSI_FORE_BLUE "%s" ANSI_RESET "]# ", name);
  }
}

int get_cmd_id(const char *cmd) {
  for (size_t i = 0; i < CMDS_AMOUNT; i++) {
    if (strncmp(cmd, CMDS[i], MAX_CMD_LEN) == 0)
      return i;
  }
  return -1;
}
