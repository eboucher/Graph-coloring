/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"
#include "VertexGraphData.h"


/* VERTEX FUNCTIONS */

u32 ColorDelVertice(VerticeSt x) {
    return(x.color);
}

u32 GradoDelVertice(VerticeSt x) {
    return(x.degree);
}

u32 NombreDelVertice(VerticeSt x) {
    return(x.name);
}

void ImprimirVecinosDelVertice(VerticeSt x, NimheP G) {

    for(u32 i = 0; i < G->neighbors_array[x.index].size; i++) {
        if(i < G->neighbors_array[x.index].size - 1)
            printf(" %u", G->name_array[G->neighbors_array[x.index].data[i]]);
        else
            printf(" %u.\n", G->name_array[G->neighbors_array[x.index].data[i]]);
    }
}


/* FUNCTIONS TO RETRIEVE DATA FROM A GRAPH  */

u32 NumeroDeVertices(NimheP G) {
    return(G->no_vertices);
}

u32 NumeroDeLados(NimheP G) {
    return(G->no_edges);
}

u32 NumeroDeVerticesDeColor(NimheP G, u32 i) {

    if((i > G->coloring) || (i == 0 && G->coloring)) {
        return 0;
    } else {
        return G->vertices_with_color[i];
    }
}

u32 ImprimirVerticesDeColor(NimheP G, u32 i) {

    u32 it;
    if((i > G->coloring) || (i == 0 && G->coloring))
        printf("No hay vertices de color i\n");

    else {
        printf("Vertices de Color %u:", i);
        for(it = 0; it < G->no_vertices; it++) {
            if(G->color_array[i] == i) {
                if(it == 0)
                    printf("%u, ", G->name_array[i]);
                else
                    printf(", %u", G->name_array[i]);
            }
        }
        printf(".\n");
    }

    return G->vertices_with_color[i];
}

u32 CantidadDeColores(NimheP G) {
    return(G->coloring);
}

VerticeSt IesimoVerticeEnElOrden(NimheP G, u32 i) {

    VerticeSt vertex;
    vertex.name = G->name_array[G->order[i]];
    vertex.degree = G->degree_array[G->order[i]];
    vertex.color = G->color_array[G->order[i]];
    vertex.index = G->order[i];


    return vertex;
}

VerticeSt IesimoVecino(NimheP G, VerticeSt x, u32 i) {

    VerticeSt ith_neighbor;

    u32 ith_index = vector_get(&G->neighbors_array[x.index], i);

    ith_neighbor.name = G->name_array[G->order[ith_index]];
    ith_neighbor.degree = G->degree_array[G->order[ith_index]];
    ith_neighbor.color = G->color_array[G->order[ith_index]];
    ith_neighbor.index = ith_index;

    return ith_neighbor;
}
