#include <time.h>
    /**
    * @brief Obtiene la hora de inicio del sistema
    *
    * Calcula la hora de inicio del sistema, restando el uptime en segundos a la hora actual, y convirtiendolo en un formato
    * legible.
    * @param btime Cadena de caracteres donde se almacena el valor obtenido, para ser procesado fuera de la llamada a funcion.
    * @param segundos El tiempo en segundos que estuvo encendido el sistema
    */
int getBootTime(char** btime, long segundos){

	time_t rawtime;
	struct tm *info;

	time( &rawtime );
	rawtime -= segundos;
	info = localtime( &rawtime );
	*btime = asctime(info);

	return 0;
}