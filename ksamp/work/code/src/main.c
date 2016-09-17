#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>
#include <getopt.h>

#include "../include/ksamp.h"

void printInterval(int[]);

int main (int argc, char* argv[]){

	int opt= 0;
	int flag = 0;
	int intervals[2];

    static struct option long_options[] = {
        {"stats",     no_argument,       0,  's' },
        {"interval",  required_argument, 0,	 'l' },
        {"help",      no_argument,       0,  'h' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sl:h", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : flag=1;
                 break;
             case 'l' : flag=2;
             			intervals[0] = atoi(optarg);
             			intervals[1] = atoi(optarg + strlen(optarg)+1);
             	 break;
             case 'h' : flag=3;
             	 break;
             default: printf("Seleccione una opcion valida\n");
                 exit(EXIT_FAILURE);
        }
    }

    if(flag==3) {
    	printHelp();
    	return 0;
    }

    filesystems = 0;
    tiempo = &segundos;
    printMainProgram();

    if(flag==1) stats();

    if(flag==2){
    	stats();
    	printInterval(intervals);
    }

	return 0;
}

void printMainProgram(){
	printHeader(fp,buffer);

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

	getUpTime(fp,tiempo);
	printf("Uptime: %ldD %ld:%02ld:%02ld \n",segundos/day, (segundos%day)/hour,(segundos%hour)/minute,segundos%minute);

	getSupFs(fp,&filesystems);
	printf("El kernel soporta %i sistemas de archivos diferentes\n",filesystems);
}


void stats(void){

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
		if(i==0 | i==2 | i==3){
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
    printf("Cantidad de cambios de contexto: %s\n",buff);

	strcpy(path,"/proc/stat");
    strcpy(before,"processes ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    printf("Cantidad de procesos creados: %s",buff);

	// getMemoria(fp,memoria);
	strcpy(path,"/proc/meminfo");
    strcpy(before,"MemTotal:");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);
    memoria[0] = atoi(buff);
    strcpy(before,"MemFree:");
    parseFile(fp,path,before,after,&buff);
    memoria[1] = atoi(buff);
	printf("Memoria disponible/total %i/%i\n",memoria[1],memoria[0]);
}

void printInterval(int intervals[]){
	printf("%i\n",intervals[0]);
	printf("%i\n",intervals[1]);
}

void printHelp(){

	printf("\nMensaje de ayuda del programa Ksamp\n");
}