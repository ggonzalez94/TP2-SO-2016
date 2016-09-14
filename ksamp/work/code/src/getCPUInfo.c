#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCPUInfo(FILE* fp,char** buff){

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("/proc/cpuinfo", "r");
	if (fp == NULL)
		return 1;

	while ((read = getline(&line, &len, fp)) != -1) {

		*buff = strstr(line,"model name");
		if(*buff != NULL){
			*buff = strstr(*buff,":")+2;
			break;
		}
	}
	free(line);
	fclose(fp);

	return 0;
}