// "command.h" implements commands that prompt users to define the necessary 
//   variables, then perform the corresponding linear algebra operations. 
//   All functions return true if the operations succeed and false otherwise.

#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

// exec_vadd() performs addition of vectors.
// effects: reads input, produces output
bool exec_vadd(void);

// exec_vsmult() performs scalar multiplication of a vector.
// effects: reads input, produces output
bool exec_vsmult(void);

// exec_dot() evaluates the dot product of two vectors in Rn.
// effects: reads input, produces output
bool exec_dot(void);

// exec_cross() evaluates the cross product of two vectors in R3.
// effects: reads input, produces output
bool exec_cross(void);

// exec_vlen() determines the length (norm) of a vector.
// effects: reads input, produces output
bool exec_vlen(void);

// exec_vang() determines the angle between two vectors in radians.
// effects: reads input, produces output
bool exec_vang(void);

// exec_veq() determines if two vectors are equal.
// effects: reads input, produces output
bool exec_veq(void);

// exec_projv() finds the projection of a vector onto another vector.
// effects: reads input, produces output
bool exec_projv(void);

// exec_perpv() finds the perpendicular of a vector onto another vector.
// effects: reads input, produces output
bool exec_perpv(void);

// exec_projp() finds the projection of a vector in R3 onto a plane.
// effects: reads input, produces output
bool exec_projp(void);

// exec_perpp() finds the perpendicular of a vector in R3 onto a plane.
// effects: reads input, produces output
bool exec_perpp(void);

#endif
