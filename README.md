### Para compilar el proyecto:

```
gcc -Wall -Wextra -O3 -std=c99 -Iapifiles dirmain/mainEBoucher.c apifiles/*.c
-o EB
La ejecucion se puede hacer de las dos siguientes maneras:
```
- Carga mediante un archivo:
    ./EB <[/ruta/al/archivo/nombrearchivo]
- Carga manual:
    ./EB
e ingresando el grafo manualmente.


### Descripción de las pruebas

```
Las pruebas consisten en el monitoreo de la ejecucion del programa cuando se corre con un input
dado y el control de los resultados de coloreo. Los estimadores de interes para el monitoreo de la
ejecucion son el tiempo transcurrido que tardo en ejecutarse, y el tamaño maximo del conjunto
residente de memoria asignada.
En cuanto al control de los resultados de coloreo, basta con ejecutar la API junto con el
mainEBoucher.cprovisto. Este imprime el coloreo obtenido de 10 iteraciones iniciales conor-
den aleatorio, luego una iteracion enorden Welsh-Powelly de no haberse encontrado el numero
cromatico del grafo, correGreedy1001 veces con los distintos ordenes implementados y luego im-
prime el mejor coloreo de esas corridas. Tambien corre el algoritmo2-coloral principio para verificar
si el grafo dado es 2-coloreable, y luego de las 11 primeras corridas, verifica si es 3-coloreable antes
de correrGreedy1001 veces.
```
### Mecanografiado de las pruebas

```
Existe una gran variedad de herramientas para probar el tiempo y memoria consumidos por el
programa. Mencionounicamente dos de ellas:
```
- Comandohtop

```
Utilizarhtop mientras se ejecuta el programa permite visualizar tanto la RAM (columna
RES) que esta siendo usada por el proceso, y el tiempo (columnaTIME+).
```
- Comandotime

```
El comandotimecorre el programa y da un resumen de la utilizacion de recursos.
Se puede usar este comando como sigue:
```
```
command time -v ./EB<[/ruta/al/archivo/nombrearchivo]
```
```
commandfuerza al shell a ejecutartime, ignorando cualquier funcion del mismo nombre.
```
```
-v: Opcional para obtener un formato detallado, mostrando cada pieza de informacion
disponible sobre el uso de recursos del programa con una descripcion en ingles de su signifi-
cado.
```
