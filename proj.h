// "proj.h" provides functions that compute the projection and 
//   perpendicular of vectors or planes.

#ifndef PROJ_H
#define PROJ_H

struct vector;

// projv(u, v) produces the projection of u onto v.
// requires: u and v are valid vectors in the same Rn
//           v is not a zero vector
struct vector projv(const struct vector *u, const struct vector *v);

#endif
