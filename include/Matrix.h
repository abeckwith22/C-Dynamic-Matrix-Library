#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// A struct for a basic implementation of a (m x n) matrix.
// Contains:
//
//      int      rows           - Number of rows
//
//      int      cols           - Number of columns
//
//      double **data           - Matrix data
//
typedef struct {
    int rows;
    int cols;
    double **data;  // pointer to an array of row pointers
} Matrix;

// Allocates memory for the matrix and initialize to zeros.
Matrix *create_matrix(int rows, int cols);

// Frees all memory associated with the matrix.
void free_matrix(Matrix *mat);

// Prints the matrix in a readable grid format
void print_matrix(const Matrix *mat, bool debug);

// Sets a value at a specific row and column
int set_element(Matrix *mat, int row, int col, double value);

// Retrieves a value from a position
double get_element(const Matrix *mat, int row, int col);

// Returns a new matrix that's the sum of two matrices
Matrix *add_matrices(const Matrix *a, const Matrix *b);

// Multiplies two matrices together using matrix multiplication
Matrix *multiply_matrices(const Matrix *a, const Matrix *b);

#endif
