#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCPUTime(FILE* fp,int numeros[]){
	//WIP Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle

	char *line = NULL;
	size_t len = 0;
	char *buff = NULL;
	int i = 0;
	int j = 0;

	fp = fopen("/proc/stat", "r");
	if (fp == NULL)
		return 1;
	
	getline(&line, &len, fp);

	buff = strstr(line," ")+2;
	buff = strtok(buff," ");

	while(buff != NULL){
		if (i==0 || i==2 || i==3){
			//printf("%s\n",buff);
			numeros[j] = atoi(buff);
			j++;
		}
		i++;
		buff = strtok(NULL," ");
	}

	free(line);
	fclose(fp);

	return 0;
}