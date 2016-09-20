/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef uint32_t u32;

#define VECTOR_INITIAL_CAPACITY 8
#define VECTOR_GROWTH_RATE 8

typedef struct _VerticeSt_t {
    u32 name;         /* Real name of vertex */
    u32 degree;       /* Vertex degree */
    u32 color;        /* Vertex color */
    u32 index;        /* Index of vertex in Nimhe array of vertices */
} VerticeSt;

typedef struct _VectorSt_t {
    u32 capacity;       /* total available slots */
    u32 size;           /* slots used so far */
    u32 *data;          /* array of indices of neighbor vertices in vertices array */
} Vector;

typedef struct _NimheSt_t {
    u32 no_vertices;            /* Number of vertices */
    u32 no_edges;               /* Number of edges */
    u32 coloring;               /* Graph coloring so far */
    u32 *name_array;            /* Array of graph vertex names */
    u32 *color_array;           /* Array of colors of vertices */
    u32 *degree_array;          /* Array of degrees of vertices */
    u32 *RAR_order_array;       /* Array of values used for RAR order for each vertex */
    Vector *neighbors_array;    /* Array of lists of neighbors related to each vertex */
    u32 *order;                 /* Coloring order */
    u32 *natural_order;         /* Natural order */
    u32 *vertices_with_color;   /* Array to store number of vertices colored with each color */
    bool *used;                 /* Array to be used in Greedy function and OrdenEspecifico */
} *NimheP;

typedef struct _QueueSt_t {
    u32 capacity;       /* total available slots */
    u32 front;          /* index of first element */
    u32 rear;           /* Index of last element */
    u32 *elements;      /* array of elements */
} Queue;

#endif
