#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct
{
    int *data; // Tableau dynamique pour stocker les éléments
    size_t size; // Nombre d'éléments actuellement stockés
    size_t capacity; // Capacité totale du tableau
} Vector;

Vector *init_vector(size_t initial_capacity);

void push_back(Vector *vec, int value);

void free_vector(Vector *vec);

void print_vector(Vector *vec);

#endif /* !VECTOR_H */