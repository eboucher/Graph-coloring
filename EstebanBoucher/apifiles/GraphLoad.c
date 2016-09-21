/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"
#include "GraphLoad.h"
#include "DataStructs.h"

u32 hash_code(u32 key, u32 size) {

    u32 hash = key;
    hash ^= size;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return key % size;
}

u32 find_vertex_hash(NimheP G, u32 vertex, bool *v_loaded) {

    /* Get vertex hash */
    u32 hash_index = hash_code(vertex, G->no_vertices);
    /* Flag variable to stop looping when all the graph has been checked */
    u32 counter = G->no_vertices;

    /* Find corresponding position in name_array: Move until an empty cell or
       until current cell found is already assigned to fst_vertex */
    while(counter && G->vertices_checker < G->no_vertices + 1 &&
          v_loaded[hash_index] && G->name_array[hash_index] != vertex) {

        /* go to next cell */
        ++hash_index;
        /* wrap around the table */
        hash_index %= G->no_vertices;

        /* Decrement the counter */
        --counter;
    }
    /* Check whether the while exited because vertex was not found in G */
    if(!v_loaded[hash_index]) {
        /* This must be a new vertex, add it to the graph */
        G->name_array[hash_index] = vertex;
        G->order[hash_index] = hash_index;
        G->natural_order[hash_index] = hash_index;
        /* Initialize its list of neighbors in the graph struct */
        vector_init(&G->neighbors_array[hash_index]);
        /* Now, set v_loaded array to indicate that the given vertex is
           already loaded in the graph */
        v_loaded[hash_index] = true;
        /* Increment number of vertices loaded */
        ++G->vertices_checker;

    } else if(counter)
        /* Increment number of vertices loaded */
        ++G->vertices_checker;

    return hash_index;
}

void insert_edge(NimheP G, u32 fst_vertex, u32 snd_vertex, bool *v_loaded) {

    /* Get hash index in name_array of each vertex */

    u32 fst_index = find_vertex_hash(G, fst_vertex, v_loaded);
    u32 snd_index = find_vertex_hash(G, snd_vertex, v_loaded);

    /* Only attempt to add each other as neighbors if no extra edge has been
       found in the input */
    if(G->vertices_checker < G->no_vertices + 1) {
        /* Second vertex as new neighbor in first vertex list's of neighbors */
        vector_append(&G->neighbors_array[fst_index], snd_index);
        /* Increment fst_vertex degree */
        ++G->degree_array[fst_index];

        /* Second vertex as new neighbor in first vertex list's of neighbors */
        vector_append(&G->neighbors_array[snd_index], fst_index);
        /* Increment snd_vertex degree */
        ++G->degree_array[snd_index];
    }
}
