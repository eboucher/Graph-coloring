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
#include "Types.h"

#define LINE_LENGHT 80

/* STRUCTURES FOR GRAPH REPRESENTATION */

typedef struct _VerticeSt_t VerticeSt;

typedef struct _NimheSt_t *NimheP;


/* GRAPH CONSTRUCTION AND DESTRUCTION FUNCTIONS */

NimheP NuevoNimhe(void);
/*
 * Allocates memory, initializes what needs to be initialized in the struct
 * NimheSt returns a pointer to it. Besides, it reads a graph from standard
 * input in the format specified in DIMACS and fills the NimheSt structure
 * with that data.
 *
 * In case of error, the function returns a pointer to NULL. Possible errors
 * can be failure to allocate memory, but also that the input format is
 * invalid, for example, the first line withouth comments does not start
 * with p, or that n* != n (that is specified in the input format).
 */

int DestruirNimhe(NimheP G);
/*
 * Destroys and frees allocated memory. Returns 1 if all went well and 0
 * otherwise.
 */

void shuffle(u32 *array, u32 n, u32 seed);
/*
 * Arrange the N elements of ARRAY in random order. Only effective if N is much
 * smaller than RAND_MAX.
 */

#endif
