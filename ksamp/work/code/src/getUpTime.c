#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getUpTime(FILE* fp, long* tiempo){

	char *line = NULL;
	size_t len = 0;

	fp = fopen("/proc/uptime","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	getline(&line, &len, fp);
	line = strtok(line," ");
	*tiempo = atol(line);
	
	fclose(fp);

	return 0;
}
