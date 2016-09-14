#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getKernelInfo(FILE* fp,char** buff){

	char *line = NULL;
	size_t len = 0;

	fp = fopen("/proc/version","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	getline(&line, &len, fp);
	*buff = line + 14;
	*buff = strtok(*buff,"(");
	fclose(fp);

	return 0;
}