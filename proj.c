#include "proj.h"
#include "vector.h"

#include <assert.h>
#include <stdio.h>

struct vector projv(const struct vector *u, const struct vector *v) {
  assert(is_vec_valid(u));
  assert(is_vec_valid(v));
  assert(u->n == v->n);
  assert(!is_vec_zero(v));

  double len = vec_len(v);
  double coeff = (dot_product(u, v) / (len * len));

  return vec_scalar_mult(v, coeff);
}
