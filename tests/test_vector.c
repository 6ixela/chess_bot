#include <criterion/criterion.h>

#include "vector.h"

Test(init_vec, test_vec) {
    Vector *vector = init_vector(8);
    cr_assert_eq(vector->capacity, 8, "Expected %s\nbut got %s", vector->capacity, 8);
    cr_assert_eq(vector->size, 0, "Expected %s\nbut got %s", vector->size, 0);
    free_vector(vector);
}

Test(push_2els_vec, test_vec) {
    Vector *vector = init_vector(8);
    push_back(vector, 1);
    push_back(vector, 2);
    cr_assert_eq(vector->data[0], 1, "Expected %s\nbut got %s", vector->data[0], 1);
    cr_assert_eq(vector->data[1], 2, "Expected %s\nbut got %s", vector->data[1], 2);
    free_vector(vector);
}

Test(push_max_size_vec, test_vec) {
    Vector *vector = init_vector(2);
    push_back(vector, 1);
    push_back(vector, 2);
    cr_assert_eq(vector->data[0], 1, "Expected %s\nbut got %s", vector->data[0], 1);
    cr_assert_eq(vector->data[1], 2, "Expected %s\nbut got %s", vector->data[1], 2);
    cr_assert_eq(vector->capacity, 2, "Expected %s\nbut got %s", vector->capacity, 2);
    cr_assert_eq(vector->size, 2, "Expected %s\nbut got %s", vector->size, 2);
    free_vector(vector);
}

Test(push_over_size_vec1, test_vec) {
    Vector *vector = init_vector(2);
    push_back(vector, 1);
    push_back(vector, 2);
    cr_assert_eq(vector->data[0], 1, "Expected %s\nbut got %s", vector->data[0], 1);
    cr_assert_eq(vector->data[1], 2, "Expected %s\nbut got %s", vector->data[1], 2);
    cr_assert_eq(vector->capacity, 2, "Expected %s\nbut got %s", vector->capacity, 2);
    cr_assert_eq(vector->size, 2, "Expected %s\nbut got %s", vector->size, 2);
    push_back(vector, 3);
    push_back(vector, 4);
    cr_assert_eq(vector->data[2], 3, "Expected %s\nbut got %s", vector->data[2], 3);
    cr_assert_eq(vector->data[3], 4, "Expected %s\nbut got %s", vector->data[3], 4);
    cr_assert_eq(vector->capacity, 4, "Expected %s\nbut got %s", vector->capacity, 4);
    cr_assert_eq(vector->size, 4, "Expected %s\nbut got %s", vector->size, 4);
    free_vector(vector);
}

Test(push_over_size_vec2, test_vec) {
    Vector *vector = init_vector(2);
    push_back(vector, 1);
    push_back(vector, 2);
    push_back(vector, 3);
    push_back(vector, 4);
    push_back(vector, 5);
    cr_assert_eq(vector->data[4], 5, "Expected %s\nbut got %s", vector->data[4], 5);
    cr_assert_eq(vector->capacity, 8, "Expected %s\nbut got %s", vector->capacity, 8);
    cr_assert_eq(vector->size, 5, "Expected %s\nbut got %s", vector->size, 5);
    free_vector(vector);
}

Test(concat_vec, test_vec) {
    Vector *vector1 = init_vector(2);
    Vector *vector2 = init_vector(2);
    push_back(vector1, 1);
    push_back(vector1, 2);
    push_back(vector2, 3);
    push_back(vector2, 4);
    push_back(vector2, 5);
    Vector *vector = concat_vectors(vector1, vector2);
    cr_assert_eq(vector->data[4], 5, "Expected %s\nbut got %s", vector->data[4], 5);
    cr_assert_eq(vector->capacity, 5, "Expected %s\nbut got %s", vector->capacity, 8);
    cr_assert_eq(vector->size, 5, "Expected %s\nbut got %s", vector->size, 5);
    print_vector(vector);
    free_vector(vector);
}

Test(concat_vec1, test_vec) {
    Vector *vector1 = init_vector(2);
    push_back(vector1, 1);
    push_back(vector1, 2);
    Vector *vector = concat_vectors(vector1, NULL);
    cr_assert_eq(vector->data[1], 2, "Expected %s\nbut got %s", vector->data[4], 5);
    cr_assert_eq(vector->capacity, 2, "Expected %s\nbut got %s", vector->capacity, 8);
    cr_assert_eq(vector->size, 2, "Expected %s\nbut got %s", vector->size, 5);
    free_vector(vector);
}

Test(concat_vec2, test_vec) {
    Vector *vector1 = init_vector(2);
    push_back(vector1, 1);
    push_back(vector1, 2);
    Vector *vector = concat_vectors(NULL, vector1);
    cr_assert_eq(vector->data[1], 2, "Expected %s\nbut got %s", vector->data[4], 5);
    cr_assert_eq(vector->capacity, 2, "Expected %s\nbut got %s", vector->capacity, 8);
    cr_assert_eq(vector->size, 2, "Expected %s\nbut got %s", vector->size, 5);
    free_vector(vector);
}