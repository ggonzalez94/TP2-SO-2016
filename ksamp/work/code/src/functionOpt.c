#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ksamp.h"

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;


void printMainProgram(){

	strcpy(path,"/proc/cpuinfo");
    strcpy(before,"model name	: ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    printf("CPU :%s",buff);

    strcpy(path,"/proc/version");
    strcpy(before,"version ");
    strcpy(after,"(");
    parseFile(fp,path,before,after,&buff);
    printf("Version del Kernel de Linux: %s\n",buff);

    strcpy(path,"/proc/uptime");
    strcpy(before," ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	*tiempo = atol(buff);
	printf("Uptime: %ldD %ld:%02ld:%02ld \n",segundos/day, (segundos%day)/hour,(segundos%hour)/minute,segundos%minute);

	getSupFs(fp,&filesystems);
	printf("El kernel soporta %i sistemas de archivos diferentes\n",filesystems);
}


void printStats(void){

	printf("\nInformacion adicional:\n");

   	strcpy(path,"/proc/stat");
    strcpy(before,"cpu");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	buff = strstr(buff," ") + strlen(" ")+1;
	strcpy(buffer,strtok(buff," "));

	int j = 0;

	for (int i = 0; i < 4; ++i)
	{
		if((i==0) | (i==2) | (i==3)){
			CPU_times[j] = atoi(buffer);
			j++;
		}
		strcpy(buffer,strtok(NULL," "));	
	}

	printf("Cantidad de tiempo CPU usada para usuario: %i\n", CPU_times[0]);
   	printf("Cantidad de tiempo CPU usado por el sistema: %i\n", CPU_times[1]);
   	printf("Cantidad de tiempo en idle: %i\n", CPU_times[2]);

	getBootTime(fp,&buff,segundos);
	printf("Fecha y hora de booteo: %s",buff);

    strcpy(path,"/proc/stat");
    strcpy(before,"ctxt ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    printf("Cantidad de cambios de contexto: %s",buff);

	strcpy(path,"/proc/stat");
    strcpy(before,"processes ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    printf("Cantidad de procesos creados: %s",buff);
}


void calculateInterval(double values[]){

	strcpy(path,"/proc/diskstats");
    strcpy(before,"sda");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	buff = strstr(buff," ") + strlen(" ");	
	strcpy(buffer,strtok(buff," "));

	int j = 0;

	for (int i = 0; i < 5; ++i)
	{
		if((i==0) | (i==4)){
			values[j] = atof(buffer);
			j++;
		}
		strcpy(buffer,strtok(NULL," "));	
	}

	values[2] = values[0]+values[1];

	strcpy(path,"/proc/meminfo");
    strcpy(before,"MemTotal:");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    values[3] = atof(buff);
    strcpy(before,"MemFree:");
    parseFile(fp,path,before,after,&buff);
    values[4] = atof(buff);

	strcpy(path,"/proc/loadavg");
    strcpy(before,"");
    strcpy(after," ");
    parseFile(fp,path,before,after,&buff);
    values[5] = atof(buff);
}