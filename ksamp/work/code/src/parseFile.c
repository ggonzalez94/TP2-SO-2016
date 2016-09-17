#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseFile(FILE* fp, char path[], char before[], char after[], char** buff){

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	fp = fopen(path,"r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		if(strstr(line,before)!=NULL){
			*buff = strstr(line,before) + strlen(before);
			*buff = strtok(*buff,after);
			break;
		}
	}
	fclose(fp);

	return 0;
}