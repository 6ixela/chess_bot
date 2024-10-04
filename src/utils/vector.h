#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Vector;

Vector *init_vector(size_t initial_capacity);

void push_back(Vector *vec, int value);

void free_vector(Vector *vec);

void print_vector(Vector *vec);

Vector *concat_vectors(Vector *vec1, Vector *vec2);

#endif /* !VECTOR_H */