#include <stdlib.h>
#include <stdio.h>

#include "../include/main_includes.h"

int main(int argc, char **argv)
{

  char *line;
  char **args;
  int status;

  // Correr el loop principal
  do {
    printf("> ");
    line = read_line();
    args = split_line(line);
    status = execute(args);

    free(line);
    free(args);
  } while (status);


  return EXIT_SUCCESS;
}

