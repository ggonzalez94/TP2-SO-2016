#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/launch.h"

extern char* path[50];

void splitArgs(char** args, int flag_index, char** inst1, char** inst2);
void crearNieto(int file_desc[], char** inst2, char** path);
void execvp2(char** args);

int launch(char **args)
{
  char *lastArgument = (char*)malloc(20 * sizeof(char*));
  lastArgument = findLastArgument(args);
  pid_t pid;//, wpid;
  // int status;
  int i=0;
  int changeStdIOResult;
  int file_desc[2];
  char** inst1 = (char**)malloc(20 * sizeof(char*));
  char** inst2 = (char**)malloc(20 * sizeof(char*));

  resetFlags();
  
  caracter[0] = "&";
  caracter[1] = "|";
  caracter[2] = "<";
  caracter[3] = ">";
  caracter[4] = ">>";

  int cant_flags = 0;
  int flag_index=0;

  //cuenta la cantidad de flags, cuenta cada uno por separado, y guarda el indice del mismo
  while(args[i]!=NULL){
  	for(int j=0; j<5; j++){
	  	if(checkFlag(caracter[j],args[i],j)==0){
	  		flags[j]++;
	  		cant_flags++;
	  		flag_index = i;
	  	}
	}
  	i++;
  	if(args[i]==NULL && cant_flags ==0)
  		flag_index=i;
  }

  if(cant_flags>1){
  	printf("Error, puede procesarse solo un caracter especial por instruccion\n");
  	free(inst1);
  	free(inst2);
  	return 1;
  }

  splitArgs(args,flag_index,inst1, inst2);
  

	if (flags[PIPE]){
		if(pipe(file_desc) == -1) {
			perror("Pipe failed");
			exit(1);
		}
	}

  pid = fork();
  switch(pid){
  	case 0: 
    // Child process
  		if(flags[PIPE]){
  			crearNieto(file_desc,inst2, path);
  		}

	    // Cambio standard input/output
	    else if (flags[APPEND]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"a",stdout)) == -1)
	    		exit(EXIT_FAILURE);
	    }
	    else if (flags[OUTP]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"w",stdout)) == -1)
	    		exit(EXIT_FAILURE);
	    }
	    else if (flags[INPT]){
	    	if((changeStdIOResult = changeStdIO(lastArgument,"r+",stdin)) == -1)
	    		exit(EXIT_FAILURE);
	    }

	    execvp2(inst1);
	

	  	break;

  	case -1:
    // Error forking
	    perror("Baash error forking");
	    break;

    
    default:
    // Parent process
  		if(flags[AMP] == 0){
  			if(flags[PIPE]){
	  			close(file_desc[0]);
		        close(file_desc[1]);
		        wait(0);
		        wait(0);
		    }
		    else{
		    	wait(0);
		    }
		    // do {
		    //   wpid = waitpid(pid, &status, WUNTRACED);
		    // } while (!WIFEXITED(status) && !WIFSIGNALED(status));

	      // if(wpid == -1){
	      //   perror("Child process returned -1");
	      //   exit(EXIT_FAILURE);
	      // }
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
  	if (execv(path, args) == -1) {
    	return -1;
  	}
    return 0;
}

int checkFlag(const char* ch, char* word, int flagIndex){
	if(strcmp(ch,word)==0){
  		return 0;
  	}
  	return -1;
}

void resetFlags(){
	for (int i = 0; i < 5; ++i)
		flags[i]=0;
}

void splitArgs(char** args, int flag_index, char** inst1, char** inst2){
	int i=0, j=0;
	while(args[i]!=NULL){
		if(i<flag_index){
			inst1[i] = args[i];
		}

		if(i==flag_index){
			inst1[i]=NULL;
		}

		if(i>flag_index){
			inst2[j] = args[i];
			j++;
		}

		i++;

		if(args[i]==NULL){
			inst2[j]=NULL;
		}
	}
}

void crearNieto(int file_desc[], char** inst2, char** path){
	//nieto
	if(fork() == 0)            //creating 2nd child
	{
		dup2(file_desc[0],STDIN_FILENO);
		close(file_desc[1]);       //closing pipe write
		close(file_desc[0]);
		execvp2(inst2);
	}

	dup2(file_desc[1],STDOUT_FILENO);
	close(file_desc[0]);       //closing pipe read
	close(file_desc[1]);
}

void execvp2(char** args){
	  	if (isRelative(args)){
	  		char new_str[100] = "";
	  		for(int i=0; i<15;i++){
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
	}