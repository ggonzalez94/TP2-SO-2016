# TP1-SO-2016 

### Laboratorio 1 - Observando el Comportamiento de Linux - 2016 
![Icono](https://t3.ftcdn.net/jpg/00/96/00/98/160_F_96009890_zdJu97gT4d6zoltOWyQXdbbzdkSi9Glz.jpg)
___
|Autores                               |
|------------------------------------|
|Gonzalez Somerstein Gustavo -7721064  |
|Maero Facundo - 38479441              |

## 1. Descripción del programa
---
El programa KSamp permite inspeccionar información interna del Kernel de Linux, particularmente en el directorio /proc. 

El software muestra:

 - El nombre del equipo donde se ejecuta, y la fecha y hora actual como mensaje de bienvenida.
 - El tipo y modelo de CPU, y su velocidad de clock en MHz
 - La versión del Kernel de Linux del sistema
 - El tiempo que ha estado encendido el equipo (D hh:mm:ss)
 - La cantidad de sistemas de archivos diferentes que soporta el Kernel

Acepta parámetros adicionales para visualizar más informacion, como:

 - Cantidad de tiempo de CPU utilizado para usuarios, sistema y proceso idle.
 - Cantidad de cambios de contexto.
 - Fecha y hora cuando el sistema fue iniciado
 - Número de procesos creados desde el inicio del sistema

Además, permite mostrar información actualizada cada cierto tiempo, para tener una mejor idea del funcionamiento del sistema:

 - Número de peticiones a disco realizadas. 
 - Cantidad de memoria configurada en el hardware. 
 - Cantidad de memoria disponible. 
 - Lista de los promedios de carga de en el último minuto. 
 - Información amigable al usuario, con unidades fáciles de leer.
 - Información diferencial, para visualizar los cambios en los últimos segundos.

## 2. Instrucciones de instalación
---
 - Para instalar el programa, descargue el repositorio en su computadora.
 - Luego, mediante la terminal, ejecute los siguientes comandos para descomprimir el archivo .zip y situarse en la carpeta donde se halla el Makefile:
```
% cd Downloads
% unzip TP1-SO-2016-master.zip
% cd TP1-SO-2016-master/ksamp/work/code
```
 - Seguidamente, para crear la carpeta donde se almacenan los archivos .o, ejecute:
```
% mkdir obj
```
 - Para comenzar el proceso de compilación y linkeo de los archivos, ejecute el comando:
```
% make
```
 
 - Una vez terminado, para visualizar en consola la información, ejecute el comando: 
```
% ./ksamp
```
 - Además, puede agregar los siguientes modificadores para visualizar información adicional:
```
-s, --stats
-f, --friendly
-d, --differential
-l, --interval 'PARAM1' 'PARAM2'

```
Donde ```PARAM1``` y ```PARAM2``` son el tiempo de refresco de la informacion, y el tiempo total que se quiere monitorear.

 - Para obtener ayuda, ejecute:
```
% ./ksamp -h
% ./ksamp -help
```
Al compilar y linkear, se genera un archivo donde se guardan los posibles errores y advertencias que encuentre el programa CppCheck al realizar el análisis estático del código. Este archivo se encuentra en:
```
ksamp/work/code/err.txt
```
Si desea más información, remítase a la documentación proporcionada, que se encuentra en la ruta ```\ksamp\doc\html\index.html```
