## Universidad Nacional de Córdoba

### FaMAF

# Matematica Discreta II

## Proyecto: Primera Parte

## Esteban L. Boucher

### eboucher7@gmail.com

### Septiembre 2016

```
Prof. Daniel Penazzi
```

##Indice general


- 1 Introduccion
   - 1.1 Motivación del proyecto
   - 1.2 Propósito y objetivos
      - 1.2.1 Coloreo Greedy
   - 1.3 Restricciones
- 2 Formato del archivo de entrada
- 3 Estructura del programa
   - 3.1 Descripción de estructuras y variables
      - 3.1.1 struct NimheStt
      - 3.1.2 struct VectorStt.
      - 3.1.3 struct QueueStt
      - 3.1.4 struct VerticeStt
   - 3.2 Estructura general
      - 3.2.1 APIfiles
         - 3.2.1.1 Types.h
         - 3.2.1.2 Cthulhu.{c, h}
         - 3.2.1.3 GraphLoad.{c, h}
         - 3.2.1.4 VertexGraphData.{c, h}
         - 3.2.1.5 DataStructs.{c, h}.
         - 3.2.1.6 SortFuncs.{c, h}
         - 3.2.1.7 ColorFuncs.{c, h}
      - 3.2.2 Dirmain
         - 3.2.2.1 mainEBoucher.c
   - 3.3 Descripcion de algoritmos
      - 3.3.1 Algoritmo 2-color
      - 3.3.2 Algoritmo Greedy de coloreo de vértices
- 4 Instrucciones de operación
   - 4.1 Mecanografiado de compilación
   - 4.2 Descripción de las pruebas
   - 4.3 Mecanografiado de las pruebas
- 5 Desafios y elecciones de diseño
   - 5.1 Problema: vértices pueden ser cualquier u32
   - 5.2 Vecinos de un vertice
   - 5.3 Orden de los vértices
   - 5.4 Funciones de ordenación
      - 5.4.1 Revierte()
      - 5.4.2 GrandeChico() y ChicoGrande()
   - 5.5 Arreglo de usados
   - 5.6 Identificadores de vertices
   - 5.7 Elección de funcionhash
- 6 Posibles mejoras
- 7 Referencias


## 1 Introduccion

### 1.1 Motivación del proyecto

El problema de coloreo de grafos consiste en asignar colores a ciertos elementos de un grafo
sujetos a ciertas restricciones.
El problema de coloreo de vértices es el problema más común de coloreo de grafos. El problema
es, dados m colores, encontrar una forma de colorear los vértices de un grafo de tal manera que no
hallan dos vértices adyacentes utilizando el mismo color.
El interés acerca de este problema se debe a su gran número de aplicaciones. Entre las más
conocidas de coloreo de grafos se destacan:^1

- Establecer horarios y cronogramas
    Supongamos que queremos hacer un cronograma de exámenes para un universidad. Listamos
    diferentes asignaturas y estudiantes matriculados en cada asignatura. Muchas asignaturas
    tendrán estudiantes en común. ¿Como se puede organizar el cronograma de modo que no
    hallan dos exámenes con un estudiante en común programados al mismo tiempo? ¿Cuantas
    ranuras de tiempo mínimo son necesarias para programar todos los exámenes? Este problema
    se puede representar como un grafo en el que cada vértice es una asignatura y una arista entre
    dos vértices significa que hay un estudiante común. Este es un problema de coloreo de grafos,
    donde el número mínimo de intervalos de tiempo es igual al número cromático del grafo.
- Asignación de frecuencias de radio móvil
    Cuando se asignan frecuencias a las torres, las frecuencias asignadas a todas las torres que
    se encuentran en el mismo lugar debe ser diferentes. ¿Cómo asignar frecuencias con esta
    restricción? ¿Cual es el mínimo número de frecuencias necesarias? Este problema es también
    un ejemplo del problema de coloreo de grafos donde cada torre representa un vértice y una
    arista entre dos torres representa que están en el rango de la otra.
- Sudoku
    El sudoku es también una variación del problema de coloreo de grafos en el cual cada celda
    representa un vértice. Hay una arista entre dos vértices si están en la misma fila o la misma
    columna o el mismo bloque.
- Asignación de registros
    En optimización de compiladores, la asignación de registros es el proceso de asignar un gran
    número de variables del programa de destino a un número reducido de registros de la CPU.
    Este problema también un problema de coloreo de grafos.
- Grafos bipartitos
    Podemos comprobar si un grafo es bipartito o no coloreando el grafo utilizando dos colores.
    Si un grafo dado es 2-coloreable, entonces es bipartito, de lo contrario no lo es.
- Mapa de coloreo
    Mapas gráficos de países o provincias donde dos ciudades adyacentes no pueden ser asignadas
    con el mismo color. Cuatro colores son suficientes para colorear cualquier mapa.^2

