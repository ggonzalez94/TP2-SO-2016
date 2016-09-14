#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getSupFs(FILE* fp,int* filesystems){

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("/proc/filesystems","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		(*filesystems)++;
	}
	fclose(fp);

	return 0;
}