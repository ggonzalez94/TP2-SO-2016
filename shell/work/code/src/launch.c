#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/launch.h"

const char *paths[] = {
  "/bin/",
  "/usr/bin/",
  "/usr/games/",
  "/usr/sbin/"
};

int launch(char **args, char **path)
{
  char *lastArgument = findLastArgument(args);
  pid_t pid, wpid;
  int status;
  int i=0;
  int changeStdIOResult;

  resetFlags();
  
  caracter[0] = "&";
  caracter[1] = "|";
  caracter[2] = "<";
  caracter[3] = ">";
  caracter[4] = ">>";

  while(args[i]!=NULL){

  	for(int j=0; j<5; j++){
	  	if(checkFlag(caracter[j],args[i],j)==0){
	  		args[i]=NULL;
	  		break;
	  	}
	}
  	i++;
  }

  pid = fork();
  switch(pid){
  	case 0: 
    // Child process
    
	    // Cambio standard input/output
	    if (flags[APPEND]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"a",stdout)) == -1)
	    		exit(EXIT_FAILURE);
	    }
	    if (flags[OUTP]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"w",stdout)) == -1)
	    		exit(EXIT_FAILURE);
	    }
	    if (flags[INPT]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"r+",stdin)) == -1)
	    		exit(EXIT_FAILURE);
	    }

	  	if (isRelative(args)){
	  		char new_str[100] = "";
	  		for(int i=0; i<20;i++){

	  				strcat(new_str,path[i]);
	  				strcat(new_str,"/");
	  				strcat(new_str, args[0]);
	  				runCommand(args,new_str);

	  			//limpio el string para probar de nuevo
	  			new_str[0] = 0;
	  		}
	  		perror("Baash error executing command");
	  		exit(EXIT_FAILURE);
	  	}

	  	else if(runCommand(args,args[0]) == -1){
			perror("Baash error executing command");
		    exit(EXIT_FAILURE);
	  	}
	  	break;

  	case -1:
    // Error forking
	    perror("Baash error forking");
	    break;

    
    default:
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

int changeStdIO(char* lastArgument, const char* mode, FILE *stream){
    	FILE *fp;
    	fp = freopen(lastArgument,mode,stream);
    	if(fp == NULL)
    		return -1;
    	else
    		return 0;
    }

//Devuelve una copia del ultimo argumento
char *findLastArgument(char **args){
  int i = 0 ;
  while(args[i] != NULL){
    i++;
  }
  char *last = (char*) malloc (50*sizeof(args[i-1]));
  strcpy(last,args[i-1]);
  return last;
}

//Devuelve 1(True) si el path es relativo ("/" no esta en path)
int isRelative(char** path){

	if(strstr(*path,"/")==NULL){
		return 1;
	}
	return 0;
}

int runCommand(char **args, char *path){
  	if (execv(path, args) == -1) 
    	return -1;
    return 0;
}

int checkFlag(const char* ch, char* word, int flagIndex){
	if(strcmp(ch,word)==0){
  		flags[flagIndex]++;
  		return 0;
  	}
  	return -1;
}

void resetFlags(){
	for (int i = 0; i < 5; ++i)
		flags[i]=0;
}