### Para compilar el proyecto:

```

gcc -Wall -Wextra -O3 -std=c99 -Iapifiles dirmain/mainEBoucher.c apifiles/*.c -o EB
```

La ejecución se puede hacer de las dos siguientes maneras:

- Carga mediante un archivo:
```
    ./EB <[/ruta/al/archivo/nombrearchivo]
```
- Carga manual:

```
    ./EB

```
e ingresando el grafo manualmente.


### Descripción de las pruebas

```
Las pruebas consisten en el monitoreo de la ejecución del programa cuando se corre con un input
dado y el control de los resultados de coloreo. Los estimadores de interés para el monitoreo de la
ejecución son el tiempo transcurrido que tardó en ejecutarse, y el tamaño máximo del conjunto residente de memoria asignada.
En cuanto al control de los resultados de coloreo, basta con ejecutar la API junto con el
mainEBoucher.c provisto. Este imprime el coloreo obtenido de 10 iteraciones iniciales conor-
den aleatorio, luego una iteración en orden Welsh-Powelly de no haberse encontrado el número cromático del grafo, corre Greedy 1001 veces con los distintos órdenes implementados y luego imprime el mejor coloreo de esas corridas. También corre el algoritmo 2-color al principio para verificar si el grafo dado es 2-coloreable, y luego de las 11 primeras corridas, verifica si es 3-coloreable antes
de correr Greedy 1001 veces.
```
### Mecanografiado de las pruebas

```
Existe una gran variedad de herramientas para probar el tiempo y memoria consumidos por el programa. Menciono unicamente dos de ellas:
```
- Comando htop

```
Utilizar htop mientras se ejecuta el programa permite visualizar tanto la RAM (columna
RES) que está siendo usada por el proceso, y el tiempo (columna TIME+).
```
- Comandotime

```
El comando time corre el programa y da un resumen de la utilización de recursos.
Se puede usar este comando como sigue:
```
```
command time -v ./EB<[/ruta/al/archivo/nombrearchivo]
```
```
command fuerza al shell a ejecutar time, ignorando cualquier función del mismo nombre.
```
```
-v: Opcional para obtener un formato detallado, mostrando cada pieza de información
disponible sobre el uso de recursos del programa con una descripción en ingles de su signifi-
cado.
```



