// "vector.h" provides the vector structure and vector operations.

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

extern const int max_vec_n;
extern const char *default_vec_name;

struct vector {
  int n;              // Dimension in Rn
  double comp[100];   // Components of a vector
  const char *name;   // Variable name
};
// requires: 0 <= n <= max_vec_n

// is_vec_valid(v) produces true if v is a valid vector and false otherwise.
bool is_vec_valid(const struct vector *v);

// is_vec_zero(v) produces true if v is a zero vector and false otherwise.
// requires: v is a valid vector
bool is_vec_zero(const struct vector *v);

// print_vec(v, tab) outputs v in a column.
// requires: v is a valid vector
// effects: produces output
void print_vec(const struct vector *v);

// equal_vec(u, v) produces true if u and v are equal and false otherwise.
// requires: u and v are valid vectors
bool equal_vec(const struct vector *u, const struct vector *v);

// vec_at(v, i) produces the i-th component of v.
// requires: v is a valid vector.
//           1 <= i <= v->n
double vec_at(const struct vector *v, const int i);

// vec_add(u, v) computes the addition of u and v.
// requires: u and v are valid vectors in the same Rn
struct vector vec_add(const struct vector *u, const struct vector *v);

// vec_scalar_mult(v, c) computes the scalar product of v and c.
// requires: v is a valid vector
struct vector vec_scalar_mult(const struct vector *v, const double c);

// dot_product(u, v) produces the dot product of u and v.
// requires: u and v are valid vectors in the same Rn
double dot_product(const struct vector *u, const struct vector *v);

// cross_product(u, v) produces the cross product of u and v.
// requires: u and v are valid vectors and both belong to R3
struct vector cross_product(const struct vector *u, const struct vector *v);

// vec_len(v) produces the length (norm) of v.
// requires: v is a valid vector
double vec_len(const struct vector *v);

// vec_angle(u, v) produces the angle between u and v in radians.
// requires: u and v are valid, non-zero vectors in the same Rn.
double vec_angle(const struct vector *u, const struct vector *v);

#endif
