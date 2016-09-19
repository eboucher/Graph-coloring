/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include <stdio.h>
#include <stdlib.h>
#include "Cthulhu.h"

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

u32 time(u32 *t);

void main_shuffle(u32 *array, u32 n, u32 seed) {
    srand(seed);
    if(n > 1) {
        u32 i;
        for(i = 0; i < n-1; i++) {
          u32 j = i + rand() / (RAND_MAX / (n - i) + 1);
          u32 t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int main() {

    /* Variables Declaration */

    u32 *specific_order;

    u32 coloring;               /* Last coloring obtained with Greedy, used in many iterations */
    u32 best_coloring;          /* Best coloring so far with given runs */
    u32 seed, best_seed = 1;    /* Seed used for coloring at these tries and best seed so far */
    u32 WP_coloring = 0;        /* Coloring got with Greedy at WelshPowell order */

    u32 random_option = 0;      /* Random option to be used for each of the 1000 coloring tries */

    u32 a = 0;     /* Number of times run Greedy with ChicoGrande */
    u32 b = 0;     /* Number of times run Greedy witd GrandeChico */
    u32 c = 0;     /* Number of times run Greedy with Revierte */
    u32 d = 0;     /* Number of times run Greedy with ReaordenAleatorioRestringido */

    /* ================================================== */

    /* Read Graph */
    NimheP graph = NuevoNimhe();
    if (graph == NULL) {
        perror("Error en el formato de entrada\n");
        exit(EXIT_FAILURE);
    }

    /* Check Bipartite */
    if (Chidos(graph)) {
        printf("Grafo Bipartito\n");
        return (DestruirNimhe(graph) == 1 ? 0 : 1);
    } else {
        printf("Grafo NO Bipartito\n");
    }

    /* Starting to run Greedy 10 times with Orden Aleatorio order */

    u32 no_vertices = NumeroDeVertices(graph);
    specific_order = malloc(no_vertices * sizeof(u32));

    best_coloring = no_vertices;

    for(u32 k = 0; k < no_vertices; k++)
        specific_order[k] = k;

    srand(time(NULL));
    for (int i=1; i<=10; i++) {
        seed = rand();
        main_shuffle(specific_order, no_vertices, seed);

        OrdenEspecifico(graph, specific_order);
        coloring = Greedy(graph);
        printf("coloreo aleatorio numero %u: %u colores\n", i, coloring);

        if(coloring < best_coloring) {
            best_coloring = coloring;
            best_seed = seed;
        }
    }

    /* Starting to run Greedy once, with Welsh Powell order */

    OrdenWelshPowell(graph);
    WP_coloring = Greedy(graph);
    printf("\n coloreo con Greddy en WelshPowell:%u colores\n", WP_coloring);

    /* Check if some run gives X(G) = 3 and stop */

    if((WP_coloring == 3) || (best_coloring == 3)) {
        printf("X(G) = 3\n");
        return (DestruirNimhe(graph) == 1 ? 0 : 1);
    }

    if(best_coloring < WP_coloring) {
        main_shuffle(specific_order, no_vertices, best_seed);
        OrdenEspecifico(graph, specific_order);
        coloring = Greedy(graph);
    }

    coloring = no_vertices;
    best_coloring = no_vertices;

    /* Starting to run Greedy, iterating 1001 times */

    printf("\n====Comenzando Greedy Iterado 1001 veces====\n\n");

    srand(time(NULL));

    for (int i=1; i<=1001; i++) {

        random_option = (rand() % 16);
        if (random_option <= 7) {
            ChicoGrande(graph);
            coloring = Greedy(graph);
            a++;
            //printf("%i  Greedy sobre el Grafo: %i\n", i, coloring);
        } else if ((random_option > 7) && (random_option <= 12)) {
            Revierte(graph);
            coloring = Greedy(graph);
            //printf("%i  Greedy sobre el Grafo: %i\n", i, coloring);
            c++;
        } else if ((random_option > 12) && (random_option <= 14)) {
            GrandeChico(graph);
            coloring = Greedy(graph);
            //printf("%i  Greedy sobre el Grafo: %i\n", i, coloring);
            b++;
        } else {
            ReordenAleatorioRestringido(graph);
            coloring = Greedy(graph);
            //printf("%i  Greedy sobre el Grafo: %i\n", i, coloring);
            d++;
        }
        best_coloring = min(best_coloring, CantidadDeColores(graph));
    }

    Revierte(graph);
    coloring = Greedy(graph);
    best_coloring = min(best_coloring, CantidadDeColores(graph));

    printf("Mejor coloreo con Greedy iterado 1001 veces: %u colores\n", best_coloring);
    printf("(%i CG,%i GC, %i R, %i RAR)\n", a, b, c, d);

    free(specific_order);
    specific_order = NULL;

    return (DestruirNimhe(graph) == 1 ? 0 : 1);
}
