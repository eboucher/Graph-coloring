/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef VERTEXGRAPHDATA_H
#define VERTEXGRAPHDATA_H

#include "Types.h"

typedef struct _NimheSt_t *NimheP;       /* Forward declaration of *NimheP */

/* VERTEX FUNCTIONS */

u32 ColorDelVertice(VerticeSt x);
/*
 * Returns the color which vertex x is colored with.
 */

u32 GradoDelVertice(VerticeSt x);
/*
 * Returns degree of vertex x.
 */

u32 NombreDelVertice(VerticeSt x);
/*
 * Returns the real name of vertex x.
 */

void ImprimirVecinosDelVertice(VerticeSt x, NimheP G);
/*
 * Prints a list of vertex x's neighbors in standard output. The list
 * must be formed by the real names of the vertices, separated by commas,
 * with a period at the end of the list.
 */

/* FUNCTIONS TO RETRIEVE DATA FROM A GRAPH  */

u32 NumeroDeVertices(NimheP G);
/*
 * Returns the number of vertices in graph G.
 */

u32 NumeroDeLados(NimheP G);
/*
 * Returns the number of edges in graph G.
 */

u32 NumeroDeVerticesDeColor(NimheP G, u32 i);
/*
 * Returns the number of vertices colored with color i. (if i = 0
 * returns the number of uncolored vertices).
 */

u32 ImprimirVerticesDeColor(NimheP G, u32 i);
/*
 * Vertices having color i, separated by commas and a period after
 * the last color. (If i = 0 this list will be the list of uncolored
 * vertices).
 * For example:
 * Vértices de Color 3: 15,17,1.
 *
 * Vertices need not necessarily to be sorted.
 * If there is no vertex of color i, print “No hay vértices de color i”.
 * Returns the number of vertices of color i.
 */

u32 CantidadDeColores(NimheP G);
/*
 * Returns the number of colors used in the coloring of G.
 */

VerticeSt IesimoVerticeEnElOrden(NimheP G, u32 i);
/*
 * Returns vertex number i in the stored order at that moment in G.
 * (index 0 indicates the first vertex, index 1 the second, etc)
 */

VerticeSt IesimoVecino(NimheP G, VerticeSt x, u32 i);
/*
 * Returns the i-th neighbor of x in the order it is stored in G.
 */

#endif