```
El siguiente programa consiste en la resolución de ese problema.
```

### 1.2 Propósito y objetivos

Actualmente no se conoce un algoritmo de tiempo polinomial que resuelva el problema de
coloreo de grafos. Sin embargo, hay una cierta calidad mínima que se puede obtener. Supongamos
que d es el mayor grado de cualquier vértice en nuestro grafo. A medida que avanzamos en el
coloreo, cuando coloreamos cualquier vértice particular v, este está unido a lo sumo con otros d
vértices, de los cuales algunos pueden ya estar coloreados. Luego, hay a lo sumo d colores que hay
que evitar usar. Usamos el color de menor número no prohibido. Esto significa que usamos colores
numerados d+1 o menor, dado que al menos uno de los colores 1, 2, ...,d+1 NO está prohibido.
De esta manera, nunca necesitamos usar ningún color de mayor número qued+1. Esto nos da el
siguiente teorema:

#### 1.2.1 Coloreo Greedy

Teorema 1 (Coloreo Greedy).Si d es el mayor de los grados de los vértices en un grafo G,
entonces G tiene una coloración propia con d + 1 colores o menos, es decir, el número cromático
de G es como maximo d + 1.

```
Esto nos da una cota superior del numero cromatico del grafo.^4
```
El objetivo de este proyecto consiste en cargar un grafo y dar un coloreo propio de sus vértices,
corriendo repetidamente Greedy usando órdenes que cumplan con el Teorema 1.

### 1.3 Restricciones

- Tiempo
    El presente programa está estipulado para ser razonablemente rápido. En particular, con
    todos los grafos de ejemplo probados por la catedra^5 ,^6 se espera que termine en menos de
    una hora. Algunos de esos grafos pueden llegar a tener cerca de 2 millones de vértices y 10
    millones de aristas.
- Memoria
    El programa nunca debe usar más de 256 MB de memoria RAM.

## 2 Formato del archivo de entrada

El formato de entrada es una variación de DIMACS, un formato estándar para representar
grafos. La descripción oficial de DIMACS es como sigue:

1. Ninguna línea tiene más de 80 caracteres.
2. Al principio hay cero o más líneas que empiezan con ’c’ (sin las comillas), las cuales son
líneas de comentario y son ignoradas.
3. Luego hay una línea de la forma:
p edge n m
donde n y m son dos enteros. n representa el número de vértices y m el número de lados.
4. Luego siguen m líneas todas comenzando con ’e’ (sin las comillas) y dos enteros, representando
un lado. Luego de esas m líneas se detiene la carga.


## 3 Estructura del programa

En la Figura 1 se muestra un diagrama de la estructuración del programa en los distintos
archivos.

```
GraphLoad ColorFuncs DataStructs SortFuncs VertexGraphData
```
```
Cthulhu
```
```
Usuario
```
```
mainEBoucher.c
```
```
GraphLoad.h ColorFuncs.h DataStructs.h
SortFuncs.h VertexGraphData.h
```
```
GraphLoad.c
```
```
Cthulhu.h
```
```
ColorFuncs.c DataStructs.c
SortFuncs.c VertexGraphData.c
```
```
Cthulhu.c
```
```
Types.h
```
```
Figura 1: Diagrama de archivos del programa
```
### 3.1 Descripción de estructuras y variables

#### 3.1.1 struct NimheStt

Las estructura principal de este programa es struct NimheStt, la cual contiene toda la información del grafo necesaria para correr el algoritmo de Greedy y obtener del mismo para modificar
el orden de los vértices acorde a las distintas funciones de ordenación.


- Información básica del grafo

```
NimheSt contiene la cantidad de vértices y lados del grafo cargado y la cantidad de colores
que está usando en el momento para colorear los vértices que contiene.
```
- Información de los vértices del grafo

```
En esta implementación la información que define a los vértices está dispersa en distintos
arreglos dentro de la estructura del grafo: un name array que contiene los nombres ”reales” de
los vértices, los cuales en esta implementación son enteros sin signo de 32 bits; un color array que guarda el coloreo actual de los vértices, un degree array para los grados de los vértices, un RAR order array para guardar el orden en el cual los vértices deben colorearse si se usa ReordenAleatorioRestringido. Los últimos datos acerca de los vértices son las listas de vecinos, estas están en neighborsArray, un arreglo de vectores en los cuales se guardan los
́indices de los vecinos de un vertice
```
- Información de órdenes de los vértices

```
Se utiliza principalmente un arreglo order, que se utiliza para dar el coloreo cuando se corre
Greedy sobre el grafo. Los arreglos naturalOrder y verticesWithColor se utilizan para
guardar el orden natural y la cantidad de colores coloreados con el color con el que está
coloreado el vértice en la i-ésima posición del arreglo, respectivamente. Se asignan los valores de los últimos dos arreglos al arreglo order cuando se llama a la función de ordenación correspondiente. Más sobre las funciones de ordenación adelante.
```
- Información de control

