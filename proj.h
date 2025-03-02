// "proj.h" provides functions that compute the projection and 
//   perpendicular of vectors or planes.

#ifndef PROJ_H
#define PROJ_H

struct vector;

// projv(u, v) produces the projection of u onto v.
// requires: u and v are valid vectors in the same Rn
//           v is not a zero vector
struct vector projv(const struct vector *u, const struct vector *v);

// perpv(u, v) produces the perpendicular of u onto v.
// requires: u and v are valid vectors in the same Rn
//           v is not a zero vector
struct vector perpv(const struct vector *u, const struct vector *v);

// projp(x, n) produces the projection of x onto a plane with the normal vector n.
// requires: x and n are valid vectors in the same Rn
//           x is not a zero vector
struct vector projp(const struct vector *x, const struct vector *n);

// perpp(x, n) produces the perpendicular of x onto a plane with the normal vector n.
// requires: x and n are valid vectors in the same Rn
//           x is not a zero vector
struct vector perpp(const struct vector *x, const struct vector *n);

#endif
