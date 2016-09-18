#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    /**
    * @brief Calcula la cantidad de sistemas de archivos soportados.
    *
    * Lee el archivo filesystems y cuenta en un bucle la cantidad de sistemas de archivos soportados por el Kernel.
    * @param fp File Descriptor, utilizado para abrir los archivos necesarios como lectura.
    * @param filesystems Puntero a tipo int, donde se va contando la cantidad de filesystems soportados.
    */
int getSupFs(FILE* fp,int* filesystems){

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	*filesystems = 0;

	fp = fopen("/proc/filesystems","r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		(*filesystems)++;
	}
	fclose(fp);

	return 0;
}