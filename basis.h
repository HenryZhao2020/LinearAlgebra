// "basis.h" provides functions about the basis for a set of vectors.

#ifndef BASIS_H
#define BASIS_H

struct matrix;

// std_basis(n) produces the standard basis for Rn.
// requires: n >= 0 
struct matrix std_basis(int n);

#endif
