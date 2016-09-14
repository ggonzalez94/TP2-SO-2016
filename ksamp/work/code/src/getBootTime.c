#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getBootTime(FILE* fp, char** btime, long segundos){

	time_t rawtime;
	struct tm *info;

	time( &rawtime );

	rawtime -= segundos;
	info = localtime( &rawtime );
	*btime = asctime(info);

	return 0;
}