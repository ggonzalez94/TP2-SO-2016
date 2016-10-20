/** @file split_line.c
 *  @brief Una funcion simple que parsea un string
 *
 *  Contiene una funcion que parsea el string que recibe,
 *  separandolo en tokens.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* @brief Separa la linea de texto en tokens.
*
* La instruccion con la que se llama a split_line es parseada y separada,
* usando como delimitadores los caracteres de escape, y los espacios.
* @param line comando ingresado por consola a parsear.
* @return tokens: un arreglo con el comando ingresado, separado en tokens.
*/

char **split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}