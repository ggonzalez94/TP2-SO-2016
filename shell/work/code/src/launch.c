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
//Devuelve una copia del ultimo argumento
char *findLastArgument(char **args){
  int i = 0 ;
  while(args[i] != NULL){
    i++;
  }
  char *last = malloc (50*sizeof(args[i-1]));
  strcpy(last,args[i-1]);
  return last;
}

//Devuelve 1(True) si el path es relativo ("/" no esta en path)
//Que pasa si la direccion es relativa pero no a la carpeta actual? (Ej : /shell)
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
  char *lastArgument = findLastArgument(args);
  // char *lastArgument = strcat(findLastArgument(args),".txt"); // lastArgument + .txt
  // const char* lastArgument = "a.txt";
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

    // Cambio standard output
    if (flags[OUTP]){
      FILE *fp;
      fp = freopen(lastArgument,"w",stdout);
      if (fp == NULL){ return -1;} //Si fallo abortar
    }
    else if (flags[INPT]){
      FILE *fp;
      fp = freopen(lastArgument,"r+",stdin);
      if (fp == NULL){ return -1;} //Si fallo abortar
    }

  	if (isRelative(args)){
  		char new_str[100] = "";
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

      if(wpid == -1){
        perror("Child process returned -1");
        exit(EXIT_FAILURE);
      }
	   }
  }

  return 1;
}