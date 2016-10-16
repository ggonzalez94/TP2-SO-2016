#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
