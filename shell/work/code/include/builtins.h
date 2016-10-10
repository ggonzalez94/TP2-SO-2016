#define NUM_BUILTINS = 3
#include <stdbool.h>
/*
  Function Declarations for builtin shell commands:
 */

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_num_builtins();
bool is_builtin(char **args, int i);
int execute_builtin (char **args,int i);