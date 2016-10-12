#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AMP 0
#define PIPE 1
#define INPT 2
#define OUTP 3

int flags [4] = {0,0,0,0};

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


int checkFlag(char ch, char* word, int flagIndex){

	if(strcmp(&ch,word)==0){
  		flags[flagIndex]++;
  		return 0;
  	}
  	return -1;
}

void resetFlags(){
	for (int i = 0; i < 4; ++i)
		flags[i]=0;
}

int launch(char **args)
{
  pid_t pid, wpid;
  int status;
  int i=0;

  resetFlags();

  char caracter[5]= "&|<>";

  while(args[i]!=NULL){

  	for(int j=0; j<4; j++){
	  	if(checkFlag(caracter[j],args[i],j)==0){
	  		args[i]=NULL;
	  		break;
	  	}
	}
  	i++;
  }

  pid = fork();
  if (pid == 0) {
    // Child process

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

  	if(flags[AMP] == 0){
	    do {
	      wpid = waitpid(pid, &status, WUNTRACED);
	    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
  }

  return 1;
}