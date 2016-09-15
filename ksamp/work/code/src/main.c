#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>
#include <getopt.h>

#include "../include/ksamp.h"

void specialf(void);

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
        {"prueba",	  required_argument, 0,	 'r' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sr:", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : specialf();
                 break;
             case 'r' : printf("Opcion r con argumento %s\n",optarg);
             	 break;
             default: printf("Seleccione una opcion valida\n");
                 // exit(EXIT_FAILURE);
        }
    }

					//WIP Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle

					// char *line = NULL;
					// size_t len = 0;

					// fp = fopen("/proc/stat", "r");
					// if (fp == NULL)
					// 	return 1;
					
					// getline(&line, &len, fp);

					// 	// buff = strtok(line,"cpu");
					// 	// if(buff != NULL){
					// 	// 	buff = strstr(buff," ")+1;
					// 	// }

					// buff = strtok(line," ");

					// for(int i=0; i<4; i++){

					// }

					// while(buff != NULL){
					// 	printf("%s\n",buff);
					// 	buff = strtok(NULL," ");
					// }

					
					// // printf("%s\n",buff);

					// free(line);
					// fclose(fp);
	
	return 0;
}


void specialf(void){
	getBootTime(fp,&buff,segundos);
	printf("\nFecha y hora de booteo: %s",buff);

	getCtxtChanges(fp,&buff);
	printf("Cantidad de cambios de contexto: %s",buff);

	getProcesses(fp,&buff);
	printf("Cantidad de procesos creados: %s\n",buff);
}