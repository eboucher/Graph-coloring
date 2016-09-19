/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "DataStructs.h"

void vector_init(Vector *vector) {
    /* initialize size and capacity */
    vector->size = 0;
    vector->capacity = VECTOR_INITIAL_CAPACITY;

    /* allocate memory for vector.data */
    vector->data = malloc(vector->capacity * sizeof(u32));
}

void vector_append(Vector *vector, u32 value) {
    /* make sure there's room to expand into */
    if (vector->size >= vector->capacity) {
    /* double vector.capacity and resize the allocated memory accordingly */
    vector->capacity += VECTOR_GROWTH_RATE;
    vector->data = realloc(vector->data, vector->capacity * sizeof(u32));
    }
    /* append the value and increment vector->size */
    vector->data[vector->size++] = value;
}

u32 vector_get(Vector *vector, u32 index) {
    if (index >= vector->size) {
        printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
        exit(EXIT_FAILURE);
    }
    return vector->data[index];
}

void vector_free(Vector *vector) {
    free(vector->data);
}

/* Crate_queue function takes argument the maximum number of elements the Queue can hold, creates
   a Queue according to it and returns a pointer to the Queue. */

Queue* Queue_init(u32 max_elements) {

    Queue *Q;
    Q = (Queue *)malloc(sizeof(Queue));

    /* Initialize its properties */
    Q->elements = malloc((max_elements) * sizeof(u32));
    Q->capacity = max_elements;
    Q->front = 0;
    Q->rear = 0;

    return Q;
}

void Dequeue(Queue *Q) {

    /* Removing an element is equivalent to incrementing index of front by one,
       as we fill elements in circular fashion */
    Q->front = (Q->front + 1) % Q->capacity;
}

u32 Queue_front(Queue *Q) {
    /* Return the element which is at the front */
    return Q->elements[Q->front];
}

void Enqueue(Queue *Q, u32 element) {

    /* Insert the element in its rear side */ 
    Q->elements[Q->rear] = element;
    /* As we fill the queue in circular fashion */
    Q->rear = (Q->rear + 1) % Q->capacity;
}

bool Queue_is_empty(Queue *Q) {
    return (Q->front == Q->rear ? true : false);
}

void Queue_free(Queue *Q) {
    free(Q->elements);
}
