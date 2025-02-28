#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

extern const int min_n;
extern const int max_n;

struct vector {
  int n;           // Dimension in Rn, n <= 100
  int comp[100];   // Components of a vector
};

// print_vec(vec) outputs vec in a column.
// requires: vec is a valid vector
// effects: produces output
void print_vec(const struct vector *vec);


// equal_vec(v1, v2) produces true if v1 and v2 are equal and false otherwise.
// requires: v1 and v2 are valid vectors
bool equal_vec(const struct vector *v1, const struct vector *v2);

// vec_add(v1, v2) computes the addition of v1 and v2.
// requires: v1 and v2 are valid vectors
//           v1 and v2 belong to the same Rn
struct vector vec_add(const struct vector *v1, const struct vector *v2);

// vec_scalar_mult(vec, k) computes the scalar multiplication of vec and k.
// requires: vec is a valid vector
struct vector vec_scalar_mult(const struct vector *vec, const int k);

#endif
