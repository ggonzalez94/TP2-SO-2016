#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>

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

	// getBootTime(fp,&buff,segundos);
	// printf("Fecha y hora de booteo: %s\n",buff);

	// getCtxtChanges(fp,&buff);
	// printf("Cantidad de cambios de contexto: %s\n",buff);

	// getProcesses(fp,&buff);
	// printf("Cantidad de procesos creados: %s\n",buff);


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




