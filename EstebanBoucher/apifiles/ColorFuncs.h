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
 * Devuelve 1 si χ(G) = 2, 0 si no.
 */

u32 Greedy(NimheP G);
/*
 * Corre greedy en G con el orden interno que debe estar guardado de alguna
 * forma dentro de G. Devuelve el numero de colores que se obtiene.
 */

#endif
