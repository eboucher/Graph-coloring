MATEMATICA DISCRETA II - PROYECTO 2016
=========================================
---

### Integrantes:

* [Astrada Lucas]                  leakarate06@gmail.com
* [Boucher Esteban]                eboucher7@gmail.com


---
> INFORME

flag --->> gcc ... -flto


CHIDOS!! 

    u32 i, j;

    G->coloring = 0;

    for(i = 0; i < G->no_vertices; i++)
        G->vertices_array[i].vertex_color = 0;

    for(i = 0; i < G->no_vertices; i++) {
        if(G->vertices_array[i].vertex_color == 0)
            G->vertices_array[i].vertex_color = 1;
        for(j = 0; j < G->vertices_array[i].vertex_degree; j++) {
            if(G->vertices_array[i].neighbors.data[j]->vertex_color == 0)
                G->vertices_array[i].neighbors.data[j]->vertex_color = 3 - G->vertices_array[i].vertex_color;
        }
    }

    for(i = 0; i < G->no_vertices; i++) {
        for(j = 0; j < G->vertices_array[i].vertex_degree; j++) {
            if(G->vertices_array[i].vertex_color == G->vertices_array[i].neighbors.data[j]->vertex_color)
                return 0;
        }
    }
    return 1;
