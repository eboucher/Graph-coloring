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
void main_shuffle(u32 *array, u32 n, u32 seed) {
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

    u32 *specific_order;      /* Auxiliar array of specific order to OrdenEspecifico function */
    u32 coloring;             /* Last coloring obtained with Greedy, used in many iterations */
    u32 best_coloring;        /* Best coloring obtained so far with Greedy runs */
    u32 seed, best_seed = 1;  /* Seed used for coloring at these tries and best seed so far */
    u32 WP_coloring = 0;      /* Coloring got with Greedy at WelshPowell order */
    u32 random_option = 0;    /* Random option to be used for each of the 1000 coloring tries */

    u32 a = 0;     /* Number of times Greedy was run with ChicoGrande */
    u32 b = 0;     /* Number of times Greedy was run with GrandeChico */
    u32 c = 0;     /* Number of times Greedy was run with Revierte */
    u32 d = 0;     /* Number of times Greedy was run with ReaordenAleatorioRestringido */

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

    /* Allocate memory of size no_vertices to generate a specific order */
    specific_order = malloc(no_vertices * sizeof(u32));

    /* Best coloring so far is the number of vertices in the graph */
    best_coloring = no_vertices;

    /* Assign values in range 0 to no_vertices-1 in specific_order array */
    for(u32 k = 0; k < no_vertices; k++)
        specific_order[k] = k;

    /* Set the seed to be used by rand() to generate "random" numbers */
    srand(time(NULL));

    /* Starting to run Greedy 10 times with Orden Aleatorio order */
    for (int i=1; i<=10; i++) {
        /* Pick a random seed */
        seed = rand();
        /* Shuffle specific_order array using recently generated seed */
        main_shuffle(specific_order, no_vertices, seed);
        /* Give a specific order for the vertices in graph to be used for Greedy coloring */
        OrdenEspecifico(graph, specific_order);
        /* Color graph vertices using Greedy algorithm */
        coloring = Greedy(graph);
        /* Print coloring obtained */
        printf("coloreo aleatorio numero %u: %u colores\n", i, coloring);
        /* Update best_coloring if a better coloring has been obtained */
        if(coloring < best_coloring) {
            best_coloring = coloring;
            best_seed = seed;
        }
    }

    /* Order graph vertices with Welsh Powell order */
    OrdenWelshPowell(graph);
    /* Color graph vertices using Greedy algorithm */
    WP_coloring = Greedy(graph);
    /* Print coloring obtained */
    printf("\n coloreo con Greddy en WelshPowell:%u colores\n", WP_coloring);

    /* Check if some of these runs gave X(G) = 3 and stop */
    if((WP_coloring == 3) || (best_coloring == 3)) {
        printf("X(G) = 3\n");
        /* Free allocated memory for specific_order array */
        free(specific_order);
        specific_order = NULL;
        /* Destroy graph struct and return */
        return (DestruirNimhe(graph) == 1 ? 0 : 1);
    }

    /* Update best order obtained and retrieve a previous order if necessary */
    if(best_coloring < WP_coloring) {
        /* Shuffle specific_order the same way as when it gave the best coloring obtained so far */
        main_shuffle(specific_order, no_vertices, best_seed);
        /* Set graph order back to the best order so far */
        OrdenEspecifico(graph, specific_order);
        /* Color the graph with that order again */
        coloring = Greedy(graph);
    }

    /* Set coloring variable to current graph coloring */
    coloring = CantidadDeColores(graph);
    /* Best coloring set to current coloring for now */
    best_coloring = coloring;

    /* Starting to run Greedy, iterating 1001 times */

    printf("\n====Comenzando Greedy Iterado 1001 veces====\n\n");

    /* Set the seed to be used by rand() to generate "random" numbers */
    srand(time(NULL));
    /* Loop to run Greedy 1000 times with random orders */
    for (int i=1; i<=1000; i++) {
        /* Pick a random option */
        random_option = (rand() % 16);
        if (random_option <= 7) {
            /* ChicoGrande with 50% probability */
            ChicoGrande(graph);
            /* Color graph vertices using Greedy algorithm */
            coloring = Greedy(graph);
            /* Increase ChicoGrande counter */
            a++;
        } else if ((random_option > 7) && (random_option <= 12)) {
            /* Revierte with 31,25% probability */
            Revierte(graph);
            /* Color graph vertices using Greedy algorithm */
            coloring = Greedy(graph);
            /* Increase Revierte counter */
            c++;
        } else if ((random_option > 12) && (random_option <= 14)) {
            /* GrandeChico with 12,5% probability */
            GrandeChico(graph);
            /* Color graph vertices using Greedy algorithm */
            coloring = Greedy(graph);
            /* Increase GrandeChico counter */
            b++;
        } else {
            /* ReordenAleatorioRestringido with 6,25% probability */
            ReordenAleatorioRestringido(graph);
            /* Color graph vertices using Greedy algorithm */
            coloring = Greedy(graph);
            /* Increase ReordenAleatorioRestringido counter */
            d++;
        }
        /* Update best_coloring obtained so far */
        best_coloring = min(best_coloring, CantidadDeColores(graph));
    }
    /* Sort vertices in graph using Revierte */
    Revierte(graph);
    /* And color the graph one last time */
    coloring = Greedy(graph);
    /* Update best_coloring */
    best_coloring = min(best_coloring, CantidadDeColores(graph));

    /* Print coloring obtained with Greedy iterating 1001 times */
    printf("Mejor coloreo con Greedy iterado 1001 veces: %u colores\n", best_coloring);
    /* Print the number of times the graph was colored using each of the above sorting fuctions */
    printf("(%i CG,%i GC, %i R, %i RAR)\n", a, b, c, d);

    /* Free allocated memory for specific_order array */
    free(specific_order);
    specific_order = NULL;

    /* Destroy graph struct and return */
    return (DestruirNimhe(graph) == 1 ? 0 : 1);
}
