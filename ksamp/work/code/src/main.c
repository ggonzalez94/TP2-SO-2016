#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <getopt.h>
#include "../include/ksamp.h"

    /**
    * @brief Punto de inicio del programa
    *
    * Iniciado al ingresar el comando ./ksamp en consola.
    * Admite parametros extra, con los que realiza funciones avanzadas.
    * En base de estos parametros llama a las funciones correspondientes.
    * @see checkInput()
    * @see printMainProgram()
    * @see getStats()
    * @see calculateInterval(double values[])
    */
int main (int argc, char* argv[]){

    struct Datos datos;
    struct Interval interval;
    struct Interval intervalOld;
    struct Interval difference;
    struct Flags flags = {.s=0, .l=0, .h=0, .d=0, .f=0};

	int opt = 0;
	int parametros[2] = {0 , 0};

    static struct option long_options[] = {
        {"stats",     no_argument,       0,  's' },
        {"interval",  required_argument, 0,	 'l' },
        {"help",      no_argument,       0,  'h' },
        {"differential",no_argument,     0,  'd' },
        {"friendly",  no_argument,       0,  'f' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sl:hdf", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : flags.s++;
                 break;
             case 'l' : flags.l++;
             			parametros[0] = atoi(optarg);
             			parametros[1] = atoi(optarg + strlen(optarg)+1);
             	 break;
             case 'h' :	flags.h++;
             	 break;
             case 'd' : flags.d++;
             	 break;
             case 'f' : flags.f++;
             	 break;
             default: printf("Por favor seleccione una opcion valida\n");
             		  printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
                 exit(EXIT_FAILURE);
        }
    }

    checkInput(flags,parametros);

    if(flags.h) {
    	printHelp();
    	return 0;
    }

    printHeader(fp,buffer);
    getMainProgram(&datos);
    printMainProgram(datos);

    if(flags.s) {
        getStats(&datos);
        printStats(datos,flags.f);
    }

    if(flags.l){
    	getStats(&datos);
        printStats(datos,flags.f);

   		calculateInterval(&intervalOld);
    	do{
    		calculateInterval(&interval);

    		if(flags.d){

                restarIntervalos(interval, intervalOld, &difference);
                actualizarIntervalos(&intervalOld,interval);
    			printf("\nMostrando diferencia en los valores cada %i segundos por %i segundos\n",parametros[0], parametros[1]);
    			printDifferences(difference, flags.f);
    		}
    		else{
    			printf("\nMas informacion adicional. Refresco cada %i segundos por %i segundos\n",parametros[0], parametros[1]);
    			printIntervals(interval, flags.f);
    		}

    		
			fflush(stdout);
			sleep(parametros[0]);
			parametros[1] -= parametros[0];
			if(parametros[0] > parametros[1]) break; //si estoy en la ultima vuelta, no subo renglones sino que salgo
			for(int lineas = 0; lineas < 7; lineas++) printf("\x1B[A");  //subo una linea

    	}while(parametros[0]<=parametros[1]);
    }

	return 0;
}

    /**
    * @brief Chequea que los comandos introducidos sean validos.
    *
    * Recibe los parametros extras que se ingresaron, y comprueba que sean validos,
    * que su combinacion sea posible, y que no se repitan. Ademas verifica que los
    * valores ingresados con --interval no sean negativos.
    * Si detecta algun error, llama a la funcion exitAndHelp().
    * @param flags[] Un arreglo con los comandos adicionales ingresados
    * @param intervals[] Un arreglo con los valores pasados al comando -l
    * @see exitAndHelp()
    */
void checkInput(struct Flags flags, int parametros[]){
	//help no puede combinarse con nada
	if(flags.h && (flags.s || flags.l || flags.d || flags.f)) exitAndHelp();
	//chequeo combinaciones invalidas de -s
	if(flags.s && (flags.l || flags.d)) exitAndHelp();
	//-d y -f no pueden llamarse juntas (no sin -l)
	if((flags.d && flags.f) && !flags.l) exitAndHelp();

	//miro repeticiones de flags
    if(flags.s>1 || flags.l>1 || flags.h>1 || flags.d>1 || flags.f>1)
        exitAndHelp();

	//miro valores incorrectos de -l
	if((parametros[0] < 1 || parametros[1] < 1) && flags.l) exitAndHelp();
}

    /** @brief Muestra un mensaje de error y finaliza el programa.
     *
     *  Es llamada cuando se ingresan parametros incorrectos al llamar al programa
     *  Indica al usuario como ver la lista de comandos permitidos y
     *  luego finaliza la ejecucion del programa.
     *  @see checkInput()
     */
void exitAndHelp(){
	printf("Por favor seleccione una opcion valida\n");
	printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
	exit(EXIT_FAILURE);
}

void restarIntervalos(struct Interval interval, struct Interval intervalOld, struct Interval* difference){
    difference->reads = interval.reads - intervalOld.reads;
    difference->writes = interval.writes - intervalOld.writes;
    difference->rw = interval.rw - intervalOld.rw;
    difference->memDisp = interval.memDisp - intervalOld.memDisp;
    difference->memTot = interval.memTot - intervalOld.memTot;
    difference->loadAvg = interval.loadAvg - intervalOld.loadAvg;
}

void actualizarIntervalos(struct Interval* intervalOld, struct Interval interval){
    intervalOld->reads = interval.reads;
    intervalOld->writes = interval.writes;
    intervalOld->rw  = interval.rw;
    intervalOld->memDisp = interval.memDisp;
    intervalOld->memTot = interval.memTot;
    intervalOld->loadAvg = interval.loadAvg;
}