#include "Matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Allocates memory for the matrix and initialize to zeros.
Matrix *create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        printf("ERROR: Invalid matrix dimensions (%d x %d)\n", rows, cols);
        return NULL;
    }
    // Allocated a matrix
    Matrix *mat = malloc(sizeof(Matrix));
    if (!mat) {
        printf("ERROR: Matrix failed to allocate\n");
        return NULL;
    }

    mat->rows = rows;
    mat->cols = cols;

    // Allocate memory for row pointers
    mat->data = malloc(rows * sizeof(double *));
    if (!mat->data) {
        free(mat);
        return NULL;
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        mat->data[i] = calloc(cols, sizeof(double));
        if (!mat->data[i]) {
            // Clean up if allocation fails mid-way
            for (int j = 0; j < i; j++) free(mat->data[j]);
            free(mat->data);
            free(mat);
            printf("ERROR: Matrix row %d failed to allocate\n", i);
            return NULL;
        }
    }

    return mat;
}

// Frees all memory associated with the matrix.
void free_matrix(Matrix *mat) {
    if (!mat) return;
    // Free all data values inside of matrix
    for (int i = 0; i < mat->rows; i++) free(mat->data[i]);
    // Then free data
    free(mat->data);
    // and finally matrix struct
    free(mat);
}

// Prints the matrix in a readable grid format
void print_matrix(const Matrix *mat, bool debug) {
    for (int i = 0; i < mat->rows; i++) {
        printf("| ");
        double *row =
            mat->data[i];  // adds a double to memory sure, but has FAR better readability.
        for (int j = 0; j < mat->cols; j++) {
            if (debug) {
                printf("row %i, col %i -> %6.2f", i, j, *(row + j));
            } else {
                printf("%6.2f", *(row + j));
            }
            printf(" | ");
        }
        printf("\n");
    }
}

// Sets a value at a specific row and column
int set_element(Matrix *mat, int row, int col, double value) {
    // Check for out-of-bounds
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("ERROR: out-of-bounds\n");
        return NAN;
    }

    mat->data[row][col] = value;

    return 0;
}

// Retrieves a value from a position
double get_element(const Matrix *mat, int row, int col) {
    // Check for out-of-bounds
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("ERROR: out-of-bounds\n");
        return NAN;
    }
    return mat->data[row][col];
}

// Returns a new matrix that's the sum of two matrices.
// If I understand properly, matrix addition is simply component-wise, therefore
// both matrices must have the same NxM dimensions in order for matrix addition
// to work.
Matrix *add_matrices(const Matrix *a, const Matrix *b) {
    // Check if matrix dimensions match otherwise we can't do matrix addition
    if (!(a->rows == b->rows && a->cols == b->cols)) {
        printf("ERROR: Incompatible matrices for add operation. Invalid dimensions.\n");
        return NULL;
    }

    // Creates new matrix to be returned
    Matrix *new_matrix = create_matrix(a->rows, a->cols);

    // Sums of matrices A and B are copied over to new_matrix.
    for (int i = 0; i < new_matrix->rows; i++)
        for (int j = 0; j < new_matrix->cols; j++)
            new_matrix->data[i][j] = a->data[i][j] + b->data[i][j];

    return new_matrix;
}

// Multiplies two matrices together using matrix multiplication
// naive approach
Matrix *multiply_matrices(const Matrix *a, const Matrix *b) {
    // Check if matrix-matrix multiplication is even possible given the passed matrices.
    if (!(a->cols == b->rows)) {
        printf("ERROR: Invalid dimensions for matrix-matrix multiplication\n");
        printf("Matrix A's columns count (%d) must match matrix B's row count (%d)\n", a->cols,
               b->rows);
        return NULL;
    }

    // Create matrix and pass a->rows and b->cols to it. An m x p matrix.
    Matrix *result_matrix = create_matrix(a->rows, b->cols);

    // ==== Now to multiply and set the matrix properly ====
    for (int i = 0; i < result_matrix->rows; i++) {
        for (int j = 0; j < result_matrix->cols; j++) {
            // resets sum
            double sum = 0;
            // sums all of the rows and columns to be added to result_matrix[i][j]
            // taking what I believe to be the dot product.
            for (int k = 0; k < a->cols; k++) {
                sum += ((a->data[i][k]) * (b->data[k][j]));
            }
            // results in the dot product with a->data[i][k] and b->data[k][j]
            result_matrix->data[i][j] = sum;
        }
    }

    return result_matrix;
}
