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

    /* allocate memory for the underlying data */
    V->data = malloc(V->capacity * sizeof(u32));
}

void vector_append(Vector *V, u32 value) {
    /* make sure there's room to expand into */
    if (V->size >= V->capacity) {
    /* double V->capacity and resize the allocated memory accordingly */
    V->capacity += VECTOR_GROWTH_RATE;
    V->data = realloc(V->data, V->capacity * sizeof(u32));
    }
    /* append the value and increment V->size */
    V->data[V->size++] = value;
}

void vector_free(Vector *V) {
    /* Free its array of data */
    free(V->data);
}

/* Initializes a Queue struct */
Queue* Queue_init(u32 max_elements) {
    /* Create a pointer to a Queue */
    Queue *Q;
    /* And allocate memory to point to it */
    Q = (Queue *)malloc(sizeof(Queue));
    /* Allocate memory for the underlying circular array */
    Q->elements = malloc((max_elements) * sizeof(u32));
    /* And initialize its properties */
    Q->capacity = max_elements;
    /* Set both front and rear to 0, hence its size is 0 */
    Q->front = 0;
    Q->rear = 0;
    /* Return the pointer to Q */
    return Q;
}

void Dequeue(Queue *Q) {
    /* Removing an element is equivalent to incrementing index of front
       by one, as we fill elements in circular fashion */
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
    /* The Queue is empty when its front and rear are equal */
    return (Q->front == Q->rear ? true : false);
}

void Queue_free(Queue *Q) {
    /* Free array of elements in Queue */
    free(Q->elements);
    /* Free the Queue */
    free(Q);
    Q = NULL;
}
