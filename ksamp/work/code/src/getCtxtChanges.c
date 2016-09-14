#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCtxtChanges(FILE* fp,char** buff){

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("/proc/stat", "r");
	if (fp == NULL)
		return 1;

	while ((read = getline(&line, &len, fp)) != -1) {

		*buff = strstr(line,"ctxt ");
		if(*buff != NULL){
			*buff = strstr(*buff," ")+1;
			break;
		}
	}
	free(line);
	fclose(fp);

	return 0;
}
