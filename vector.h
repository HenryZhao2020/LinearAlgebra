// "vector.h" provides the vector structure and vector operations.

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Limits on the dimension of a vector
extern const int min_n;
extern const int max_n;

struct vector {
  int n;           // Dimension in Rn, n <= 100
  int comp[100];   // Components of a vector
};
// requires: min_n <= n <= max_n

// is_vec_valid(vec) produces true if vec is a valid vector and false otherwise.
bool is_vec_valid(const struct vector *vec);

// print_vec(vec) outputs vec in a column and returns the width of the column.
// requires: vec is a valid vector
// effects: produces output
int print_vec(const struct vector *vec);

// equal_vec(v1, v2) produces true if v1 and v2 are equal and false otherwise.
// requires: v1 and v2 are valid vectors
bool equal_vec(const struct vector *v1, const struct vector *v2);

// vec_at(vec, i) produces the i-th component of vec.
// requires: vec is a valid vector.
//           1 <= i <= vec->n
int vec_at(const struct vector *vec, int i);

// vec_add(v1, v2) computes the addition of v1 and v2.
// requires: v1 and v2 are valid vectors
//           v1 and v2 belong to the same Rn
struct vector vec_add(const struct vector *v1, const struct vector *v2);

// vec_scalar_mult(vec, c) computes the scalar multiplication of vec and c.
// requires: vec is a valid vector
struct vector vec_scalar_mult(const struct vector *vec, int c);

// dot_product(v1, v2) produces the dot product of v1 and v2.
// requires: v1 and v2 are valid vectors and belong to the same Rn
int dot_product(const struct vector *v1, const struct vector *v2);

// cross_product(v1, v2) produces the cross product of v1 and v2.
// requires: v1 and v2 are valid vectors and both belong to R3
struct vector cross_product(const struct vector *v1, const struct vector *v2);

// vec_len(vec) produces the length (norm) of vec.
// requires: vec is a valid vector
int vec_len(const struct vector *vec);

#endif
