/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"

/* GRAPH CONSTRUCTION AND DESTRUCTION FUNCTIONS */

NimheP NuevoNimhe(void) {

    char line[LINE_LENGHT], *line_ptr;

    /* Read a line from stdin, store it on 'line' and point to that line using line_ptr */
    line_ptr = fgets(line, sizeof(line), stdin);

    if(line_ptr == NULL) {
        /* If this is the case, no data has been found in the file,
           therefore the program must be ended with an error message. */
        perror("Error en formato de entrada\n");
        exit(EXIT_FAILURE);
    }

    NimheP G = NULL;                            /* Create a new graph called G */
    G = calloc(1, sizeof(struct _NimheSt_t));   /* Allocate memory for G */

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

        u32 no_vertices, no_edges;
        sscanf(line_ptr, "%c %s %u %u", &p_letter, edge_word, &no_vertices, &no_edges);
        
        G->no_vertices = no_vertices;
        G->no_edges = no_edges;

        if(strcmp(edge_word, "edge")) {
            perror("Error en formato de entrada\n");
            exit(EXIT_FAILURE);
        } else {
            /* Allocate enough memory for the array of vertices real names */
            G->name_array = calloc(G->no_vertices, sizeof(u32));

            /* Allocate enough memory for the array of colors of vertices */
            G->color_array = calloc(G->no_vertices, sizeof(u32));

            /* Allocate enough memory for the array of degrees of vertices */
            G->degree_array = calloc(G->no_vertices, sizeof(u32));

            /* Allocate enough memory for the array of RAR order of vertices */
            G->RAR_order_array = calloc(G->no_vertices, sizeof(u32));

            /* Allocate enough memory to store all lists of vertex neighbors */
            G->neighbors_array = calloc(G->no_vertices, sizeof(Vector));

            /* Allocate enough memory to store current order */
            G->order = calloc(G->no_vertices, sizeof(u32));

            /* Allocate enough memory to store natural order */
            G->natural_order = calloc(G->no_vertices, sizeof(u32));

            /* Allocate memory for the array to store number of vertices colored with each color */
            G->vertices_with_color = calloc((G->no_vertices + 1), sizeof(u32));

        }
    } else {
        perror("Error en formato de entrada\n");
        exit(EXIT_FAILURE);
    }

    /* Array of bools to check during graph load if there is a vertex in the given position */
    bool *v_loaded;
    v_loaded = calloc(G->no_vertices, sizeof(bool));

    /* Variable used to check if the following lines are exactly G->edges */
    u32 lines_counter = G->no_edges;

    /* Get another line */
    line_ptr = fgets(line, sizeof(line), stdin);

    while(line_ptr && lines_counter) {
        /* there is an edge in this line to load to G */

        if(!strncmp(line_ptr, "e ", 2)) {

            /* Scan line parameters into different tokens */
            sscanf(line_ptr, "%c %u %u", &e_letter, &fst_vertex, &snd_vertex);

            insert_edge(G, fst_vertex, snd_vertex, v_loaded);

        } else {
            perror("Error en formato de entrada\n");
            exit(EXIT_FAILURE);
        }
        --lines_counter;
        line_ptr = fgets(line, sizeof(line), stdin);
    }

    /* Free temporary array used during load */
    free(v_loaded);
    v_loaded = NULL;
    
    /* Allocate memory for the array of used colors to be used in Greedy coloring function */
    G->used = malloc((G->no_vertices + 1) * sizeof(bool));

    int OrdenNat(const void *elem1, const void *elem2) {

        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->name_array[*fst] > G->name_array[*snd]) return 1;
        if(G->name_array[*fst] < G->name_array[*snd]) return -1;
        return 0;
    }

    qsort(G->natural_order, G->no_vertices, sizeof(u32), &OrdenNat);

    return G;
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
            vector_free(&G->neighbors_array[i]);

        free(G->neighbors_array);
        G->neighbors_array = NULL;

        free(G->order);
        G->order = NULL;

        free(G->natural_order);
        G->natural_order = NULL;

        free(G->vertices_with_color);
        G->vertices_with_color = NULL;

        free(G->used);
        G->used = NULL;

        free(G);
        G = NULL;
    }

    return 1;
}
