/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"
#include "ColorFuncs.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


/* COLORING FUNCTIONS */

int Chidos(NimheP G) {

    u32 visited = 0, i = 0;

    memset(G->color_array, 0, (G->no_vertices) * sizeof(u32));

    Queue *Q = NULL;
    Q = Queue_init(G->no_vertices);

    while(visited < G->no_vertices) {

        while(i < G->no_vertices) {
            if(!G->color_array[i]) {
                G->color_array[i] = 1;
                Enqueue(Q, G->order[i]);
                ++visited;
                ++i;
                break;
            }
            ++i;
        }

        while(!Queue_is_empty(Q)) {

            u32 V_index = Queue_front(Q);
            Dequeue(Q);

            for(u32 j = 0; j < G->degree_array[V_index]; j++) {

                u32 W_index = G->neighbors_array[V_index].data[j];

                if(!G->color_array[W_index]) {

                    G->color_array[W_index] = 3 - G->color_array[V_index];
                    ++visited;
                    Enqueue(Q, W_index);

                } else if(G->color_array[W_index] == G->color_array[V_index]) {

                    Queue_free(Q);
                    return 0;
                }
            }
        }
    }

    Queue_free(Q);

    return 1;
 }

u32 Greedy(NimheP G) {

    memset(G->used, false, (G->no_vertices + 1) * sizeof(bool));
    memset(G->vertices_with_color, 0, (G->no_vertices + 1) * sizeof(u32));
    memset(G->color_array, 0, (G->no_vertices) * sizeof(u32));

    G->coloring = 1;
    G->color_array[G->order[0]] = 1;
    G->vertices_with_color[0] = G->no_vertices - 1;
    G->vertices_with_color[1] = 1;

    u32 no_neighbors, neighbor_color, i, j;

    /* Assign colors to remaining V-1 vertices */
    for(i = 1; i < G->no_vertices; i++) {

        /* Process all adjacent vertices and flag their colors as unavailable */
        no_neighbors = G->degree_array[G->order[i]];

        for(j = 0; j < no_neighbors; j++) {
            neighbor_color = G->color_array[G->neighbors_array[G->order[i]].data[j]];
            if(neighbor_color != 0)
                G->used[neighbor_color] = true;
        }

        /* Find first available color */
        for(j = 1; j <= G->no_vertices; j++)
            if(!G->used[j])
                break;

        /* Assign the found color */
        G->color_array[G->order[i]] = j;

        /*  */
        ++G->vertices_with_color[j];
        --G->vertices_with_color[0];

        G->coloring = max(G->coloring, j);

        /* Reset the values back to false for the next iteration */
        for(j = 0; j < no_neighbors; j++) {
            u32 neighbor_color = G->color_array[G->neighbors_array[G->order[i]].data[j]];
            if(neighbor_color != 0)
                G->used[neighbor_color] = false;
        }
    }

    return G->coloring;
}
