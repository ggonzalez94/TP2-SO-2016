#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMemoria(FILE* fp,int memoria[]){

	char *line = NULL;
	size_t len = 0;
	char *buffer = NULL;
	static int resultado[2];
	fp = fopen("/proc/meminfo", "r");
	if (fp == NULL)
		return 1;
	getline(&line, &len, fp);
	while (line != NULL){
		if(strstr(line,"MemTotal")){
			buffer = strstr(line,"MemTotal");
			buffer = strstr(buffer," ") + 8;
			buffer = strtok(buffer," "); //Borro la parte de kb posterior
			memoria[0] = atoi(buffer);
		}
		else if(strstr(line,"MemFree")){
			buffer = strstr(line,"MemFree");
			buffer = strstr(buffer," ") + 8;
			buffer = strtok(buffer," ");
			memoria[1] = atoi(buffer);
			break;
		}
		getline(&line,&len,fp); //Avanzo a la siguiente linea
	}
	//return resultado;
	return 0;
}
