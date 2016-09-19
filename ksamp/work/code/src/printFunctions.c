#include <asm/param.h>      //para la constante HZ
#include "../include/ksamp.h"

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;

void printMainProgram(struct Datos datos){

    long ut = datos.uptime;

    printf("CPU:%s",datos.cpu);
    printf("Version del Kernel de Linux: %s\n",datos.kernel);
    printf("Uptime: %ldD %ld:%02ld:%02ld \n",ut/day, (ut%day)/hour,(ut%hour)/minute,ut%minute);
    printf("El kernel soporta %i sistemas de archivos diferentes\n",datos.filesystems);
}

void printStats(struct Datos datos, int human){

    printf("\nInformacion adicional:\n");

    if(human){
        printf("Tiempo CPU usada para usuario: %.0f segundos = %.2f minutos = %.2f horas\n", datos.userTime/HZ, datos.userTime/(HZ*60), datos.userTime/(HZ*60*60));
        printf("Tiempo CPU usado por el sistema: %.0f segundos = %.2f minutos = %.2f horas\n", datos.sysTime/HZ, datos.sysTime/(HZ*60), datos.sysTime/(HZ*60*60));
        printf("Tiempo en idle: %.0f segundos = %.2f minutos = %.2f horas\n", datos.idleTime/HZ, datos.idleTime/(HZ*60), datos.idleTime/(HZ*60*60));
    }

    else{
        printf("Tiempo CPU usada para usuario: %.0f jiffies\n", datos.userTime);
        printf("Tiempo CPU usado por el sistema: %.0f jiffies\n", datos.sysTime);
        printf("Tiempo en idle: %.0f jiffies\n", datos.idleTime);
    }

    printf("Fecha y hora de booteo: %s",datos.bootTime);
    printf("Cantidad de cambios de contexto: %i\n",datos.contextChanges);
    printf("Cantidad de procesos creados: %i\n",datos.processes);
}

    /**
    * @brief Imprime valores leidos de /proc
    *
    * Es llamada al ingresar la opcion --interval, que muestra informacion avanzada sobre los
    * valores leidos a lo largo del tiempo ingresado, actualizandose automaticamente.
    * Si se solicita la impresion amigable, convierte los valores de memoria de KB a MB para una lectura mas facil de los datos.
    * @param values[] Arreglo con los valores a imprimir
    * @param human Flag de impresion amigable
    * @see calculateInterval()
    */
void printIntervals(struct Interval data, int human){
		printf("Numero de lecturas realizadas: %i\n",data.reads);
		printf("Numero de escrituras realizadas: %i\n",data.writes);
		printf("Numero de peticiones al disco (lecturas + escrituras): %i\n",data.rw);
		if(human) printf("Memoria disponible/total: %i MB/%i MB\n",data.memDisp/1024,data.memTot/1024);
		else	  printf("Memoria disponible/total: %i KB/%i KB\n",data.memDisp,data.memTot);
	    printf("Promedio de carga del sistema en el ultimo minuto: %.2f\n",data.loadAvg);
}

    /**
    * @brief Imprime las variaciones en los valores leidos de /proc
    *
    * Es llamada al ingresar la opcion --differential, que muestra el cambio en los 
    * valores leidos a lo largo del tiempo ingresado, actualizandose automaticamente.
    * Si se solicita la impresion amigable, convierte los valores de memoria de KB a MB para una lectura mas facil de los datos.
    * @param values[] Arreglo con los valores a imprimir
    * @param human Flag de impresion amigable
    * @see calculateInterval()
    */
void printDifferences(struct Interval data, int human){
		printf("Variacion del numero de lecturas realizadas: %i\n",data.reads);
		printf("Variacion del numero de escrituras realizadas: %i\n",data.writes);
		printf("Variacion de peticiones al disco realizadas: %i\n",data.rw);
		if(human) printf("Variacion de la memoria disponible: %i MB             \n",data.memDisp/1024);
		else	  printf("Variacion de la memoria disponible: %i KB             \n",data.memDisp);
	    printf("Variacion de la carga del sistema en el ultimo minuto: %.2f\n",data.loadAvg);
}

    /**
    * @brief Imprime los comandos de ayuda
    *
    * Muestra una lista de los comandos validos del programa, su version
    * corta y larga, y una breve explicacion de cada uno.
    */
void printHelp(){
	printf("Mensaje de ayuda del programa Ksamp\n");
	printf("-s, --sats               Para obtener mas estadisticas de uso del sistema\n");
	printf("-l, --interval x y       Abarca lo anterior, y ademas actualiza las estadisticas\n");
	printf("                         cada 'x' segundos durante 'y' segundos\n");
	printf("-f, --friendly           Expresa los valores en un formato amigable\n");
	printf("-d, --differential       Al ver las estadisticas actualizadas, ver la diferencia");
	printf("                         con respecto al valor en el momento anterior,\n");
	printf("                         en lugar del valor absoluto\n\n");
    printf("                         Para mas informacion, ingrese a la documentacion del\n");
    printf("                         software, que se encuentra en la carpeta /doc\n");
}