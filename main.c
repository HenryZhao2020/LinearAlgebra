#include "vector.h"

#include <stdio.h>

int main(void) {
  struct vector v1 = {3, {1, 2, 3}};
  struct vector prod = vec_scalar_mult(&v1, -3);
  print_vec(&prod);
}
