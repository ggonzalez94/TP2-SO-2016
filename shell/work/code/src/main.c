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

char* path[50];

int splitPath (char** path)
{
  char* fullPath;
  fullPath = getenv ("PATH");
  if(fullPath == NULL)
    return -1;
  char *pathAux = (char *)malloc(strlen(fullPath) + 1);
  strcpy(pathAux,fullPath);

    path[0] = strtok(pathAux,":");
    int i=0;
    while(path[i] != NULL){
      i++;
      path[i] = strtok(NULL,":");
    }
    free(pathAux);
  
  return 0;
}

int main(int argc, char **argv)
{

  char *line;
  char **args;
  int status;

  splitPath(path);

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


  return EXIT_SUCCESS;
}

