#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

#include "../include/ksamp.h"

void calculateInterval(int[], double values[]);
void printIntervals (double values[]);

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
             case 's' : verificarInput(flag);
             			flag=1;
                 break;
             case 'l' : verificarInput(flag);
             			flag=2;
             			intervals[0] = atoi(optarg);
             			intervals[1] = atoi(optarg + strlen(optarg)+1);
             	 break;
             case 'h' : verificarInput(flag);
             			flag=3;
             	 break;
             default: printf("Por favor seleccione una opcion valida\n");
             		  printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
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

    	do{
    		calculateInterval(intervals,values);
    		printf("\nMas informacion adicional. Refresco cada %i segundos\n",intervals[0]);
			printIntervals(values);
    		intervals[1] -= intervals[0];
			fflush(stdout);
			sleep(intervals[0]);

			if(intervals[0] > intervals[1]) break; //si estoy en la ultima vuelta, no subo renglones sino que salgo
			for(int lineas = 0; lineas < 7; lineas++) printf("\x1B[A");  //subo una linea

    	}while(intervals[0]<=intervals[1]);
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

    strcpy(path,"/proc/uptime");
    strcpy(before," ");
    strcpy(after,"");
    parseFile(fp,path,before,after,&buff);

	*tiempo = atol(buff);
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

void calculateInterval(int intervals[], double values[]){

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

void printIntervals(double values[]){
		printf("Numero de peticiones al disco realizadas: %.0f\n",values[2]);
		printf("Numero de lecturas realizadas: %.0f\n",values[0]);
		printf("Numero de escrituras realizadas: %.0f\n",values[1]);
		printf("Memoria disponible/total %.0f KB/%.0f KB\n",values[4],values[3]);
	    printf("Promedio de carga del sistema en el ultimo minuto: %.2f\n",values[5]);
}

void printHelp(){
	printf("Mensaje de ayuda del programa Ksamp\n");
	printf("-s, --sats               Para obtener mas estadisticas de uso del sistema\n");
	printf("-l, --interval x y       Abarca lo anterior, y ademas actualiza las estadisticas\n");
	printf("                         cada 'x' segundos durante 'y' segundos\n");
}

void verificarInput(int flag){
	if(flag != 0) { //si el comando ingresado no es correcto
		printf("Por favor seleccione una opcion valida\n");
		printf("Ingrese la opcion --help o -h para obtener ayuda\n");
		exit(EXIT_FAILURE);
	}
}