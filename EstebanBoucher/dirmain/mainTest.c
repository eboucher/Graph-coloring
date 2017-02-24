/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include <stdio.h>
#include <stdlib.h>
#include "Cthulhu.h"

/* Function to compute min value of two values with given type */
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

/* time() function prototype to be used for rand value generaton */
u32 time(u32 *t);

/* shuffle function to be used with OrdenAleatorio order. Arrange
   the N elements of ARRAY in random order using the given seed. */
void shuffle_f(u32 *array, u32 n, u32 seed) {
    /* Set the seed to be used by rand() to generate "random" numbers */
    srand(seed);
    if(n > 1) {
        u32 i;
        for(i = 0; i < n-1; i++) {
            /* Pick a random position to swap with the one being checked */
            u32 j = i + rand() / (RAND_MAX / (n - i) + 1);
            /* Save j-th value in array in a temporary variable */
            u32 t = array[j];
            /* Swap these two values */
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main() {

    /* Variables Declaration */

    /* Last coloring obtained with Greedy, used in many iterations */
    u32 coloring;
    /* Best coloring obtained so far with Greedy runs */
    u32 best_coloring;
    /* Coloring got with Greedy at WelshPowell order */
    u32 WP_coloring = 0;

    /* ======================================================== */

    /* Read Graph */
    NimheP graph = NuevoNimhe();
    if (graph == NULL) {
        perror("Error en el formato de entrada\n");
        exit(EXIT_FAILURE);
    }

    /* Check whether the given graph is bipartite or not */
    if (Chidos(graph)) {
        printf("Grafo Bipartito\n");
        return (DestruirNimhe(graph) == 1 ? 0 : 1);
    } else {
        printf("Grafo No Bipartito\n");
    }

    /* Get the number of vertices on the graph */
    u32 no_vertices = NumeroDeVertices(graph);

    printf("Name array: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->name_array[i]);
    printf("\n");
    printf("Natural order: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->natural_order[i]);
    printf("\n");
    printf("Name array in natural order: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->name_array[graph->natural_order[i]]);
    printf("\n");
    printf("Degree array: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->degree_array[i]);
    printf("\n");
    printf("Array of colors: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->color_array[i]);



    printf("\nWhat's the order for the vertices in graph?\n");
    printf("Order array: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->name_array[graph->order[i]]);
    printf("\nNow let's call Revierte function\n");
    Revierte(graph);
    coloring = Greedy(graph);
    printf("What's the new order for the vertices in graph?\n");
    printf("Order array: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->name_array[graph->order[i]]);
    printf("\n");
    printf("-----------------------------------\n\n");
    /* Order graph vertices with Welsh Powell order */
    OrdenWelshPowell(graph);
    printf("\n");
    printf("Current order: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->order[i]);
    WP_coloring = Greedy(graph);
    printf("\n");
    printf("Name array in Welsh-Powell order: ");
    for(u32 i=0; i<no_vertices; i++)
        printf(", %u",graph->name_array[graph->order[i]]);


    /* Best coloring so far is the number of vertices in the graph */
    best_coloring = no_vertices;

    /* Set the seed to be used by rand() to generate "random" numbers */
    srand(time(NULL));


    /* Color graph vertices using Greedy algorithm */
    WP_coloring = Greedy(graph);
    /* Print coloring obtained */
    printf("\n coloreo con Greddy en WelshPowell:%u colores\n", WP_coloring);

    /* Check if some of these runs gave X(G) = 3 and stop */
    if((WP_coloring == 3) || (best_coloring == 3)) {
        printf("X(G) = 3\n");
        /* Destroy graph struct and return */
        return (DestruirNimhe(graph) == 1 ? 0 : 1);
    }

    /* Set coloring variable to current graph coloring */
    coloring = CantidadDeColores(graph);
    /* Best coloring set to current coloring for now */
    best_coloring = coloring;


    /* Sort vertices in graph using Revierte */
    Revierte(graph);
    /* And color the graph one last time */
    coloring = Greedy(graph);

    /* Destroy graph struct and return */
    return (DestruirNimhe(graph) == 1 ? 0 : 1);
}
