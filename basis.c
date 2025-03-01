#include "basis.h"
#include "matrix.h"

struct matrix std_basis(int n) {
  struct matrix basis = {n, n, {0}};
  for (int i = 0; i < n; ++i) {
    basis.table[i * n + i] = 1;
  }
  return basis;
}
