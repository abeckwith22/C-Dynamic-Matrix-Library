#include <stdio.h>

#include "Matrix.h"

int main(int argc, char **argv) {
    Matrix *my_mat = create_matrix(4, 4);

    // Before setting matrix
    // Original matrix
    print_matrix(my_mat, false);

    // After setting matrix
    printf("---------- AFTER SETTING MATRIX -----------\n");

    // transformed matrix
    set_element(my_mat, 0, 0, 4.0f);
    set_element(my_mat, 1, 1, 9.3f);

    print_matrix(my_mat, false);

    // Getting matrix entry
    double entry = get_element(my_mat, 1, 1);
    printf("Matrix entry @ (1, 1) -> %f\n", entry);

    // Component-wise adding two matrices
    printf("---------- ADDING -----------\n");

    Matrix *m1 = create_matrix(3, 3);
    Matrix *m2 = create_matrix(3, 3);

    printf("---------- m1 -----------\n");

    set_element(m1, 0, 0, 1.0f);
    set_element(m1, 1, 1, 1.0f);
    set_element(m1, 2, 2, 1.0f);

    print_matrix(m1, false);

    printf("---------- m2 -----------\n");
    set_element(m2, 0, 0, 1.0f);
    set_element(m2, 1, 1, 1.0f);
    set_element(m2, 2, 2, 1.0f);

    print_matrix(m2, false);

    printf("---------- m3 -----------\n");

    Matrix *m3 = add_matrices(m1, m2);

    print_matrix(m3, false);

    printf("---------- and now a 4x4 matrix-----------\n");
    Matrix *m4 = create_matrix(4, 4);
    print_matrix(m4, true);

    // Free matrix resources
    free_matrix(my_mat);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m3);
    free_matrix(m4);

    return 0;
}