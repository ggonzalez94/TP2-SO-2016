/** @file read_line.c
 *  @brief Lee una linea ingresada por consola luego de un Enter.
 *
 *  Detecta el comando ingresado en la consola, y lo guarda en un arreglo de chars.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

  /**
  * @brief Lee una linea ingresada por consola luego de un Enter.
  * Detecta el comando ingresado en la consola, y lo guarda en un arreglo de chars.
  * 
  * @return line Un arreglo de chars con la cadena de caracteres ingresada
  */

char *read_line(void)
{
  char *line = NULL;
  size_t bufsize = 0;
  ssize_t read;
  if ((read = getline(&line, &bufsize, stdin)) != -1)
  	return line;
  else{
  	perror("Error reading line");
  	exit(0);
  }
}
