/** @file execute.c
 *  @brief Ejecuta la instruccion ingresada, sea builtin o no.
 *
 *  Recibe la instruccion que se ingreso por consola,
 *  y comanda su ejecución, intentando primero en las
 *  builtin del Baash, y luego con los programas propios de Linux.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/execute.h"
#include "../include/builtins.h"

extern char* path[50];

  /**
  * @brief Ejecuta la instrucción ingresada.
  *
  * Al presionar enter, se llama a esta funcion con los caracteres 
  * ingresados en el Baash. Si fue un string vacio, no hace nada.
  * Caso contrario, intenta ejecutarlo como una funcion builtin.
  * Si falla, intenta con los programas de Linux.
  * @see launch()
  * @param args Una cadena de strings previamente parseada, lista para ser ejecutada.
  * @return 0 para finalizar el Baash, 1 en caso contrario, para esperar otro comando.
  */

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
     if (is_builtin(args,i)) {
       return execute_builtin(args,i);
     }
  }

  return launch(args);
}