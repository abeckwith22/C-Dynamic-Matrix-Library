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

    printf("---------- m1+m2=m3 -----------\n");

    Matrix *m3 = add_matrices(m1, m2);

    print_matrix(m3, false);

    printf("---------- and now a 4x4 matrix-----------\n");
    Matrix *m4 = create_matrix(4, 4);
    print_matrix(m4, true);

    printf("---------- MATRIX MULTIPLICATION -----------\n");

    // Simple 2x2 matrices
    Matrix *mult_m1 = create_matrix(2, 2);
    Matrix *mult_m2 = create_matrix(2, 2);

    // set elements for matrix 1
    set_element(mult_m1, 0, 0, 1.0f);
    set_element(mult_m1, 0, 1, 2.0f);
    set_element(mult_m1, 1, 0, 3.0f);
    set_element(mult_m1, 1, 1, 4.0f);

    // Set elements for matrix 2
    set_element(mult_m2, 0, 0, 5.0f);
    set_element(mult_m2, 0, 1, 6.0f);
    set_element(mult_m2, 1, 0, 7.0f);
    set_element(mult_m2, 1, 1, 8.0f);

    printf("---------- M1 MULTIPLICATION -----------\n");
    print_matrix(mult_m1, false);
    printf("---------- M2 MULTIPLICATION -----------\n");
    print_matrix(mult_m2, false);
    printf("---------- M3 (m1 x m2) MULTIPLICATION -----------\n");
    Matrix *mult_result = multiply_matrices(mult_m1, mult_m2);
    print_matrix(mult_result, false);

    // Free all allocated matrix resources
    free_matrix(my_mat);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m3);
    free_matrix(m4);
    free_matrix(mult_m1);
    free_matrix(mult_m2);
    free_matrix(mult_result);

    return 0;
}