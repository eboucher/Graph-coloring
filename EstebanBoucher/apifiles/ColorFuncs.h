/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef COLORFUNCS_H
#define COLORFUNCS_H

#include "Types.h"

/* COLORING FUNCTIONS */

int Chidos(NimheP G);
/*
 * Returns 1 if χ(G) = 2, 0 otherwise.
 */

u32 Greedy(NimheP G);
/*
 * Run greedy in G with the internal order. Returns the number of
 * colors obtained.
 */

#endif
