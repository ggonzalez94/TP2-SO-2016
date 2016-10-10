#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/builtins.h"

/*
  Array de builtins
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

/*
  Devuelve un puntero a la funcion built-in correspondiente
*/
int (*builtin_func[]) (char **) = {
  &lsh_cd,
  &lsh_help,
  &lsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Implementacion de las funciones built-in
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args)
{
  int i;
  printf("Bienvenido a Baash\n");
  printf("Entre el comando y aprete enter\n");
  printf("Los siguientes son comandos built-in\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use el comando man para info sobre otros programas. EJ: man ps\n");
  return 1;
}

int lsh_exit(char **args)
{
  return 0;
}

bool is_builtin(char **args,int i){
  return strcmp(args[0], builtin_str[i]) == 0;
}

int execute_builtin(char **args,int i){
  return (*builtin_func[i])(args);
}

