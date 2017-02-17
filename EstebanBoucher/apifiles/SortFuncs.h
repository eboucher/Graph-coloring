/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef SORTFUNCS_H
#define SORTFUNCS_H

#include "Types.h"

/* AUXILIAR FUNCTION */

void shuffle(u32 *array, u32 n, u32 seed);
/*
 * Shuffle array elements in random order using the given seed.
 */

/* SORTING FUNCTIONS */

void OrdenNatural(NimheP G);
/*
 * Arrange graph vertices in increasing order of their real "names".
 */

void OrdenWelshPowell(NimheP G);
/*
 * Sorts the vertices of G according to the Welsh-Powell order, ie, 
 * with their degrees in non-increasing order.
 */

void ReordenAleatorioRestringido(NimheP G);
/*
 * If G is colored with r colors and W1 are the vertices colored 1,
 * W2 colored with 2, etc, then this function sorts the vertices
 * putting first the vertices of Wj1 (in some order) then of Wj2
 * (in some order), etc, where j1, j2, ... are random (but different).
 */

void GrandeChico(NimheP G);
/*
 * If G is colored with r colors and W1 are the vertices colored 1,
 * W2 colored with 2, etc, then this function sorts the vertices
 * putting first the vertices of Wj1 (in some order) then of Wj2
 * (in some order), etc, where j1, j2, ... are such that |WJ1|≥|WJ2|≥
 * ... ≥|Wjr| .
 */

void ChicoGrande(NimheP G);
/*
 * Idem as above except that the order now is such that |Wj1| ≤ |Wj2|
 * ≤ ... ≤ |Wjr| .
 */

void Revierte(NimheP G);
/*
 * If G is colored with r colors and W1 are the vertices colored 1,
 * W2 colored with 2, etc, then this function sorts the vertices
 * putting first the vertices of Wr (in some order) then Wr-1
 * (in some order), etc.
 */

void OrdenEspecifico(NimheP G, u32* x);
/*
 * The image of x must be all numbers between 0 and n - 1, without repeating.
 * The first function checks that x meets that condition. If not, the function
 * lets the order of G as it was. If x satisfies the condition, then the
 * function sorts the vertices with OrdenNatural(), then reads the given order
 * in the string x and sorts them according to what it reads. That is, if after
 * OrdenNatural vertices were ordered as, for example, V[0],V[1],...,V[n-1], 
 * after OrdenEspecifico the order should be V[x[0]],V[x[1]],...,V[x[n-1]].
 */

 #endif