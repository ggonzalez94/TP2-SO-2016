#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/execute.h"
#include "../include/builtins.h"



int execute(char **args, char **path)
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

  return launch(args, path);
}

