/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef GRAPHLOAD_H
#define GRAPHLOAD_H

#include "Types.h"

u32 hash_code(u32 key, u32 size);
/*
 * Define a hashing method to compute the hash code for the key in the
 * range from 0 to size - 1.
 */

u32 find_vertex_hash(NimheP G, u32 vertex, bool *v_loaded);
/*
 * Whenever an element is to be searched. Compute the hash code of the key
 * passed and locate the actual vertex index using the hash code as index
 * in the array. Use linear probing to get element ahead if the element was
 * not found at the computed hash code. In case input vertex was not in G, 
 * assign a new cell to it in G->name_array at the corresponding position
 * and initialize its vector of neighbors.
 */

void insert_edge(NimheP G, u32 fst_vertex, u32 snd_vertex, bool *v_loaded);
/*
 * Whenever an edge is to be inserted. Calls find_vertex_hash for each vertex
 * to make sure both have assigned cells in G->name_array and get their
 * identifiers in G. Then add each other as neighbors in each other's list
 * of neighbors.
 */

#endif
