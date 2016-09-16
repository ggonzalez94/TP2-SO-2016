#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>
#include <getopt.h>

#include "../include/ksamp.h"

int main (int argc, char* argv[]){

	getMemoria(fp,memoria);
	printf("%s\n","Mostrando memoria test" );
	printf("%i, %i\n",memoria[0],memoria[1]);

	int opt= 0;

	int helpflag = 0, statsflag = 0, intervalflag = 0;


    static struct option long_options[] = {
        {"stats",     no_argument,       0,  's' },
        {"interval",  required_argument, 0,	 'l' },
        {"help",      no_argument,       0,  'h' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sl:h", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : statsflag=1;
                 break;
             case 'l' : printf("Opcion l con argumento %s\n",optarg);
             	 break;
             case 'h' : helpflag=1;
             	 break;
             default: printf("Seleccione una opcion valida\n");
                 exit(EXIT_FAILURE);
        }
    }

    if(helpflag) {
    	printHelp();
    	return 0;
    }

    tiempo = &segundos;
    printMainProgram();

    if(statsflag) stats();

	return 0;
}

void printMainProgram(){
	printHeader(fp,buffer);
	
	getCPUInfo(fp,&buff);
	printf("CPU: %s",buff);

	getKernelInfo(fp,&buff);
	printf("Version del Kernel de Linux: %s\n",buff);

	getUpTime(fp,tiempo);
	printf("Uptime: %ldD %ld:%02ld:%02ld \n",segundos/day, (segundos%day)/hour,(segundos%hour)/minute,segundos%minute);

	getSupFs(fp,&filesystems);
	printf("El kernel soporta %i sistemas de archivos diferentes\n",filesystems);
}


void stats(void){

	printf("\nInformacion adicional:\n");
    getCPUTime(fp,CPU_times);
   	printf("Cantidad de tiempo CPU usada para usuario: %i\n", CPU_times[0]);
   	printf("Cantidad de tiempo CPU usado por el sistema: %i\n", CPU_times[1]);
   	printf("Cantidad de tiempo en idle: %i\n", CPU_times[2]);

	getBootTime(fp,&buff,segundos);
	printf("Fecha y hora de booteo: %s",buff);

	getCtxtChanges(fp,&buff);
	printf("Cantidad de cambios de contexto: %s",buff);

	getProcesses(fp,&buff);
	printf("Cantidad de procesos creados: %s",buff);
}

void printHelp(){

	printf("\nMensaje de ayuda del programa Ksamp\n");
}