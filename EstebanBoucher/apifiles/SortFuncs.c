/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "SortFuncs.h"

u32 time(u32 *t);

/* AUXILIAR FUNCTION */

void shuffle(u32 *array, u32 n, u32 seed) {
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

/* SORTING FUNCTIONS */

void OrdenNatural(NimheP G) {

    /* Declare a local comparison function */
    int CompOrdenNat(const void *elem1, const void *elem2) {
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->name_array[*fst] > G->name_array[*snd]) return 1;
        if(G->name_array[*fst] < G->name_array[*snd]) return -1;
        return 0;
    }
    /* Order graph vertices according to the declared comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenNat);
}

void OrdenWelshPowell(NimheP G) {

    /* Declare a local comparison function */
    int CompOrdenWP(const void *elem1, const void *elem2) {
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->degree_array[*fst] < G->degree_array[*snd]) return 1;
        if(G->degree_array[*fst] > G->degree_array[*snd]) return -1;
        return 0;
    }
    /* Order vertices according to the Welsh-Powell comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenWP);
}

void ReordenAleatorioRestringido(NimheP G) {

    /* Create an array to store a specific order */
    u32 *specific_order;
    /* Allocate memory for G->coloring values in specific_order array */
    specific_order = malloc(G->coloring * sizeof(u32));

    /* Assign values in range 0 to coloring-1 in specific_order array */
    for(u32 i = 0; i < G->coloring; i++)
        specific_order[i] = i + 1;

    /* Create a seed variable */
    u32 seed;
    /* generate a seed for shuffle function */
    seed = time(NULL);
    /* Shuffle specific_order array using the generated seed */
    shuffle(specific_order, G->coloring, seed);

    for(u32 i = 0; i < G->no_vertices; i++)
        G->RAR_order_array[i] = specific_order[G->color_array[i]];

    /* Declare a local comparison function */
    int CompRAR(const void *elem1, const void *elem2) {
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->RAR_order_array[*fst] > G->RAR_order_array[*snd]) return 1;
        if(G->RAR_order_array[*fst] < G->RAR_order_array[*snd]) return -1;
        return 0;
    }

    /* Order graph vertices according to the declared comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompRAR);

    /* Free allocated memory for specific_order array */
    free(specific_order);
    specific_order = NULL;
}

void GrandeChico(NimheP G) {

    /* Declare a local comparison function */
    int CompOrdenGrandeChico(const void *elem1, const void *elem2) {

        int result = 0;
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        /* Get number of vertices colored with the same color as fst and snd */
        u32 no_vertices_fst = G->vertices_with_color[G->color_array[*fst]];
        u32 no_vertices_snd = G->vertices_with_color[G->color_array[*snd]];

        if(no_vertices_fst < no_vertices_snd) result = 1;
        if(no_vertices_fst > no_vertices_snd) result = -1;
        if(no_vertices_fst == no_vertices_snd) {
            /* In case both colors "have" the same number of vertices, break
               ties using the color names in natural order */
            if(G->color_array[*fst] > G->color_array[*snd]) {
                result = 1;
            } else if(G->color_array[*fst] < G->color_array[*snd]) {
                result = -1;
            } else {
                result = 0;
            }
        }
        return result;
    }

    /* Order graph vertices according to the declared comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenGrandeChico);
}

void ChicoGrande(NimheP G) {

    /* Declare a local comparison function */
    int CompOrdenChicoGrande(const void *elem1, const void *elem2) {

        int result = 0;
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        /* Get number of vertices colored with the same color as fst and snd */
        u32 no_vertices_fst = G->vertices_with_color[G->color_array[*fst]];
        u32 no_vertices_snd = G->vertices_with_color[G->color_array[*snd]];

        if(no_vertices_fst > no_vertices_snd) result = 1;
        if(no_vertices_fst < no_vertices_snd) result = -1;
        if(no_vertices_fst == no_vertices_snd) {
            /* In case both colors "have" the same number of vertices, break
               ties using the color names in natural order */
            if(G->color_array[*fst] > G->color_array[*snd]) {
                result = 1;
            } else if(G->color_array[*fst] < G->color_array[*snd]) {
                result = -1;
            } else {
                result = 0;
            }
        }
        return result;
    }

    /* Order graph vertices according to the declared comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenChicoGrande);
}

void Revierte(NimheP G) {

    /* Declare a local comparison function */
    int CompOrdenRevierte(const void *elem1, const void *elem2) {
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->color_array[*fst] > G->color_array[*snd]) return 1;
        if(G->color_array[*fst] < G->color_array[*snd]) return -1;
        return 0;
    }

    /* Order graph vertices according to the declared comparison function */
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenRevierte);
}

void OrdenEspecifico(NimheP G, u32* x) {
    /* Variable used to check if string x meets the condition mentioned in
       the header file */
    bool meets_condition = true;
    /* Here, G->used array is used to mark positions as "used", so that the
       next try to access them will result in a "repeated" and thus aborting.
       Initially, no position is marked as "used" */
    memset(G->used, false, (G->no_vertices + 1) * sizeof(bool));
    /* Check if there is some out of bounds or repeated value in x */
    for(u32 i = 0; i < G->no_vertices; i++) {
        if((x[i] >= G->no_vertices) || ((x[i] < G->no_vertices)
           && (G->used[x[i]]))) {
            /* Condition is not met */
            meets_condition = false;
            break;
        }
        else
            /* Mark this position x[i]-th position in G as "used" */
            G->used[x[i]] = true;
    }

    if(meets_condition)
        for(u32 i = 0; i < G->no_vertices; i++)
            /* New order is assigned according to the description of the
               function in the header file */
            G->order[i] = G->natural_order[x[i]];
}
