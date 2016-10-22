/** @file launch.c
 *  @brief Contiene todas las funciones relacionadas a la ejecucion de programas en Linux.
 *
 *  Aqui se identifican modificadores de la instruccion ingresada, se la ejecuta, se detecta
 *  si es un path absoluto o relativo, y se llevan a cabo los distintos mecanismos relacionados con
 *  pipes y descriptores de archivos.
 *
 *  @author Facundo Maero
 *  @author Gustavo Gonzalez
 */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/launch.h"
#include "../include/shared.h"

extern char* path[PATH_MAX];

  /**
  * @brief Funcion principal del archivo. Gestiona la ejecucion de la instruccion.
  *
  * Chequea la cantidad de flags, detecta su tipo y realiza las operaciones necesarias segun el caso.
  * Al solicitar un pipe, crea dos procesos y modifica sus file descriptors para permitir su comunicacion.
  * Al solicitar guardar o leer de un archivo tambien modifica los file descriptors.
  * El proceso padre se encarga de esperar a los hijos, a menos que se solicite una ejecucion en paralelo.
  *
  * @param args Una cadena de strings previamente parseada, lista para ser ejecutada.
  * @return 1 para continuar la ejecucion del programa Baash.
  */

int launch(char **args)
{
  pid_t pid;//, wpid;
  // int status;
  int changeStdIOResult;
  int file_desc[2];
  char** inst1 = (char**)malloc(STANDARD_BUFFER * sizeof(char*));
  char** inst2 = (char**)malloc(STANDARD_BUFFER * sizeof(char*));

  resetFlags();
  int flag_index = 0;
  int cant_flags = countFlags(args,&flag_index);

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
  			crearNieto(file_desc,inst2);
  		}
      else{
        // Cambio standard input/output
        char *lastArgument = (char*)malloc(20 * sizeof(char*));
        findLastArgument(args,lastArgument);

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
        free(lastArgument);
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

  /**
  * @brief Cambia la entrada o salida estandar del proceso actual
  *
  * Cambia la entrada o salida estandar del proceso actual, creando un descriptor de archivo con el nombre
  * que se le especifica, su modo y reemplazando un descriptor por defecto.
  *
  * @param lastArgument El nombre del archivo de donde se leera o escribira contenido.
  * @param mode el modo con el que se creara el file descriptor. Puede ser para lectura (r), escritura (w) o append (a).
  * @param stream El file descriptor por defecto a sert reemplazado.
  * @return 0 en caso exitoso, -1 al fallar la creacion del file descriptor.
  */

int changeStdIO(char* lastArgument, const char* mode, FILE *stream){
    	FILE *fp;
    	fp = freopen(lastArgument,mode,stream);
    	if(fp == NULL)
    		return -1;
    	else
    		return 0;
    }


  /**
  * @brief Identifica el ultimo elemento de la cadena de chars ingresada como parametro.
  *
  * Segun la cadena de caracteres que se le provea, ejecuta un bucle hasta encontrar su ultimo elemento,
  * y lo copia en el parametro lastArgument.
  *
  * @param args Una cadena de strings previamente parseada, desde donde se buscara su ultimo elemento.
  * @param lastArgument el puntero a char donde se copiara el elemento encontrado.
  */
void findLastArgument(char **args,char *lastArgument){
  int i = 0 ;
  while(args[i] != NULL){
    i++;
  }
  strcpy(lastArgument,args[i-1]);
}

  /**
  * @brief Detecta si el path ingresado es de tipo relativo o absoluto.
  *
  * Evalua el primer caracter del path ingresado. Si el mismo es "/" entiende que
  * es de tipo absoluto. Caso contrario, es relativo.
  *
  * @param args Una cadena de strings a detectar si es absoluta o relativa al path actual.
  * @return 1 si el path ingresado es relativo, 0 si es absoluto.
  */
int isRelative(char** path){

	if(strstr(*path,"/")==NULL){
		return 1;
	}
	return 0;
}

  /**
  * @brief Ejecuta el comando pasado como parametro, usando el path que se le provee.
  * 
  * Utiliza la system call execv, que recibe el path absoluto del programa a ejecutar,
  * y la lista de argumentos a pasarle al mismo.
  *
  * @param args Un conjunto de argumentos a pasarle al programa a ejecutar.
  * @param path la ruta absoluta del programa a ejecutar.
  * @return 0 si el comando pudo ser ejecutado, -1 si no se encontro en el path provisto.
  */
int runCommand(char **args, char *path){
  	if (execv(path, args) == -1) {
    	return -1;
  	}
    return 0;
}


  /**
  * @brief Compara dos strings para saber si son iguales o no.
  * 
  * Compara dos strings caracter a caracter, y determina si son iguales o no.
  * Es usada para identificar si la palabra es un modificador valido o no (& < > >> |).
  *
  * @param ch El modificador a ser comparado con un token ingresado por teclado.
  * @param word Un token ingresado por teclado, a comparar con un modificador predefinido.
  * @return 0 si el token es un modificador, -1 caso contrario.
  */
int checkFlag(const char* ch, char* word){
	if(strcmp(ch,word)==0){
  		return 0;
  	}
  	return -1;
}


/**
  * @brief Setea el arreglo de flags a 0.
  * 
  * Vuelve a cero la cuenta de la cantidad de flags encontrados, preparando
  * el arreglo para la proxima instruccion recibida.
  *
  */
void resetFlags(){
	for (int i = 0; i < TOTAL_FLAGS; i++)
		flags[i]=0;
}


/**
  * @brief Separa la instruccion ingresada por teclado en dos.
  * 
  * En funcion de la posicion del caracter modificador, separa la instruccion en dos.
  * Estas dos se utilizan al usar el pipe, pasando una instruccion a cada proceso.
  *
  * @param args La instruccion a separar.
  * @param flag_index La posicion del caracter modificador, desde donde se separara la cadena.
  * @param inst1 Aqui se guardara la instruccion 1 (antes del flag).
  * @param inst2 Aqui se guardara la instruccion 2 (despues del flag).
  */
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


/**
  * @brief Realiza un segundo fork si se solicito hacer pipe.
  * 
  * El proceso hijo hace un fork, y el proceso nieto ejecuta una de las dos
  * instrucciones separadas previamente. El pipe se acomoda acorde a lo necesario.
  *
  * @param file_desc[] El pipe previamente inicializado
  * @param inst2 La instruccion a ejecutar por el proceso nieto.
  */
void crearNieto(int file_desc[], char** inst2){
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


/**
  * @brief Ejecuta el programa solicitado buscandolo en el PATH de Linux.
  * 
  * Verifica si el comando igresado es relativo o absoluto, y lo intenta ejecutar
  * con la syscall execv. Si no se pudo ejecutar, imprime un error.
  *
  * @param args La instruccion a ejecutar.
  */
void execvp2(char** args){
	  	if (isRelative(args)){
	  		char new_str[100] = "";
	  		int i = 0;
	  		while (path[i] != NULL){
	  			strcat(new_str,path[i]);
				strcat(new_str,"/");
				strcat(new_str, args[0]);
				runCommand(args,new_str);

	  			//limpio el string para probar de nuevo
	  			new_str[0] = 0;
	  			i++;
	  		}
	  		//Si no se encontro el comando imprimo el error
	  		perror("Baash error executing command");
	  		exit(EXIT_FAILURE);
	  	}

	  	else if(runCommand(args,args[0]) == -1){
	  		//Si retorna es porque hubo un error
			perror("Baash error executing command");
		    exit(EXIT_FAILURE);
	  	}
}

/**
  * @brief Cuenta los flags en la cadena, y su posicion (indice).
  * 
  * Cuenta la cantidad de flags en la cadena, su posicion y tipo de cada uno.
  * Para ello compara elemento a elemento con las distintas posibilidades de flag.
  *
  * @param args La cadena a procesar.
  * @param flag_index Por referencia se indica aqui el incide en el arreglo del ultimo flag encontrado.
  * @return cabt_flags La cantidad de flags encontrados. Deberia ser 1 para un comando correcto.
  */
int countFlags(char **args,int *flag_index){
  int cant_flags = 0;
  int i=0;
  //cuenta la cantidad de flags, cuenta cada uno por separado, y guarda el indice del mismo
  while(args[i]!=NULL){
    for(int j=0; j<TOTAL_FLAGS; j++){
      if(checkFlag(caracter[j],args[i])==0){
        flags[j]++;
        cant_flags++;
        *flag_index = i;
      }
  }
    i++;
    if(args[i]==NULL && cant_flags ==0)
      *flag_index=i;
  }
  return cant_flags;
}
