// "matrix.h" provides the matrix structure and matrix operations.

#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

extern const int max_rows;
extern const int max_cols;
extern const int max_table_len;

struct vector;

struct matrix {
  int num_rows;
  int num_cols;
  double table[10000];
};
// requires: 0 <= num_rows <= max_rows
//           0 <= num_cols <= max_cols

// is_mat_valid(A) produces true if A is a valid matrix and false otherwise.
bool is_mat_valid(const struct matrix *A);

// is_mat_zero(A) produces true if A is a zero matrix and false otherwise.
// requires: A is a valid matrix
bool is_mat_zero(const struct matrix *A);

// print_mat(A, tab) outputs A in an mxn grid, where m is the height of A,
//   and n is the width of A.
//   A tab character will be printed before the column if tab is true.
// requires: A is a valid matrix
// effects: produces output
void print_mat(const struct matrix *A, const bool tab);

// equal_mat(A, B) produces true if A and B are equal and false otherwise.
// requires: A and B are valid matrices
bool equal_mat(const struct matrix *A, const struct matrix *B);

// mat_add(A, B) produces the sum of A and B.
// requires: A and B are valid matrices with equal width and height
struct matrix mat_add(const struct matrix *A, const struct matrix *B);

// mat_smult(A, c) produces the scalar product of A and c.
// requires: A is a valid matrix
struct matrix mat_smult(const struct matrix *A, const double c);

// mat_vec_mult(A, v) produces the matrix-vector product of A and v.
// requires: A is a valid matrix
//           v is a valid vector
//           the width of A is equal to the dimension of v
struct matrix mat_vec_mult(const struct matrix *A, const struct vector *v);

// mat_mult(A, B) produces the product of A and B.
// requires: A and B are valid matrices
//           the width of A is equal to the height of B
struct matrix mat_mult(const struct matrix *A, const struct matrix *B);

// mat_transpose(A) produces the transpose of A.
// requires: A is a valid matrix
struct matrix mat_transpose(const struct matrix *A);

// mat_identity(A) produces the identity matrix of A.
// requires: A is a valid square matrix
struct matrix mat_identity(const struct matrix *A);

#endif
