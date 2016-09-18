#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    /**
    * @brief Parsea un archivo en busca de una cadena de caracteres.
    *
    * Recibido un path, una cadena a buscar y delimitadores, busca en el archivo
    * y guarda la cadena en buff. Si no puede abrir el archivo termina el programa.
    * Busca iterativamente hasta encontrar la primer ocurrencia del string buscado
    * y la recorta en base a los delimitadores.
    * @param fp File Descriptor, usado para abrir un archivo como lectura
    * @param path[] Cadena de caracteres con la ruta en la que se buscara el archivo
    * @param before[] String con el delimitador que se encuentra antes de la cadena deseada
    * @param after[] String con el delimitador que se encuentra despues de la cadena deseada
    * @param buff Puntero a char donde se almacena el resultado
    */
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