#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>
#include <getopt.h>

#include "../include/ksamp.h"

int main (int argc, char* argv[]){

	filesystems=0;
	long* tiempo = &segundos;
	printHeader(fp,buffer);
	
	getCPUInfo(fp,&buff);
	printf("CPU: %s",buff);

	getKernelInfo(fp,&buff);
	printf("Version del Kernel de Linux: %s\n",buff);

	getUpTime(fp,tiempo);
	printf("Uptime: %ldD %ld:%02ld:%02ld \n",segundos/day, (segundos%day)/hour,(segundos%hour)/minute,segundos%minute);

	getSupFs(fp,&filesystems);
	printf("El kernel soporta %i sistemas de archivos diferentes\n",filesystems);

	int opt= 0;

	//Specifying the expected options
    static struct option long_options[] = {
        {"stats",     no_argument,       0,  's' },
        {"interval",  required_argument, 0,	 'l' },
        {"help",      no_argument,       0,  'h' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sr:h", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : stats();
                 break;
             case 'r' : printf("Opcion r con argumento %s\n",optarg);
             	 break;
             case 'h' : printHelp();
             	 break;
             default: printf("Seleccione una opcion valida\n");
                 // exit(EXIT_FAILURE);
        }
    }
	return 0;
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

	printf("Mensaje de ayuda del programa Ksamp\n");
}