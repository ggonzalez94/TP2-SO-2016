#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *paths[] = {
  "/bin/",
  "/usr/bin/",
  "/usr/games/",
  "/usr/sbin/"
};

int isRelative(char** path){

	if(strstr(*path,"/")==NULL){
		return 1;
	}
	return 0;
}

int num_paths() {
  return sizeof(paths) / sizeof(char *);
}

int runCommand(char **args, char *path){
  	if (execv(path, args) == -1) 
    	return -1;
    return 0;
}

int launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process

    // if (execvp(args[0], args) == -1) {
    //   perror("Baash error");
    // }
    // exit(EXIT_FAILURE);

  	if (isRelative(args)){
  		char new_str[50] = "";
  		for(int i=0; i<num_paths();i++){
  			strcat(new_str,paths[i]);
  			strcat(new_str,args[0]);
  			runCommand(args,new_str);

  			//limpio el string para probar de nuevo
  			new_str[0] = 0;
  		}
  		perror("Baash error");
  		exit(EXIT_FAILURE);
  	}

  	else if(runCommand(args,args[0]) == -1){
		perror("Baash error");
	    exit(EXIT_FAILURE);
  	}
  } 
  else if (pid < 0) {
    // Error forking
    perror("Baash error forking");
  } 

  else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}