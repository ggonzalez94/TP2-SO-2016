/** @file main.c
 *  @brief Funcion principal del programa Baash.
 *
 *  Funcion principal del programa, que contiene el bucle principal
 *  y espera una entrada de teclado por parte del usuario.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#define LENGTH_HOSTNAME 25
#define LENGTH_DIRECTORY 111

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

#include "../include/main_includes.h"
#include "../include/colores.h"
#include "../include/shared.h"

char* path[PATH_MAX];

  /**
  * @brief Parsea el PATH del sistema 
  * Separa el contenido de la variable PATH del sistema en sus distintas rutas.
  * Las mismas son separadas con el delimitador ":". 
  * Los tokens parseados son asignados a un arreglo de punteros a chars, variable global
  * solo modificada en este punto, y utilizada a lo largo de todo el programa.
  *
  * @param path una cadena de caracteres con el PATH del sistema. 
  * @param pathAux string auxiliar.
  * @param fullPath string con la variable PATH del sistema.
  * @return 0 caso exitoso, -1 si no se encontro el PATH.
  */

int splitPath (char** path, char *pathAux, char *fullPath){

    path[0] = strtok(pathAux,":");
    int i=0;
    while(path[i] != NULL){
        i++;
        path[i] = strtok(NULL,":");
    }

    return 0;
}

  /**
  * @brief Principal funcion del programa.
  * 
  * Parsea el PATH del sistema, lee lineas de comandos ingresadas por consola y
  * maneja el loop principal del programa, imprimiendo el command prompt y esperando
  * una nueva instruccion del usuario.
  */

int main(int argc, char **argv)
{

    char *line;
    char **args;
    int status;
    char* fullPath;
    char* pathAux;

    fullPath = getenv ("PATH");
    if(fullPath == NULL)
        return -1;

    pathAux = (char*) malloc(strlen(fullPath)+1);
    strcpy(pathAux,fullPath);

    splitPath(path, pathAux, fullPath);

    char *host_name = (char*)malloc(sizeof(char) * LENGTH_HOSTNAME);
    gethostname(host_name,LENGTH_HOSTNAME);

    struct passwd *p = getpwuid(getuid());

    char *current_directory = (char*)malloc(sizeof(char) * LENGTH_DIRECTORY);
    current_directory = getcwd(current_directory,LENGTH_DIRECTORY);

    // Correr el loop principal
    do {
        //Username@Hostname: Current_Directory >
        printf(BOLDMAGENTA "%s@", p->pw_name);
        printf("%s: " RESET,host_name);
        printf(BOLDGREEN"%s",current_directory);
        printf("> " RESET);
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
        current_directory = getcwd(current_directory,LENGTH_DIRECTORY);
    } while (status);

    free(pathAux);
    return EXIT_SUCCESS;
}

