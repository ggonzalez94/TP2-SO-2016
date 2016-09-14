#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>

int main (int argc, char* argv[]){

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char * cpuinfo;
	char * kernel;
	char * uptime;
	int filesystems = 0;

	//cabecera con nombre de maquina y fecha y hora actual
	int gethostname(char *name, size_t len);
	char hostname[128];
	gethostname(hostname, sizeof (hostname));
	printf("Nombre de la PC: %s\n", hostname);

	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "Fecha y hora actual: %s\n", asctime (timeinfo) );


	fp = fopen("/proc/cpuinfo", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//imprimo version de cpu
	while ((read = getline(&line, &len, fp)) != -1) {

		cpuinfo = strstr(line,"model name");
		if(cpuinfo != NULL){
			cpuinfo = strstr(cpuinfo,":")+2;
			printf("CPU: %s",cpuinfo);
			break;
		}
	}
	free(line);
	fclose(fp);

	//imprimo version de kernel
	fp = fopen("/proc/version","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	kernel = line + 14;
	kernel = strtok(kernel,"(");
	printf("Version del Kernel de Linux: %s\n",kernel);
	fclose(fp);

	//imprimo el uptime en formato hh:mm:ss
	fp = fopen("/proc/uptime","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	read = getline(&line, &len, fp);
	uptime = strtok(line," ");

	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	long time = atol(uptime);
	printf("Uptime: %ldD %ld:%02ld:%02ld \n",time/day, (time%day)/hour,(time%hour)/minute,time%minute);
	fclose(fp);

	//cantidad de filesystems soportados
	fp = fopen("/proc/filesystems","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		filesystems++;
	}

	printf("El kernel soporta %i sistemas de archivos diferentes\n",filesystems);

	fclose(fp);


	
	return 0;
}