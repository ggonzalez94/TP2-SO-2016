#include <string.h>
#include <stdio.h>

char *read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; 
  getline(&line, &bufsize, stdin);
  return line;
}