```
Se utiliza un arreglo de booleanos used para verificar si algún ítem está siendo usado. Utilizo el término impreciso item porque la semántica de este arreglo cambia en las distintas funciones que lo utilizan. Más acerca de esto en la sección 5.
Una característica que se mencionó sin ser explicada es la de guardar los índices de los vértices en la lista de vecinos deNimheSt. Esto es una elección de diseño de esta implementación, el la cual los vértices o sus nombres ”reales” solo sean de importancia durante la carga del grafo y en la ordenación por orden natural. Luego todas las operaciones se realizan en torno a los arreglos de órdenes o de la información de los vértices sin sus nombres. De esta manera los vértices son referidos luego de la carga directamente a través de sus índices o identificadores.
Más acerca de esta elección en la sección 5.
```
#### 3.1.2 struct VectorStt.

Estructura de datos para representar un arreglo dinámico.^7 Se utiliza en la estructura del grafo para guardar los identificadores de los vecinos de un vértice.

#### 3.1.3 struct QueueStt

Estructura de datos que implementa una cola circular,^8 dentro de sus miembros tiene un arreglo de elements y dos enteros sin signo indicando los índices al primero y el último elemento de la cola.


#### 3.1.4 struct VerticeStt

Estructura de datos no utilizada en la implementación del proyecto. Implementada para el testeo
a través de las funciones de verificación destruct VertexGraphData.{c,h}con modificaciones en
la función main().

### 3.2 Estructura general

Debido al tamaño del proyecto, esta implementación se presenta en forma de distintos módulos,
cada uno agrupando funcionalidades con el objetivo de mantener cierta independencia y facilitar la
legibilidad. Notar sin embargo que los tipos abstractos de datos implementados no son respetados
como tales dentro de las funciones de los distintos archivos, dado que todos pertenecen a la misma
API y por conveniencia se accede a los tipos abstractos de datos como si fuesen cualquier estructura
y no necesariamente a traves de la interfaz que provean.

#### 3.2.1 APIfiles

##### 3.2.1.1 Types.h

Este módulo hace las llamadas a las librerías generales necesarias en el programa, define las es-
tructuras de datos descritas en la sección 3.1. Contiene el tipo de datosu32usando el tipouint32t
definido en la librería estandarstdint.h. El motivo de esta definición es garantizar que u32 sea un
entero de 32 bits sin signo, independientemente del compilador en el que se compila el programa.
También define los macros LINELENGHT para usar durante la carga del grafo desde un archivo, y
los macrosVECTORINITIALCAPACITYyVECTORGROWTHRATEpara manejar los incrementos en el
tamaño de las estructuras Vector.

##### 3.2.1.2 Cthulhu.{c, h}

El moduloCthulhucontiene los llamados a todos los demas modulos del programa, de manera
que puedan ser usados desdemainEEboucher.cincluyendounicamente aCthulhu.h.
Cthulhudefine las funciones de construccion y destruccion del grafoNuevoNimhe():

