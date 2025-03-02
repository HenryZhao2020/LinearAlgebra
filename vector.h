// "vector.h" provides the vector structure and vector operations.

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Upper limit on the dimension of a vector
extern const int max_n;

struct vector {
  int n;              // Dimension in Rn
  double comp[100];   // Components of a vector
  char *name;         // Variable name
};
// requires: 0 <= n <= max_n

// is_vec_valid(vec) produces true if vec is a valid vector and false otherwise.
bool is_vec_valid(const struct vector *vec);

// is_vec_zero(vec) produces true if vec is a zero vector and false otherwise.
// requires: vec is a valid vector
bool is_vec_zero(const struct vector *vec);

// print_vec(vec, tab) outputs vec in a column and returns the width of the column.
//   A tab character will be printed before the column if tab is true.
// requires: vec is a valid vector
// effects: produces output
int print_vec(const struct vector *vec, bool tab);

// equal_vec(v1, v2) produces true if v1 and v2 are equal and false otherwise.
// requires: v1 and v2 are valid vectors
bool equal_vec(const struct vector *v1, const struct vector *v2);

// vec_at(vec, i) produces the i-th component of vec.
// requires: vec is a valid vector.
//           1 <= i <= vec->n
double vec_at(const struct vector *vec, int i);

// vec_add(v1, v2) computes the addition of v1 and v2.
// requires: v1 and v2 are valid vectors
//           v1 and v2 belong to the same Rn
struct vector vec_add(const struct vector *v1, const struct vector *v2);

// vec_scalar_mult(vec, c) computes the scalar multiplication of vec and c.
// requires: vec is a valid vector
struct vector vec_scalar_mult(const struct vector *vec, double c);

// dot_product(v1, v2) produces the dot product of v1 and v2.
// requires: v1 and v2 are valid vectors and belong to the same Rn
double dot_product(const struct vector *v1, const struct vector *v2);

// cross_product(v1, v2) produces the cross product of v1 and v2.
// requires: v1 and v2 are valid vectors and both belong to R3
struct vector cross_product(const struct vector *v1, const struct vector *v2);

// vec_len(vec) produces the length (norm) of vec.
// requires: vec is a valid vector
double vec_len(const struct vector *vec);

// vec_angle(v1, v2) produces the angle between v1 and v2 in radians.
// requires: v1 and v2 are valid, non-zero vectors in the same Rn.
double vec_angle(const struct vector *v1, const struct vector *v2);

#endif
