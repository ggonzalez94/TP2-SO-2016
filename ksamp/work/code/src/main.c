#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <getopt.h>
#include "../include/ksamp.h"

const long minute = 60;
const long hour = 60 * 60;
const long day = 60 * 60 * 24;

    /**
    * @brief Punto de inicio del programa
    *
    * Iniciado al ingresar el comando ./ksamp en consola.
    * Admite parametros extra, con los que realiza funciones avanzadas.
    * En base de estos parametros llama a las funciones correspondientes.
    * @see checkInput()
    * @see printMainProgram()
    * @see getStats()
    * @see calculateInterval(double values[])
    */
int main (int argc, char* argv[]){

    struct Datos datos;
    struct Interval interval;
    struct Interval intervalOld;
    struct Interval difference;
    struct Flags flags = {.s=0, .l=0, .h=0, .d=0, .f=0};

	int opt = 0;
	int parametros[2] = {0 , 0};

    static struct option long_options[] = {
        {"stats",     no_argument,       0,  's' },
        {"interval",  required_argument, 0,	 'l' },
        {"help",      no_argument,       0,  'h' },
        {"differential",no_argument,     0,  'd' },
        {"friendly",  no_argument,       0,  'f' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"sl:hdf", long_options, &long_index )) != -1) {
        switch (opt) {
             case 's' : flags.s++;
                 break;
             case 'l' : flags.l++;
             			parametros[0] = atoi(optarg);
             			parametros[1] = atoi(optarg + strlen(optarg)+1);
             	 break;
             case 'h' :	flags.h++;
             	 break;
             case 'd' : flags.d++;
             	 break;
             case 'f' : flags.f++;
             	 break;
             default: printf("Por favor seleccione una opcion valida\n");
             		  printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
                 exit(EXIT_FAILURE);
        }
    }

    checkInput(flags,parametros);

    if(flags.h) {
    	printHelp();
    	return 0;
    }

    printHeader(fp,buffer);
    getMainProgram(&datos);
    printMainProgram(datos);

    if(flags.s) {
        getStats(&datos);
        printStats(datos,flags.f);
    }

    if(flags.l){
    	getStats(&datos);
        printStats(datos,flags.f);

   		calculateInterval(&intervalOld);
    	do{
    		calculateInterval(&interval);

    		if(flags.d){

                difference.reads = interval.reads - intervalOld.reads;
                difference.writes = interval.writes - intervalOld.writes;
                difference.rw = interval.rw - intervalOld.rw;
                difference.memDisp = interval.memDisp - intervalOld.memDisp;
                difference.memTot = interval.memTot - intervalOld.memTot;
                difference.loadAvg = interval.loadAvg - intervalOld.loadAvg;

    			printf("\nMostrando diferencia en los valores cada %i segundos por %i segundos\n",parametros[0], parametros[1]);
    			printDifferences(difference, flags.f);
    		}
    		else{
    			printf("\nMas informacion adicional. Refresco cada %i segundos por %i segundos\n",parametros[0], parametros[1]);
    			printIntervals(interval, flags.f);
    		}

    		
			fflush(stdout);
			sleep(parametros[0]);
			parametros[1] -= parametros[0];
			if(parametros[0] > parametros[1]) break; //si estoy en la ultima vuelta, no subo renglones sino que salgo
			for(int lineas = 0; lineas < 7; lineas++) printf("\x1B[A");  //subo una linea

    	}while(parametros[0]<=parametros[1]);
    }

	return 0;
}

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
        printf("Tiempo CPU usada para usuario: %i segundos = %i minutos = %i horas\n", datos.userTime/60, datos.userTime/3600, datos.userTime/216000);
        printf("Tiempo CPU usado por el sistema: %i segundos = %i minutos = %i horas\n", datos.sysTime/60, datos.sysTime/3600, datos.sysTime/216000);
        printf("Tiempo en idle: %i segundos = %i minutos = %i horas\n", datos.idleTime/60, datos.idleTime/3600, datos.idleTime/216000);
    }

    else{
        printf("Tiempo CPU usada para usuario: %i jiffies\n", datos.userTime);
        printf("Tiempo CPU usado por el sistema: %i jiffies\n", datos.sysTime);
        printf("Tiempo en idle: %i jiffies\n", datos.idleTime);
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

    /**
    * @brief Chequea que los comandos introducidos sean validos.
    *
    * Recibe los parametros extras que se ingresaron, y comprueba que sean validos,
    * que su combinacion sea posible, y que no se repitan. Ademas verifica que los
    * valores ingresados con --interval no sean negativos.
    * Si detecta algun error, llama a la funcion exitAndHelp().
    * @param flags[] Un arreglo con los comandos adicionales ingresados
    * @param intervals[] Un arreglo con los valores pasados al comando -l
    * @see exitAndHelp()
    */
void checkInput(struct Flags flags, int parametros[]){
	//help no puede combinarse con nada
	if(flags.h && (flags.s || flags.l || flags.d || flags.f)) exitAndHelp();
	//chequeo combinaciones invalidas de -s
	if(flags.s && (flags.l || flags.d)) exitAndHelp();
	//-d y -f no pueden llamarse juntas (no sin -l)
	if((flags.d && flags.f) && !flags.l) exitAndHelp();

	//miro repeticiones de flags
    if(flags.s>1 || flags.l>1 || flags.h>1 || flags.d>1 || flags.f>1)
        exitAndHelp();

	//miro valores incorrectos de -l
	if((parametros[0] < 1 || parametros[1] < 1) && flags.l) exitAndHelp();
}

    /** @brief Muestra un mensaje de error y finaliza el programa.
     *
     *  Es llamada cuando se ingresan parametros incorrectos al llamar al programa
     *  Indica al usuario como ver la lista de comandos permitidos y
     *  luego finaliza la ejecucion del programa.
     *  @see checkInput()
     */
void exitAndHelp(){
	printf("Por favor seleccione una opcion valida\n");
	printf("Ingrese la opcion --help o -h para obtener ayuda\n");	
	exit(EXIT_FAILURE);
}