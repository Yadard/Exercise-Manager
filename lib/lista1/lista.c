#define LIBRARY_EXPORTS
#include "lista.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

void exercise1(void);

static func_exercise_t exercises[8] = {exercise1};

LIBRARY_API func_exercise_t EXERCISE_GETTER(const char *path,
                                            size_t path_size) {
  if (!path_size || !isalpha(path[0]))
    return NULL;

  char exercise_index = tolower(path[0]);
  int index = exercise_index - 'a';

  return exercises[index];
}

void exercise1(void) {
  float width, height;
  printf("Welcome to the rectangle area calculator!\n");
  printf("Input the width and height of the rectangle with the following "
         "notation: <width>:<height>\n");

  bool got_valid_input = false;
  char input[255];
  do {
    fgets(input, 255, stdin);
    sscanf(input, "%f:%f", &width, &height);
    got_valid_input = width && height;
  } while (!got_valid_input);

  float area = width * height;

  printf("The area of a %.2f:%.2f is %.2f\n", width, height, area);
}
