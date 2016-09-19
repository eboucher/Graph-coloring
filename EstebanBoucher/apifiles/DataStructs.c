/*
    PROYECTO MATEMATICA DISCRETA II 2016
    Boucher Esteban - eboucher7@gmail.com
    FaMAF - UNC
*/

#include "DataStructs.h"

void vector_init(Vector *V) {
    /* initialize size and capacity */
    V->size = 0;
    V->capacity = VECTOR_INITIAL_CAPACITY;

    /* allocate memory for V.data */
    V->data = malloc(V->capacity * sizeof(u32));
}

void vector_append(Vector *V, u32 value) {
    /* make sure there's room to expand into */
    if (V->size >= V->capacity) {
    /* double V.capacity and resize the allocated memory accordingly */
    V->capacity += VECTOR_GROWTH_RATE;
    V->data = realloc(V->data, V->capacity * sizeof(u32));
    }
    /* append the value and increment V->size */
    V->data[V->size++] = value;
}

u32 vector_get(Vector *V, u32 index) {
    if (index >= V->size) {
        printf("Index %d out of bounds for vector of size %d\n", index, V->size);
        exit(EXIT_FAILURE);
    }
    return V->data[index];
}

void vector_free(Vector *V) {
    free(V->data);
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
    free(Q);
    Q = NULL;
}
