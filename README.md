# TP2-SO-2016 

### Laboratorio 2 - Un Baash - 2016 
![Icono](http://i0.wp.com/blog.desdelinux.net/wp-content/uploads/2012/10/terminal5.jpg?w=640)
___
|Autores                               |
|------------------------------------|
|Gonzalez Somerstein Gustavo -7721064  |
|Maero Facundo - 38479441              |

## 1. Descripción del programa
---
El programa Baash es un intérprete de línea de comandos, que se ejecuta sobre el shell nativo de Linux, y permite ejecutar diversas instrucciones, incluídas en el sistema operativo, o propios del programa.

Sus comandos internos son:

- Cambiar de directorio actual, recibiendo paths relativos o absolutos
```
% cd 'ruta deseada'
```

- Subir un nivel en el árbol de directorios:
```
% cd ..
```
- Mostrar ayuda:
```
% help
```
- Salir del Baash:
```
% exit
```

Además, puede ejecutar los comandos internos de Linux, tales como ls, cat, wc, echo, etc. Al hacer esto, también acepta parámetros extra.
Para esto, puede ingresarse:

 1. La ruta completa del programa a ejecutar. Ej: 
```

% /bin/echo -n hello world!
```
 2. El nombre del programa. Ej:
```
% echo -n hello world!
```
 3. Un path relativo en función del directorio actual. Ej: si el directorio actual es /:
```
% bin/echo -n hello world!
```
## Funciones extra:
La consola también acepta la ejecución de **procesos en segundo plano**, **redirección de entrada/salida**, y el uso de **pipes**, funcionalidades descritas a continuación.
 Cabe aclarar que solo se acepta un modificador por instrucción.
 
 
### Ejecución de procesos en segundo plano:

Para que se ejecute un proceso, y al mismo tiempo la consola acepte input por parte del usuario, se utiliza el modificador `&` al final de la instrucción. Al presionar Enter, se comenzará a ejecutar el comando anterior, pero podrá escribirse uno nuevo al mismo tiempo. 

Para que esta función se pueda ver claramente, se incluye en el repositorio una versión ejecutable del programa Ksamp, que muestra información relevante sobre el sistema. Ej:

```

% ./ksamp -l 1 30 &
% ./ksamp -l 3 30
```
Al ejecutar la primer línea, se mostrará información con un tiempo de refresco de 1 segundo. 
Luego de ingresar la segunda línea, también se mostrará cada 3 segundos, y podrá verse como se intercalan las impresiones de los dos programas.

### Redirección de entrada / salida:

Permite modificar los file descriptors de los procesos que se están ejecutando.  Así, resulta posible guardar texto en un archivo, o tomarlo como input en lugar de utilizar la consola.

Para redirigir la salida se utiliza el caracter `>` seguido del nombre del archivo a guardar. Ej:

```
% ls > files.txt
```

Este comando crea un archivo llamado `files.txt`, que contiene la salida del programa `ls`. Aquí se sobreescribe el archivo si ya existiese, y se borra el contenido anterior en el mismo. También pueden incluirse comandos del programa al redirigir la salida standard. Ej:

```
% ls -i > files.txt
```

Como alternativa puede anexarse información al final del archivo, si ya existiese (append), con el operador `>>`. Ej:

```
% ps >> files.txt
```
Esta instrucción agrega al final del archivo `files.txt` la salida del comando ps.

Para redirigir la entrada se utiliza el caracter `<` seguido del nombre del archivo de donde se quiere leer información. Ej:

```
% wc -m < files.txt
```
Este comando muestra la cantidad de caracteres en el archivo files.txt

### Uso de pipes


## 2. Instrucciones de instalación
---
 - Para instalar el programa, descargue el repositorio en su computadora.
 - Luego, mediante la terminal, ejecute los siguientes comandos para descomprimir el archivo .zip y situarse en la carpeta donde se halla el Makefile:
```
% cd Downloads
% unzip TP2-SO-2016-master.zip
% cd TP2-SO-2016-master/shell/work/code
```
 - Seguidamente, para crear la carpeta donde se almacenan los archivos .o, ejecute:
```
% mkdir obj
```
 - Para comenzar el proceso de compilación y linkeo de los archivos, ejecute el comando:
```
% make
```
 
 - Una vez terminado, para ejecutar el programa, ingrese el comando: 
```
% ./baash
```

 - Para obtener ayuda, ejecute:
```
% ./baash
% help
```
Al compilar y linkear, se genera un archivo donde se guardan los posibles errores y advertencias que encuentre el programa CppCheck al realizar el análisis estático del código. Este archivo se encuentra en:
```
shell/work/code/err.txt
```
Si desea más información, remítase a la documentación proporcionada, que se encuentra en la ruta ```/shell/doc/html/index.html```
