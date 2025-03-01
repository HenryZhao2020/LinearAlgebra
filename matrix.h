// "matrix.h" provides the matrix structure and matrix operations.

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

extern const int max_rows;
extern const int max_cols;
extern const int max_table_size;

struct matrix {
  int rows;
  int cols;
  int table[10000];
};
// requires: 0 <= rows <= max_rows
//           0 <= cols <= max_cols

// is_matrix_valid(mat) produces true if mat is a valid matrix and false otherwise.
bool is_matrix_valid(const struct matrix *mat);

// print_matrix(mat) outputs mat in a 2D grid.
// requires: mat is a valid matrix.
// effects: produces output
void print_matrix(const struct matrix *mat);

// equal_matrix(m1, m2) produces true if m1 and m2 are equal and false otherwise.
// requires: m1 and m2 are valid matrices
bool equal_matrix(const struct matrix *m1, const struct matrix *m2);

#endif
