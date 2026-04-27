#include "vector.h"

#include <stdio.h>

static Vector *create_vector()
{
    Vector *vector = calloc(1, sizeof(Vector));
    if (!vector)
    {
        return NULL;
    }
    return vector;
}

Vector *init_vector(size_t initial_capacity)
{
    Vector *vec = create_vector();
    if (!vec)
    {
        return NULL;
    }

    vec->data = calloc(initial_capacity, sizeof(int));
    if (!vec->data)
    {
        free(vec);
        return NULL;
    }

    vec->size = 0;
    vec->capacity = initial_capacity;
    return vec;
}

void push_back(Vector *vec, int value)
{
    if (vec->size >= vec->capacity)
    {
        size_t new_capacity = vec->capacity ? vec->capacity * 2 : 1;
        int *new_data = realloc(vec->data, new_capacity * sizeof(int));
        if (!new_data)
        {
            return;
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size++] = value;
}

void free_vector(Vector *vec)
{
    if (vec)
    {
        if (vec->data != NULL)
        {
            free(vec->data);
            vec->data = NULL;
            vec->size = 0;
            vec->capacity = 0;
        }
        free(vec);
    }
}

Vector *concat_vectors(Vector *vec1, Vector *vec2)
{
    if (!vec2)
    {
        return vec1;
    }
    if (!vec1)
    {
        return vec2;
    }
    
    Vector *result = init_vector(vec1->size + vec2->size);
    if (!result)
    {
        return NULL;
    }

    for (size_t i = 0; i < vec1->size; i++)
    {
        push_back(result, vec1->data[i]);
    }
    for (size_t i = 0; i < vec2->size; i++)
    {
        push_back(result, vec2->data[i]);
    }
    free_vector(vec1);
    free_vector(vec2);
    return result;
}

void print_vector(Vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        printf("%d ", vec->data[i]);
    }
    printf("\n");
}