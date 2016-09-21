/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "Cthulhu.h"

/* GRAPH CONSTRUCTION AND DESTRUCTION FUNCTIONS */

NimheP NuevoNimhe(void) {

    char line[LINE_LENGHT], *line_ptr;
    /* Read a line from stdin, store it on 'line' and point to that line
       using line_ptr */
    line_ptr = fgets(line, sizeof(line), stdin);
    /* Check if there is data in the file */
    if(line_ptr == NULL) {
        /* No data has been found in the file, return a pointer to NULL
            and let main function notify the error */
        return NULL;
    }
    /* Ignore comment lines */
    while(!strncmp(line_ptr, "c", 1)) {
        /* Loop until no more comment lines are found */
        line_ptr = fgets(line, sizeof(line), stdin);
    }


    /* Variables to check that the file format is correct */
    char edge_word[4] = "\0";
    char p_letter, e_letter;

    /* Create a new graph called G */
    NimheP G = NULL;
    /* Allocate memory for G */
    G = calloc(1, sizeof(struct _NimheSt_t));

    /* Next line must be indicate the number of vertices and edges of 
       the new graph */
    if(!strncmp(line_ptr, "p ", 2)) {

        /* Number of vertices and edges are expected to follow */

        u32 no_vertices, no_edges;

        sscanf(line_ptr, "%c %s %u %u", &p_letter,
               edge_word, &no_vertices, &no_edges);
        
        G->no_vertices = no_vertices;
        G->no_edges = no_edges;

        if(strcmp(edge_word, "edge")) {
            /* Line expected to indicate number of vertices and edges does not
               start with 'edge', wrong format. Return a pointer to NULL and 
               let main function notify the error. */
            return NULL;

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

            /* Allocate memory for the array to store number of vertices
               colored with each color */
            G->vertices_with_color = calloc((G->no_vertices + 1), sizeof(u32));
        }
    } else {
        /* Next line after a comment line does not start with 'p'. Return a
           pointer to NULL and let main function notify the error. */
        return NULL;
    }

    /* Variables used to temporally store vertices of an edge */
    u32 fst_vertex, snd_vertex;

    /* Array of bools to check during graph load if there is a vertex in the
       given position */
    bool *v_loaded;
    v_loaded = calloc(G->no_vertices, sizeof(bool));

    /* Variable used to check if the following lines are exactly G->no_edges */
    u32 lines_counter = G->no_edges;

    /* Get another line */
    line_ptr = fgets(line, sizeof(line), stdin);

    while(line_ptr && lines_counter) {
        /* there is an edge in this line to load to G */

        if(!strncmp(line_ptr, "e ", 2)) {

            /* Scan line parameters into different tokens */
            sscanf(line_ptr, "%c %u %u", &e_letter, &fst_vertex, &snd_vertex);
            
            /* Insert edge with copied values */
            insert_edge(G, fst_vertex, snd_vertex, v_loaded);

            if(G->vertices_checker > G->no_vertices) {
                /* There are extra vertices in input file */
                /* Free temporary array used during load */
                free(v_loaded);
                v_loaded = NULL;

                /* Free allocated memory for the graph */
                DestruirNimhe(G);

                /* Return a pointer to NULL and let main function notify
                   the error */
                return NULL;
            }

        } else {
            /* Line expected to store an edge does not start with 'e' */
            /* Free temporary array used during load */
            free(v_loaded);
            v_loaded = NULL;

            /* Free allocated memory for the graph */
            DestruirNimhe(G);
            
            /* Return a pointer to NULL and let main function notify the
               error */
            return NULL;
        }
        --lines_counter;
        line_ptr = fgets(line, sizeof(line), stdin);
    }

    /* Free temporary array used during load */
    free(v_loaded);
    v_loaded = NULL;
    
    /* Allocate memory for the array of used colors to be used in Greedy coloring function */
    G->used = malloc((G->no_vertices + 1) * sizeof(bool));

    /* Declare a local comparison function */
    int OrdenNat(const void *elem1, const void *elem2) {
        /* Cast the two input values to pointers to u32 */
        u32 *fst = (u32*)elem1;
        u32 *snd = (u32*)elem2;
        if(G->name_array[*fst] > G->name_array[*snd]) return 1;
        if(G->name_array[*fst] < G->name_array[*snd]) return -1;
        return 0;
    }
    /* Order graph vertices according to the declared comparison function */
    qsort(G->natural_order, G->no_vertices, sizeof(u32), &OrdenNat);
    /* Return newly loaded graph */
    return G;
}

int DestruirNimhe(NimheP G) {
    
    if(G != NULL) {
        /* Free array of graph vertex names */
        free(G->name_array);
        G->name_array = NULL;
        /* Free array of colors of vertices */
        free(G->color_array);
        G->color_array = NULL;
        /* Free array of degrees of vertices */
        free(G->degree_array);
        G->degree_array = NULL;
        /* Free array of values used for RAR order */
        free(G->RAR_order_array);
        G->RAR_order_array = NULL;
        /* Free each list of neighbors in neighbors array */
        for(u32 i = 0; i < G->no_vertices; i++)
            vector_free(&G->neighbors_array[i]);
        /* Free neighbors array */
        free(G->neighbors_array);
        G->neighbors_array = NULL;
        /* Free order array */
        free(G->order);
        G->order = NULL;
        /* Free natural order array */
        free(G->natural_order);
        G->natural_order = NULL;
        /* Free vertices_with_color array */
        free(G->vertices_with_color);
        G->vertices_with_color = NULL;
        /* Free array of used items */
        free(G->used);
        G->used = NULL;
        /* Free pointer to NimheSt */
        free(G);
        G = NULL;
    }

    return 1;
}