- NuevoNimhe()
    Prototipo de funcion:
    NimheP NuevoNimhe();
    La funcion aloca memoria, inicializa las variables deNimheSty devuelve un puntero aesta.
    Lee un grafo desde standard input en el formato especificado en la seccion 2 y llena la estruc-
    tura con esos datos.
    Ademas de cargar el grafo, asigna el “color” 0 a cada vertice para indicar que estan todos no
    coloreados.
    En caso de error, la funcion devuelve un puntero aNULL. (errores posibles pueden ser falla en
    alocar memoria, o que el formato de entrada no sea valido, por ejemplo, que la primera linea
    sin comentarios no empiece con p o que n* 6 = n (ver en la seccion 2 que significa esto)
- DestruirNimhe()
    Prototipo de la funcion:
    int DestruirNimhe(NimheP G);
    Destruye G y libera la memoria alocada. Retorna 1 si todo anduvo bien y 0 si no.


##### 3.2.1.3 GraphLoad.{c, h}

Este modulo contiene las funciones auxiliares que se utilizan para la carga de vertices y aristas
en el grafo. Las funciones son las siguientes:

- insertedge()
    Prototipo de la funcion:
    void insertedge(NimheP G, u32 fstvertex, u32 sndvertex, bool *vloaded);
    Inserta una arista en el grafo copiando los dos vertices que la forman. Para hacer esto busca los
́indices oidentificadoresdefstvertexysndvertexllamando a la funcionfindvertexhash()
y luego agrega el identificador de cada uno en la lista del otro.
- findvertexhash()
    Prototipo de la funcion:
    u32 findvertexhash(NimheP G, u32 vertex, bool *vloaded);
    Calcula elcodigo hashdevertexy ubica avertexen el grafoGusando el codigo hash. Hace
    un sondeo lineal olinear probingpara chequear el siguiente elemento en el grafo sivertexno
    fue encontrado en elhashcodeen caso quevertexno se encuentre enG, la funcion le asigna
    la primera celda disponible que encuentra.
- hashcode()
    Prototipo de la funcion:
    u32 hashcode(u32 key, u32 size);
    La funcion define un metodo de hasheo ohashing methodpara computar el codigo hash de
    keyen el rango de 0 asize- 1. Para esto se utiliza el metodo de avalancha definido en la
    funcion de hashMurmurHash. Mas sobre la eleccion de esta funcion de hash en la seccion 5.

##### 3.2.1.4 VertexGraphData.{c, h}

```
Funciones para extraer informacion de datos de un vertice:
```
- ColorDelVertice()
    Prototipo de la funcion:
    u32 ColorDelVertice(VerticeSt x);
    Devuelve el color con el que esta coloreado el verticex. Si el vertice no esta coloreado,
    devuelve 0.
- GradoDelVertice()
    Prototipo de la funcion:
    u32 GradoDelVertice(VerticeSt x);
    Devuelve el grado del verticex.
- NombreDelVertice()
    Prototipo de la funcion:
    u32 NombreDelVertice(VerticeSt x);
    Devuelve el nombre real del verticex.


- ImprimirVecinosDelVertice()

```
Prototipo de la funcion:
void ImprimirVecinosDelVertice(VerticeSt x,NimheP G);
Imprime en standard output una lista de los vecinos del verticex.
```
```
Funciones para extraer informacion de datos del grafo:
```
- NumeroDeVertices()

```
Prototipo de funcion:
u32 NumeroDeVertices(NimheP G);
Devuelve el numero de vertices del grafo G.
```
- NumeroDeLados()

```
Prototipo de funcion:
u32 NumeroDeLados(NimheP G);
Devuelve el numero de lados del grafo G.
```
- NumeroDeVerticesDeColor()

```
Prototipo de funcion:
u32 NumeroVerticesDeColor(NimheP G,u32 i);
Retorna el numero de vertices de color i. (si i = 0 devuelve el numero de vertices no colorea-
dos).
```
- ImprimirVerticesDeColor()

```
Prototipo de funcion:
u32 ImprimirVerticesDeColor(NimheP G,u32 i);
Imprime una lista de los vertices que tienen el colori. Si i = 0, esta representa la lista de
vertices no coloreados.
Si no hay vertices de color i imprime “No hay vertices de color i”
Retorna el numero de vertices de color i.
```
- CantidadDeColores()

```
Prototipo de funcion:
u32 CantidadDeColores(NimheP G);
Devuelve la cantidad de colores usados en el coloreo de G.
```
- IesimoVerticeEnElOrden()

```
Prototipo de la funcion:
VerticeSt IesimoVerticeEnElOrden(NimheP G,u32 i);
Devuelve el vertice numero i en el orden guardado en ese momento en G. (elindice 0 indica
el primer vertice, elindice 1 el segundo, etc)
```

- IesimoVecino()
    Prototipo de la funcion:
    VerticeSt IesimoVecino(NimheP G,VerticeSt x,u32 i);
    Devuelve el vecino numero i dexen el orden en que este guardado en G, (elindice 0 indica
    el primer vertice, elindice 1 el segundo, etc).

##### 3.2.1.5 DataStructs.{c, h}.

```
Funciones deVectorSt:
```
- vectorinit()
    Prototipo de la funcion:
    void vectorinit(Vector *V);
    Inicializa una estructuraVector. Establece su tamaño en 0, su capacidad enVECTORINITIAL
       CAPACITYy reserva memoria para un arreglo de datos de tamaño igual aVECTORINITIAL
       CAPACITY.
- vectorappend()
    Prototipo de la funcion:
    void vectorappend(Vector *V, u32 value);
    Agregavalue al vector V. Si el arreglo de datos esta lleno, un llamado a esta funcion
    causara quevector->datase expanda para agregar este valor. En cualquier caso, incre-
    mentavector->size.
- vectorfree()
    Prototipo de la funcion:
    void vectorfree(Vector *V);
    Libera la memoria alocada para el arreglo de datos. Observacion: esta funcion no libera la
    estructuraVector, esto se deja para elnodo cliente, que en este caso es el modulo Cthulhu,
    en la funcion deDestruirNimhe().

```
Funciones deQueueSt:
```
- Queueinit()
    Prototipo de la funcion:
    Queue* Queueinit(u32 maxelems);
    Toma como argumento el maximo numero de elementos que la cola puede contener. Crea
    unaQueuedel tamaño recibido en la entrada y retorna un puntero a la misma.
- Dequeue()
    Prototipo de la funcion:
    void Dequeue(Queue *Q);
    Saca el primer elemento de la cola.


- Queuefront()
    Prototipo de la funcion:
    u32 Queuefront(Queue *Q);
    Retorna el primer elemento de la cola.
- Enqueue()
    Prototipo de la funcion:
    void Enqueue(Queue *Q, u32 element);
    Inserta un elemento al final de la cola.
- Queueisempty()
    Prototipo de la funcion:
    bool Queueisempty(Queue *Q);
    Retornatruesi la cola esta vacia yfalsesi hay elementos en ella.
- Queuefree()
    Prototipo de la funcion:
    void Queuefree(Queue *Q);
    Libera la memoria alocada para el arreglo de los elementos.

##### 3.2.1.6 SortFuncs.{c, h}

- shuffle()
    Prototipo de la funcion:
    void shuffle(u32 *array, u32 n, u32 seed);
    Mezcla los elementos dearrayusando la semillaseedpara generar un orden aleatorio.
- OrdenNatural()
    Prototipo de la funcion:
    void OrdenNatural(NimheP G);
    Ordena los vertices del grafo en orden creciente de sus nombres ”reales”.
- OrdenWelshPowell()
    Prototipo de la funcion:
    void OrdenWelshPowell(NimheP G);
    Ordena los vertices de G de acuerdo con el orden Welsh-Powell, es decir, con los grados en
    orden no creciente.
- ReordenAleatorioRestringido()
    Prototipo de la funcion:
    void ReordenAleatorioRestringido(NimheP G);
    Si G esta coloreado con r colores yW 1 son los vertices coloreados con 1,W 2 los coloreados
    con 2, etc, entonces esta funcion ordena los vertices poniendo primero los vertices deWj 1 (en
    algun orden) luego los deWj 2 (en algun orden), etc, donde j1, j2, ... son aleatorios (pero
    distintos).


- GrandeChico()
    Prototipo de la funcion:
    void GrandeChico(NimheP G);
    Si G esta coloreado con r colores yW 1 son los vertices coloreados con 1,W 2 los coloreados
    con 2, etc, entonces esta funcion ordena los vertices poniendo primero los vertices deWj 1
    (en algun orden)luego los de Wj 2 (en algun orden), etc, donde j1, j2, ... son tales que
    |Wj 1 |≥|Wj 2 |≥...≥|Wjr|.
- ChicoGrande()
    Prototipo de la funcion:
    void ChicoGrande(NimheP G);
    Idem que el anterior excepto que ahora el orden es tal que|Wj 1 |≤|Wj 2 |≤...≤|Wjr|
- Revierte()
    Prototipo de la funcion:
    void Revierte(NimheP G);
    Si el grafo esta coloreado con r colores yW 1 son los vertices coloreados con 1,W 2 los coloreados
    con 2, etc, entonces esta funcion ordena los vertices poniendo primero los vertices deWr(en
    algun orden) luego los deWr− 1 (en algun orden), etc.
- OrdenEspecifico()
    Prototipo de la funcion:
    void OrdenEspecifico(NimheP G, u32* x);
    Si x cumple la condicion, entonces la funcion ordena los vertices con OrdenNatural(), luego
    lee el orden dado en el string x y los ordena de acuerdo a lo que lee. Es decir, si luego de
    OrdenNatural, los vertices quedaron ordenados como, por ejemplo, V[0],V[1],...,V[n-1], luego
    de OrdenEspecifico el orden debe ser V[x[0]],V[x[1]],...,V[x[n-1]].

##### 3.2.1.7 ColorFuncs.{c, h}

- Chidos()
    Prototipo de funcion:
    int Chidos(NimheP G);
    Devuelve 1 si G es bipartito, 0 si no.
- Greedy()
    Prototipo de funcion:
    u32 Greedy(NimheP G);
    Corre greedy en G con el orden interno indicado en la estructuraNimheStde G. Devuelve el
    numero de colores que se obtiene.


#### 3.2.2 Dirmain

##### 3.2.2.1 mainEBoucher.c

Este modulo contiene a la funcion principal para probar el programa,main(). Tiene solamente
las llamadas astdio.h,stdlib.hyCthulhu.h.
Define auxiliarmente el prototipo de la funciontime()para generar numeros aleatorios, y una
funcion de comparacion de dos valores que se usa dentro de la funcionmain(). Ademas define una
funcionshufflef(), la misma que shuffle() en SortFuncs. Se define nuevamente en este modulo
para mantener la independencia del programamain()con respecto a los APIfiles.
Se usa esta interfaz para cargar leer un grafo desdestandard input, donde la entrada es como
se describe en la seccion 2.

```
Funcion main():
```
```
Prueba el programa de la siguiente manera:
```
1. Carga el grafo. Si el formato de entrada esta mal imprime una linea que dice “Error en
formato de entrada” y para. (por ejemplo, si hay una linea que empieza con “d”, o si la primera
linea que no empieza con “c” no empieza con “p”, o si el numero de vertices que se extrae de los
lados no es n, etc).
2. Siχ(G) = 2 imprime en standard output “Grafo Bipartito” y para.
3. Siχ(G)>2 imprime en una linea “Grafo No Bipartito” y luego crea 10 ordenes aleatorios mas
Welsh-Powell y corre Greedy con cada uno de esos ordenes imprimiendo cuantos colores obtiene en
cada caso.
En el caso de las corridas aleatorias cada linea sera de la forma “coloreo aleatorio numero k: r
colores” donde r sera el numero de colores que obtuvieron y k el numero de corrida aleatoria.
En el caso del orden WelshPowell la linea sera “coloreo con Greedy en WelshPowell:r colores”
Ademas, antes de esa linea habra una linea en blanco separando de las lineas anteriores de las
corridas aleatorias.
4. Si llego a este paso es porque el grafo no es bipartito, por lo tanto si alguno de esos coloreos
es con tres colores, ya se sabe queχ(G) = 3 asi que imprime una linea que diciendo “χ(G) = 3” y
para.
5. Si no se obtuvieron 3 colores con ninguno de los coloreos, se imprime una linea en blanco,
luego una linea que dice:

```
====Comenzando Greedy Iterado 1001 veces====
```
y luego otra linea en blanco.
Luego toma el mejor coloreo de los primeros 11 anteriores y corre Greedy 1000 veces cambiando
el orden de los colores, siguiendo el siguiente patron:

- 50% ChicoGrande
- 12,5% GrandeChico
- 31,25% Revierte
- 6,25% ReordenAleatorioRestringido

```
(nota: esos porcentajes son 8/16, 2/16, 5/16 y 1/16 respectivamente).
Luego de estas 1000 iteraciones, hace una iteracion final con Revierte, e imprime:
Mejor coloreo con Greedy iterado 1001 veces: k colores (a CG,b GC, c R, d RAR)
```

donde k es el menor numero de colores que hayan obtenido en las 1001 iteraciones, y a,b,c,d
son la cantidad de veces que corrieron Chico Grande,GrandeChico, Revierte y ReordenAleatori-
oRestringido, respectivamente.

### 3.3 Descripcion de algoritmos

#### 3.3.1 Algoritmo 2-color

Un grafo G=(N, E) esbipartitosi sus vertices se pueden separar en dos conjuntos disjuntos
U y V, es decir, tal que se cumple:

- U∪V = N
- U∩V =∅

de manera que las aristas solo pueden conectar vertices de un conjunto con vertices del otro, es
decir:

- ∀u 1 ,u 2 ∈U,∀v 1 ,v 2 ∈V∀u 1 ,u 2 ∈U,∀v 1 ,v 2 ∈V no existe ninguna arista e=(u 1 ,u 2 ) e=(u 1 ,u 2 )
    ni e=(v 1 ,v 2 ) e=(v 1 ,v 2 )

Un grafo bipartito es posible si el coloreo del grafo se puede hacer usando dos colores de tal
manera que vertices de un conjunto esten coloreados con el mismo color.

El algoritmo utilizado presenta una minima variacion al algoritmo dado en clase: dentro del
ciclo para recorrer los vecinos de un vertice se termina la funcion si se encuentra que uno de sus
vecinos ya estaba coloreado con el mismo color. Esto evita la tarea de tener que revisar todos los
lados del grafo y verificar si dos vecinos tienen el mismo color:


Algoritmo 12-color

```
Descolorear todos los vertices si tienen algun color.
j← 0
whilej<ndo
elegir x∈V no coloreado
coloreo C(x)← 1
j←j+ 1
crear cola Q con x como suunico elemento
whileQ 6 =∅do
p←1er elemento de Q
remuevo p de Q
forw∈Γ(p)do
ifw no esta coloreadothen
incluir w en Q
colorear C(w)←3 - C(p)
j←j + 1
end
ifw tiene el mismo color que pthen
return”no es 2-coloreable”
end
end
end
end
return”si es 2-coloreable”
```
#### 3.3.2 Algoritmo Greedy de coloreo de vertices

```
(Se utiliza la notacion vista en clase)
```
“Si el orden de los vertices es v 1 , v 2 , ... , vn:
C(v 1 ) = 1
Para k = 2, 3, ... , N:
C(vk) =min{j∈ {1, 2, ... , N}: C(vi) 6 =j ∀i≤k - 1 tal que vivk∈E}”

Esta implementacion del algoritmo utiliza los arreglos de la estructura deNimheSt usedpara
guardar los colores”prohibidos” en cada iteracion, colorarraydonde guarda el color de los
vertices.
Comienza estableciendo los valores de esos arreglos en 0, (falsepara el arreglo de colores usados).
Luego el algoritmo es el siguiente:


Algoritmo 2Greedy
Reestablecer valores de used enfalse
Reestablecer valores de colorarray en 0
Colorear C(x1ro en el orden)← 1
coloreo←coloreo + 1
Definir neighborcolor, i, j
forx∈G -{x1ro en orden}do
fory∈ListaDeVecinos(x)do
ify no esta coloreadothen
used[iy]←true
end
end
fori∈CantVertices(G)do
ifused[i] falsethen
Salir
end
end
Colorear C(y)←i
Asignar coloreo←max(coloreo, i)
end
fory∈ListaDeVecinos(x)do
if y no esta coloreadothen
used[iy]←false
end
end
returncoloreo

Ademas, en la implementacion se utiliza el arregloverticeswithcolorpara guardar en la
i-esima posicion, i≤coloreo, la cantidad de vertices coloreados con el color i. No es utilizado para
ejecutar el algoritmo, solo se actualiza cada vez que se asigna un nuevo color a un vertice. Su
utilidad esta en las funciones de ordenacion. Mas sobre esto en la seccion 5.4.2.

## 4 Instrucciones de operacion

### 4.1 Mecanografiado de compilacion

```
Para compilar el proyecto:
gcc -Wall -Wextra -O3 -std=c99 -Iapifiles dirmain/mainEBoucher.c apifiles/*.c
-o EB
La ejecucion se puede hacer de las dos siguientes maneras:
```
- Carga mediante un archivo:
    ./EB <[/ruta/al/archivo/nombrearchivo]
- Carga manual:
    ./EB
e ingresando el grafo manualmente.


### 4.2 Descripcion de las pruebas

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
### 4.3 Mecanografiado de las pruebas

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
## 5 Desafios y elecciones de diseño

### 5.1 Problema: vertices pueden ser cualquier u32

Esta caracteristica impone la restriccion de no poder usar el nombre real de un vertice como
́indice en el arreglo. Para solucionar este problema, el programa implementa un arreglo como una
hash table. La hash table utiliza una funcion hash para insertar elementos en el arreglo y resuelve
las colisiones usando sondeo lineal, como se describe en la seccion 3.2.1.3.


### 5.2 Vecinos de un vertice

La implementacion de los vecinos de un vertice tambien fue un desafio dado que durante la
carga del grafo, la cantidad de vecinos que tiene un vertice es desconocida. Se trata este problema
usando la estructuraVectorStcon un arreglo dinamico, alocando mas memoria a medida que se
llena el arreglo.

### 5.3 Orden de los vertices

El problema de implementar el orden de los vertices se debe a la inconveniencia de reordenar
los vertices en cada iteracion, por lo que resulto necesario considerar otra forma de hacerlo. Para
resolver el problema del orden de los vertices, consideramos en primer lugar el estado de los vertices
dentro de la estructura del arreglo: cada vertice esta asociado a un soloindice, suidentificador. Se
hace uso de este dato y se implementa el orden de los vertices por medio de otro arreglo en el que
lai-esima posicion tiene el identificador deli-esimo vertice en ese orden.

### 5.4 Funciones de ordenacion

Todas las funciones de ordenacion menos OrdenEspecifico fueron implementadas utilizando la
funcion estandarqsort()y definiendo funciones de comparacion locales para pasar a qsort() como
parametro, de manera que en lo que difieren las funciones entre ellas es en la funcion de comparacion
definida para pasar a qsort().

#### 5.4.1 Revierte()

La funcionRevierte()utiliza para su funcion de comparacion el arreglocolorarraypara
comparar el numero de color. De modo que si el numero de color de un vertice es mayor que el de
otro vertice, este se ordena primero que el vertice con el que se compara.
Se pasa esta funcion de comparacion a la funcion qsort() para que ordene el arregloorderde
la manera indicada.

#### 5.4.2 GrandeChico() y ChicoGrande()

Estas funciones resultan un poco mas complejas, dado que para definir sus funciones de com-
paracion es necesario obtener la informacion para comparar desde un nivel mas que en las demas
funciones. Es decir, el primer nivel es obtener el color del vertice, y el segundo nivel obtener la
cantidad de vertices coloreados con ese color.
En ambos casos, para solucionar el problema se agrego en la estructuraNimheStun arreglo en el
que se guarde la cantidad de vertices coloreados con cada color,verticeswithcolor. Este arreglo
se actualiza a medida que se colorean los vertices en la funcion Greedy(), evitando asi aumentar
la complejidad en tiempo que representaria, por ejemplo, recorrer el grafo entero cada vez que se
comparan dos vertices para determinar cual se ordena primera.
Tener una implementacion razonablemente eficiente de ellas resulta fundamental dado que son
ejecutadas repetidas veces en la prueba del programa. Las dos funciones se implementan de manera
similar, solo difieren en que vertice se ordena primero en la funcion de comparacion.

### 5.5 Arreglo de usados

Utilizar variables cuya semantica cambia en distintos contextos es sin dudas una practica que
por motivos razonables no se promueve.


Sin embargo para el proposito de este proyecto es de utilidad, dado que si no se contara con
esta variable compartida:

1. Las tres funciones que con esta implementacion utilizan el arreglo compartido, deberian crear
el arreglo por separado y alocar memoria para la cantidad de elementos necesarios, lo cual lentifica
el programa ya que dichas funciones se ejecutan repetidas veces y en ocasiones requiriendo arreglos
muy grandes.
2. Aumenta el tamaño maximo de memoria RAM residente ocupado por el programa en eje-
cucion, dado que la memoria de los otros arreglos no se estaria liberando. Si asi fuera, el codigo
seria mas complicado, y no resolveria el problema 1.
Esto se puede evitar con la variable compartida, dado que en los tres casos, el arreglo requerido
es del mismo tamaño - igual a la cantidad de vertices del grafo - y el tipo de datos del arreglo en los
tres casos es el mismo, de tipo booleano, mas adelante se explicaran sus utilizaciones por separado.

### 5.6 Identificadores de vertices

La eleccion de guardar losindices de los vertices en la lista de vecinos deNimheSten lugar de
punteros a estructuras se debe al uso mas eficiente de la memoria que se obtiene al no utilizarlos.
Ademas se puede observar una mejora en la velocidad del programa.

### 5.7 Eleccion de funcionhash

Al momento de elegir una funcion de hash para la carga de vertices en el grafo, tuve en consid-
eracion distintas funciones hash, las cuales diferian en aspectos como rendimiento y simplicidad.
La funcion de hashMurmurHash es una buena funcion de hash para propositos generales, y
provee tanto simplicidad como una gran resistencia a colisiones, por lo cual fue una buena eleccion
para este programa.^9

## 6 Posibles mejoras

Si bien los resultados del tiempo en ejecucion de este programa en computadoras con un buen
procesador cumplen con la cota de una hora impuesta como maximo, este todavia sigue sin ser
extremadamente rapido.
Una optimizacion que se realizo fue la de quitar las estructuras de verticesVerticeStde
NimheSty esparcir la informacion que los define en distintos arreglos, de manera que sea mas directo
operar sobre cada caracteristica de los vertices y tambien deshacerse de una enorme cantidad de
punteros.
Si bien se pudo observar una gran mejora en la utilizacion de memoria RAM, la optimizacion
no se reflejo en el tiempo de ejecucion.
Para intentar mejorar esteultimo punto, se realizo unaultima modificacion mayor, que consistio
en reemplazar la utilizacion de la funcion qsort() por una implementacion deradix sortadaptada
al proposito. Estaultima modificacion estuvo lejos de producir los resultados deseados pese al
entusiasmo. En una busquedaal vuelode alguna funcion de ordenacion mas eficiente que qsort()
me encontre con radix sort, que parecia podria funcionar y los calculos parecian indicar que por
los 10 digitos que se utilizan para representar a los vertices y su informacion, radix sort andaria
significativamente mas rapido.
Esto no fue asi, lo que me lleva a considerar que hice mal los calculos o que no implemente bien
la funcion de radix sort. Ninguno de estos supuestos pude comprobar, y llegue al limite del plazo
para la entrega del proyecto, por lo que averiguarlo queda pendiente.


## 7 Referencias

(^1) [http://www.geeksforgeeks.org/graph-coloring-applications/](http://www.geeksforgeeks.org/graph-coloring-applications/)
(^2) https://en.wikipedia.org/wiki/Fourcolortheorem
(^3) https://proofwiki.org/wiki/Definition:ProperColoring
(^4) [http://web.math.princeton.edu/mathalive/5/Notes2.pdf](http://web.math.princeton.edu/mathalive/5/Notes2.pdf)
(^5) [http://www.famaf.unc.edu.ar/](http://www.famaf.unc.edu.ar/) penazzi/DisII2016/GrafosDeEjemplos.html
(^6) [http://www.famaf.unc.edu.ar/](http://www.famaf.unc.edu.ar/) penazzi/DisII2016/Corrdeotrapagina/GrafosOtros.html
(^7) https://gist.github.com/EmilHernvall/953968
(^8) [http://www.thelearningpoint.net/computer-science/data-structures-queues–with-c-program-](http://www.thelearningpoint.net/computer-science/data-structures-queues–with-c-program-)
source-code
(^9) [http://stackoverflow.com/questions/11899616/murmurhash-what-is-it](http://stackoverflow.com/questions/11899616/murmurhash-what-is-it)
