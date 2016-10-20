/** @file builtins.c
 *  @brief Declaracion de funciones builtin para el programa Baash
 *
 *  Contiene las funciones propias del programa.
 *  Estas son cd, help y exit.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../include/builtins.h"
#include "../include/colores.h"

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

/**
* @brief Calcula el numero de funciones builtin soportadas.
*
* Calcula el numero de funciones builtin que puede ejecutar el programa.
* Funcion escalable si a futuro se agregan mas.
* @return La cantidad de funciones builtin del Baash.
*/
int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/**
* @brief Implementacion de la funcion Change Directory.
*
* Cambia el directorio de trabajo actual, usando la system call chdir.
* Retorna siempre 1 (sigue la ejecucion del Baash).
* Si el directorio no existe imprime un error por consola.
* @param args Los tokens ingresados por consola en el comando actual.
*/
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "Baash error: se esperaba un argumento para \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("Baash error");
    }
  }
  return 1;
}


/**
* @brief Imprime un mensaje de ayuda.
*
* Imprime un breve mensaje de ayuda que lista las funciones builtin del Baash.
* Tambien menciona los operadores pipe, append, etc.
* @param args Los tokens ingresados por consola en el comando actual.
*/
int lsh_help(char **args)
{
  int i;
  printf("Bienvenido a Baash\n");
  printf("Ingrese el comando y presione enter\n");
  printf("Los siguientes son comandos built-in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf(BOLDBLUE "  %s\n" RESET, builtin_str[i]);
  }

  printf("Use el comando " BOLDBLUE "man" RESET " para info sobre otros programas. EJ: man ps\n");
  printf("Puede utilizar los operadores:");
  printf(BOLDBLUE "\n  & Paralel \n  < Stdin \n  > Stdout \n  >> Stdout append \n  | Pipe\n" RESET);
  printf("Para alterar la ejecucion del programa.\n");
  return 1;
}


/**
* @brief Finaliza la ejecucion del Baash
*
* Devuelve un cero, lo que hace que en el archivo main.c se finalice la ejecucion del programa Baash.
* @param args Los tokens ingresados por consola en el comando actual.
*/
int lsh_exit(char **args)
{
  return 0;
}


/**
* @brief Identifica si el comando ingresado es una funcion builtin o no.
*
* Compara el primer token ingresado por consola con los nombres de las funciones builtin que soporta Baash.
* @param args Los tokens ingresados por consola en el comando actual.
* @param i El indice de la funcion builtin a comparar.
* @return 0 si la funcion no es builtin, 1 si lo es.
*/
bool is_builtin(char **args,int i){
  return strcmp(args[0], builtin_str[i]) == 0;
}

/**
* @brief Ejecuta la funcion builtin que se solicita.
*
* Ejecuta la funcion builtin necesaria, devolviendo el entero que la misma retorne.
* @param args Los tokens ingresados por consola en el comando actual.
* @param i El indice de la funcion builtin a ejecutar.
* @return El valor que retorne la funcion ejecutada (cualquiera de las 3 que sea).
*/
int execute_builtin(char **args,int i){
  return (*builtin_func[i])(args);
}

