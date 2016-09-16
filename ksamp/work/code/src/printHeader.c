#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int printHeader(FILE* fp,char buffer[]){

	fp = fopen("/proc/sys/kernel/hostname","r");
	if (fp == NULL){
		return 1;
	} 
	fgets(buffer, 256+1, fp); 
	fclose(fp);
	printf("Hostname: %s",buffer);

	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf("Fecha y hora actual: %s\n",asctime(timeinfo));

	return 0;
}