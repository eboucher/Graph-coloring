/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "SortFuncs.h"

u32 time(u32 *t);

/* AUXILIAR FUNCTION */

void shuffle(u32 *array, u32 n, u32 seed) {
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

/* SORTING FUNCTIONS */

void OrdenNatural(NimheP G) {

    int CompOrdenNat(const void *elem1, const void *elem2) {

        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->name_array[*fst] > G->name_array[*snd]) return 1;
        if(G->name_array[*fst] < G->name_array[*snd]) return -1;
        return 0;
    }

    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenNat);
}

void OrdenWelshPowell(NimheP G) {

    int CompOrdenWP(const void *elem1, const void *elem2) {
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->degree_array[*fst] > G->degree_array[*snd]) return 1;
        if(G->degree_array[*fst] < G->degree_array[*snd]) return -1;
        return 0;
    }
    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenWP);
}

void ReordenAleatorioRestringido(NimheP G) {

    u32 *specific_order, seed;
    specific_order = malloc(G->coloring * sizeof(u32));

    for(u32 k = 0; k < G->coloring; k++)
        specific_order[k] = k + 1;

    seed = time(NULL);
    shuffle(specific_order, G->coloring, seed);


    int CompREordenAleatorioRestringido(const void *elem1, const void *elem2) {
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->RAR_order_array[*fst] > G->RAR_order_array[*snd]) return 1;
        if(G->RAR_order_array[*fst] < G->RAR_order_array[*snd]) return -1;
        return 0;
    }

    qsort(G->order, G->no_vertices, sizeof(u32), &CompREordenAleatorioRestringido);

    free(specific_order);
    specific_order = NULL;
}

void GrandeChico(NimheP G) {

    int CompOrdenGrandeChico(const void *elem1, const void *elem2) {

        int result = 0;
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;

        u32 no_colors_fst = G->vertices_with_color[G->color_array[*fst]];
        u32 no_colors_snd = G->vertices_with_color[G->color_array[*snd]];

        if(no_colors_fst < no_colors_snd) result = 1;
        if(no_colors_fst > no_colors_snd) result = -1;
        if(no_colors_fst == no_colors_snd) {
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


    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenGrandeChico);
}

void ChicoGrande(NimheP G) {

    int CompOrdenChicoGrande(const void *elem1, const void *elem2) {

        int result = 0;
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;

        u32 no_colors_fst = G->vertices_with_color[G->color_array[*fst]];
        u32 no_colors_snd = G->vertices_with_color[G->color_array[*snd]];

        if(no_colors_fst > no_colors_snd) result = 1;
        if(no_colors_fst < no_colors_snd) result = -1;
        if(no_colors_fst == no_colors_snd) {
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

    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenChicoGrande);
}

void Revierte(NimheP G) {

    int CompOrdenRevierte(const void *elem1, const void *elem2) {
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->color_array[*fst] > G->color_array[*snd]) return 1;
        if(G->color_array[*fst] < G->color_array[*snd]) return -1;
        return 0;
    }

    qsort(G->order, G->no_vertices, sizeof(u32), &CompOrdenRevierte);
}

void OrdenEspecifico(NimheP G, u32* x) {

    bool meets_condition = true;

    memset(G->used, false, (G->no_vertices + 1) * sizeof(bool));

    for(u32 i = 0; i < G->no_vertices; i++) {
        if((x[i] >= G->no_vertices) || ((x[i] < G->no_vertices) && (G->used[x[i]])))
            meets_condition = false;
        else
            G->used[x[i]] = true;
    }

    if(meets_condition)
        for(u32 i = 0; i < G->no_vertices; i++)
            G->order[i] = G->natural_order[x[i]];
}