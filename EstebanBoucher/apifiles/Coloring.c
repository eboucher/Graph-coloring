/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"
#include "Coloring.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

u32 time(u32 *t);


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

    memset(G->used_color, false, (G->no_vertices + 1) * sizeof(bool));
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
                G->used_color[neighbor_color] = true;
        }

        /* Find first available color */
        for(j = 1; j <= G->no_vertices; j++)
            if(!G->used_color[j])
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
                G->used_color[neighbor_color] = false;
        }
    }

    return G->coloring;
}


/* ====================================================================== */

/* Ordering functions */

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

bool meets_condition(NimheP G, u32* x) {

    if(sizeof(x)/sizeof(u32) != G->no_vertices)
        return false;

    bool *used;
    used = malloc(G->no_vertices * sizeof(bool));
    memset(used, false, (G->no_vertices + 1) * sizeof(bool));
    for(u32 i = 0; i < G->no_vertices; i++) {
        if((x[i] >= G->no_vertices) || ((x[i] < G->no_vertices) && (used[x[i]])))
            return false;
        else
            used[x[i]] = true;
    }
    return true;
}

void OrdenEspecifico(NimheP G, u32* x) {

    if(meets_condition(G, x))
        for(u32 i = 0; i < G->no_vertices; i++)
            G->order[i] = G->natural_order[x[i]];
}
