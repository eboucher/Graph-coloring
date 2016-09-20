/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include "Types.h"

void vector_init(Vector *V);
/*
 * Initializes a vector struct. It sets size to 0, capacity to
 * VECTOR_INITIAL_CAPACITY and allocates an appropriate amount of memory
 * (vector->capacity * sizeof(u32)) for the underlying data array.
 */
 
void vector_append(Vector *V, u32 value);
/*
 * Appends the given value to the vector. If the underlying data array is full,
 * then calling this function should cause vector->data to expand to accept
 * this value. Increments vector->size.
 */

void vector_free(Vector *V);
/*
 * Frees the memory allocated for the data array. Freeing of the Vector
 * struct is left itself to client code, which in this program it is the
 * Cthulhu module.
 */

Queue* Queue_init(u32 max_elems);
/* 
 * Queue_init takes argument the maximum number of elements the Queue can
 * hold, creates a Queue according to it and returns a pointer to the Queue.
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
 * Frees the memory allocated for the elements array.
 */

#endif
