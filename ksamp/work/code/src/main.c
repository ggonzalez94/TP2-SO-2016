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

	return 0;
}