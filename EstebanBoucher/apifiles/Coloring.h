/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef COLORING_H
#define COLORING_H

#include "Types.h"

typedef struct _NimheSt_t *NimheP;       /* Forward declaration of *NimheP */

/* FUNCIONES DE COLOREO */

int Chidos(NimheP G);
/*
 * Devuelve 1 si χ(G) = 2, 0 si no.
 */

u32 Greedy(NimheP G);
/*
 * Corre greedy en G con el orden interno que debe estar guardado de alguna
 * forma dentro de G. Devuelve el numero de colores que se obtiene.
 */

void OrdenNatural(NimheP G);
/*
 * Ordena los vertices en orden creciente de sus “nombres” reales.
 */

void OrdenWelshPowell(NimheP G);
/*
 * Ordena los vertices de G de acuerdo con el orden Welsh-Powell, es decir,
 * con los grados en orden no creciente.
 */

void ReordenAleatorioRestringido(NimheP G);
/*
 * Si G esta coloreado con r colores y W1 son los vertices coloreados con 1,
 * W2 los coloreados con 2, etc, entonces esta función ordena los vertices 
 * poniendo primero los vertices de Wj1 (en algún orden) luego los de Wj2
 * (en algún orden), etc, donde j1, j2, ... son aleatorios (pero distintos).
 */

void GrandeChico(NimheP G);
/*
 * Si G esta coloreado con r colores y W1 son los vertices coloreados con 1,
 * W2 los coloreados con 2, etc, entonces esta función ordena los vértices 
 * poniendo primero los vertices de Wj1 (en algún orden) luego los de Wj2
 * (en algún orden), etc, donde j1, j2, ... son tales que |Wj1| ≥ |Wj2| ≥
 * ... ≥ |Wjr| .
 */

void ChicoGrande(NimheP G);
/*
 * Idem que el anterior excepto que ahora el orden es tal que |Wj1| ≤ |Wj2|
 * ≤ ... ≤ |Wjr| .
 */

void Revierte(NimheP G);
/*
 * Si G esta coloreado con r colores y W1 son los vertices coloreados con 1,
 * W2 los coloreados con 2, etc, entonces esta función ordena los vertices 
 * poniendo primero los vertices de Wr (en algún orden) luego los de Wr−1
 * (en algún orden), etc.
 */

void OrdenEspecifico(NimheP G, u32* x);
/*
 * La imagen de x deben ser todos los numeros entre 0 y n − 1, sin repetir.
 * La función primero chequea que x cumpla esa condición. Si no lo hace, la
 * función deja el orden de G como estaba. Si x cumple la condición, entonces
 * la funci´on ordena los vertices con OrdenNatural(), luego lee el orden dado
 * en la string x y los ordena de acuerdo a lo que lee. Es decir, si luego de
 * OrdenNatural los vertices quedaron ordenados como, por ejemplo, V[0],V[1],
 * ...,V[n-1], luego de OrdenEspecifico el orden debe ser V[x[0]],V[x[1]],...,
 * V[x[n-1]].
 */

#endif
