#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/launch.h"
#include "../include/builtins.h"

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  // for (i = 0; i < lsh_num_builtins(); i++) {
  //   if (strcmp(args[0], builtin_str[i]) == 0) {
  //     return (*builtin_func[i])(args);
  //   }
  // }

  for (i = 0; i < lsh_num_builtins(); i++) {
     if (is_builtin(args,i)) {
       return execute_builtin(args,i);
     }
  }

  return launch(args);
}

