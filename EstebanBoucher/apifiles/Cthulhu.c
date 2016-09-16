/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"
#include "DataStructs.h"

/* GRAPH CONSTRUCTION AND DESTRUCTION FUNCTIONS */

NimheP NuevoNimhe(void) {

    char line[LINE_LENGHT], *line_ptr;

    /* Read a line from stdin, store it on 'line' and point to that line using line_ptr */
    line_ptr = fgets(line, sizeof(line), stdin);

    if(line_ptr == NULL) {
        /* If this is the case, no data has been found in the file,
           therefore the program must be ended with an error message. */
        perror("Invalid file.\n");
        exit(EXIT_FAILURE);
    }

    NimheP new_nimhe = NULL;                            /* Create a new graph called new_nimhe */
    new_nimhe = calloc(1, sizeof(struct _NimheSt_t));   /* Allocate memory for new_nimhe */

    /* Variables that will be used to check that the file format is correct */
    //const char whitespace[] = " ";
    char edge_word[4] = "\0";
    char p_letter, e_letter;

    /* Variables used to temporally store vertices of an edge */
    u32 fst_vertex, snd_vertex;

    while(!strncmp(line_ptr, "c ", 2)) {
        /* Loop until no more comment lines are found */
        line_ptr = fgets(line, sizeof(line), stdin);
    }

    /* Comment lines already ignored, next line must be where number of vertices and edges are found */
    if(!strncmp(line_ptr, "p ", 2)) {
        /* case 'p ' detected, number of vertices and edges are expected to follow */

        sscanf(line_ptr, "%c %s %u %u", &p_letter, edge_word, &new_nimhe->no_vertices, &new_nimhe->no_edges);

        if(strcmp(edge_word, "edge")) {
            perror("Wrong format in line indicating number of vertices and edges.\n");
            exit(EXIT_FAILURE);
        } else {
            /* Allocate enough memory for the array of vertices real names */
            new_nimhe->name_array = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate enough memory for the array of colors of vertices */
            new_nimhe->color_array = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate enough memory for the array of degrees of vertices */
            new_nimhe->degree_array = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate enough memory for the array of RAR order of vertices */
            new_nimhe->RAR_order_array = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate enough memory to store all lists of vertex neighbors */
            new_nimhe->neighbors_array = malloc(new_nimhe->no_vertices * sizeof(Vector));

            /* Allocate enough memory to store current order */
            new_nimhe->order = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate enough memory to store natural order */
            new_nimhe->natural_order = malloc(new_nimhe->no_vertices * sizeof(u32));

            /* Allocate memory for the array to store number of vertices colored with each color */
            new_nimhe->vertices_with_color = malloc((new_nimhe->no_vertices + 1) * sizeof(u32));

        }
    } else {
        perror("Line indicating number of vertices and edges not found.\n");
        exit(EXIT_FAILURE);
    }

    /* Array of bools to check during graph load if there is a vertex in the given position */
    bool *vertex_loaded;
    vertex_loaded = calloc(new_nimhe->no_vertices, sizeof(bool));

    /* Variable used to check if the following lines are exactly new_nimhe->edges */
    u32 lines_counter = new_nimhe->no_edges;

    /* Get another line */
    line_ptr = fgets(line, sizeof(line), stdin);

    while(line_ptr && lines_counter) {
        /* there is an edge in this line to load to new_nimhe */

        if(!strncmp(line_ptr, "e ", 2)) {

            /* Scan line parameters into different tokens */
            sscanf(line_ptr, "%c %u %u", &e_letter, &fst_vertex, &snd_vertex);

            insert_edge(new_nimhe, fst_vertex, snd_vertex, vertex_loaded);

        } else {
            perror("Wrong format in edge line.\n");
            exit(EXIT_FAILURE);
        }
        --lines_counter;
        line_ptr = fgets(line, sizeof(line), stdin);
    }

    /* Free temporary array used during load */
    free(vertex_loaded);
    vertex_loaded = NULL;
    
    /* Allocate memory for the array of used colors to be used in Greedy coloring function */
    new_nimhe->used_color = malloc((new_nimhe->no_vertices + 1) * sizeof(bool));

    int OrdenNat(const void *elem1, const void *elem2) {

        u32 fst = (u32)elem1;
        u32 snd = (u32)elem2;
        if(new_nimhe->name_array[fst] > new_nimhe->name_array[snd]) return 1;
        if(new_nimhe->name_array[fst] < new_nimhe->name_array[snd]) return -1;
        return 0;
    }

    qsort(new_nimhe->natural_order, new_nimhe->no_vertices, sizeof(u32), &OrdenNat);

    return new_nimhe;
}

int DestruirNimhe(NimheP G) {
    
    if(G != NULL) {

        free(G->name_array);
        G->name_array = NULL;

        free(G->color_array);
        G->color_array = NULL;

        free(G->degree_array);
        G->degree_array = NULL;

        free(G->RAR_order_array);
        G->RAR_order_array = NULL;

        for(u32 i = 0; i < G->no_vertices; i++)
            vector_free(G->neighbors_array[i]);

        free(G->order);
        G->order = NULL;

        free(G->vertices_with_color);
        G->vertices_with_color = NULL;

        free(G->used_color);
        G->used_color = NULL;

        free(G);
        G = NULL;
    }

    return 1;
}
