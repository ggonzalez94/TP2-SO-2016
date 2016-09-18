#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <getopt.h>
#include "../include/ksamp.h"

int main (int argc, char* argv[]){

	int opt= 0;
	int intervals[2] = {0 , 0};
	int flags[5] = {0,0,0,0,0};

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
             case 's' : flags[0]=1;
                 break;
             case 'l' : flags[1]=1;
             			intervals[0] = atoi(optarg);
             			intervals[1] = atoi(optarg + strlen(optarg)+1);
             	 break;
             case 'h' :	flags[2]=1;
             	 break;
             case 'd' : flags[3]=1;
             	 break;
             case 'f' : flags[4]=1;
             	 break;
             default: printf("Por favor seleccione una opcion valida\n");
             		  printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
                 exit(EXIT_FAILURE);
        }
    }

    if(flags[2]) {
    	printHelp();
    	return 0;
    }

    filesystems = 0;
    tiempo = &segundos;
    printHeader(fp,buffer);
    printMainProgram();

    if(flags[0]) printStats();

    if(flags[1]){
    	printStats();

   		calculateInterval(oldvalues);
    	do{
    		calculateInterval(values);

    		if(flags[3]){
    			for (int i = 0; i < 6; ++i)
    			{
    				difference[i]=values[i]-oldvalues[i];
    			}
    			printf("\nMostrando diferencia en los valores cada %i segundos\n",intervals[0]);
    			printDifferences(difference, flags[4]);
    		}
    		else{
    			printf("\nMas informacion adicional. Refresco cada %i segundos\n",intervals[0]);
    			printIntervals(values, flags[4]);
    		}

    		
			fflush(stdout);
			sleep(intervals[0]);
			intervals[1] -= intervals[0];
			if(intervals[0] > intervals[1]) break; //si estoy en la ultima vuelta, no subo renglones sino que salgo
			for(int lineas = 0; lineas < 7; lineas++) printf("\x1B[A");  //subo una linea

    	}while(intervals[0]<=intervals[1]);
    }

	return 0;
}

void printIntervals(double values[], int human){
		printf("Numero de lecturas realizadas: %.0f\n",values[0]);
		printf("Numero de escrituras realizadas: %.0f\n",values[1]);
		printf("Numero de peticiones al disco (lecturas + escrituras): %.0f\n",values[2]);
		if(human) printf("Memoria disponible/total: %.0f MB/%.0f MB\n",values[4]/1024,values[3]/1024);
		else	  printf("Memoria disponible/total: %.0f KB/%.0f KB\n",values[4],values[3]);
	    printf("Promedio de carga del sistema en el ultimo minuto: %.2f\n",values[5]);
}

void printDifferences(double values[], int human){
		printf("Variacion del numero de lecturas realizadas: %.0f\n",values[0]);
		printf("Variacion del numero de escrituras realizadas: %.0f\n",values[1]);
		printf("Variacion de peticiones al disco realizadas: %.0f\n",values[2]);
		if(human) printf("Variacion de la memoria disponible: %.0f MB             \n",values[4]/1024);
		else	  printf("Variacion de la memoria disponible: %.0f KB             \n",values[4]);
	    printf("Variacion de la carga del sistema en el ultimo minuto: %.2f\n",values[5]);
}

void printHelp(){
	printf("Mensaje de ayuda del programa Ksamp\n");
	printf("-s, --sats               Para obtener mas estadisticas de uso del sistema\n");
	printf("-l, --interval x y       Abarca lo anterior, y ademas actualiza las estadisticas\n");
	printf("                         cada 'x' segundos durante 'y' segundos\n");
	printf("-f, --friendly           Expresa los valores en un formato amigable\n");
	printf("-d, --differential       Al ver las estadisticas actualizadas, ver la diferencia");
	printf("                         con respecto al valor en el momento anterior,\n");
	printf("                         en lugar del valor absoluto\n");
}