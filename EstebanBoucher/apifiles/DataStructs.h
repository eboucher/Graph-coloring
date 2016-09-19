/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include "Types.h"

// #define VECTOR_INITIAL_CAPACITY 8   // EITHER NEEDS TO BE MOVED TO GRAPH_LOAD OR TO BE REMOVED !!
#define VECTOR_GROWTH_RATE 8

typedef struct _VerticeSt_t VerticeSt; /* Forward declaration of VerticeSt */

/* Define a vector type */

typedef struct _VectorSt_t {
    u32 capacity;     	/* total available slots */
    u32 size;         	/* slots used so far */
    u32 *data;          /* array of indices of neighbor vertices in vertices array */
} Vector;

/* Define a queue type */

 typedef struct _QueueSt_t {
    u32 capacity;     	/* total available slots */
    u32 front;			/* index of first element */
    u32 rear;			/* Index of last element */
    u32 *elements;      /* array of elements */
} Queue;

void vector_init(Vector *V);
/*
 * Initializes a vector struct. It sets size to 0, capacity to
 * VECTOR_INITIAL_CAPACITY and allocates an appropriate amount of memory
 * (vector->capacity * sizeof(VerticeSt)) for the underlying data array.
 */
 
void vector_append(Vector *V, u32 value);
/*
 * Appends the given value to the vector. If the underlying data array is full,
 * then calling this function should cause vector->data to expand to accept
 * this value. Increments vector->size.
 */

u32 vector_get(Vector *V, u32 index);
/*
 * Returns a value out of a vector at the given index. If the index is below 0
 * or greater than vector->size - 1, this function should complain about the 
 * index being out of bounds.
 */

void vector_free(Vector *V);
/*
 * Frees the memory allocated for the data array. We leave freeing of the
 * Vector struct itself to client code.
 */

Queue* Queue_init(u32 max_elems);
/*
 * Initializes a Queue struct. It sets both front and rear to 0, hence its
 * size is equal to 0, and allocates an appropriate amount of memory
 * ((max_elements) * sizeof(u32)) for the underlying circular array.
 */

void Dequeue(Queue *Q);
/*
 * Remove front element from Queue Q.
 */

u32 Queue_front(Queue *Q);
/*
 * Return the element which is at the front.
 */

void Enqueue(Queue *Q, u32 element);
/*
 * Insert element in rear side of Queue Q.
 */

bool Queue_is_empty(Queue *Q);
/*
 * Returns true if Queue Q is empty and false if there are elements on it.
 */

void Queue_free(Queue *Q);
/*
 * Frees the memory allocated for the elements array. Leaves freeing of the
 * Vector struct itself to client code.
 */

#endif
