/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef CTHULHU_H
#define CTHULHU_H

#include "GraphLoad.h"
#include "DataStructs.h"
#include "VertexGraphData.h"
#include "Coloring.h"

#define LINE_LENGHT 80

/* STRUCTURES FOR GRAPH REPRESENTATION */

typedef struct _VerticeSt_t {
    u32 name;         /* Real name of vertex */
    u32 degree;       /* Vertex degree */
    u32 color;        /* Vertex color */
    u32 index;        /* Index of vertex in Nimhe array of vertices */
} VerticeSt;


typedef struct _NimheSt_t {
    u32 no_vertices;            /* Number of vertices */
    u32 no_edges;               /* Number of edges */
    u32 coloring;               /* Graph coloring so far */
    u32 *name_array;            /* Array of graph vertex names */
    u32 *color_array;           /* Array of colors of vertices */
    u32 *degree_array;          /* Array of degrees of vertices */
    u32 *RAR_order_array;       /* Array of values used for RAR order for each vertex */
    Vector *neighbors_array;    /* Array of lists of neighbors related to each vertex */
    u32 *order;                 /* Coloring order */
    u32 *natural_order;         /* Natural order */
    u32 *vertices_with_color;   /* Array to store number of vertices colored with each color */
    bool *used;                 /* Array to be used in Greedy function and OrdenEspecifico */
} *NimheP;


/* GRAPH CONSTRUCTION AND DESTRUCTION FUNCTIONS */

NimheP NuevoNimhe(void);
/*
 * Aloca memoria, inicializa lo que haya que inicializar de una estructura
 * NimheSt y devuelve un puntero a ésta. Además lee un grafo desde standard
 * input en el formato especificado en DIMACS y llena esa estructura NimheSt
 * con esos datos.
 *
 * En caso de error, la función devolverá un puntero a NULL. Errores posibles
 * pueden ser falla en alocar memoria, pero también que el formato de entrada
 * no sea válido, por ejemplo, que la primera linea sin comentarios no empiece
 * con p o que n* != n (esto se especifica en el formato de entrada).
 */

int DestruirNimhe(NimheP G);
/*
 * Destruye y libera memoria alocada. Retorna 1 si todo anduvo bien y 0 si no.
 */

void shuffle(u32 *array, u32 n, u32 seed);
/*
 * Arrange the N elements of ARRAY in random order. Only effective if N is much
 * smaller than RAND_MAX.
 */

#endif
