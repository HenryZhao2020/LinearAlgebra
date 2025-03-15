// "command.h" implements commands that prompt users to define the necessary 
//   variables, then perform the corresponding linear algebra operations.

#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

// Each function produces true if the operations succeed and false otherwise.
// To prevent duplication, refer to 'help.txt' for command description.
// effects: reads input, produces output

// Vector Operations
bool exec_vadd(void);
bool exec_vsmult(void);
bool exec_dot(void);
bool exec_cross(void);
bool exec_vlen(void);
bool exec_vang(void);
bool exec_veq(void);

// Projections
bool exec_projv(void);
bool exec_perpv(void);
bool exec_projp(void);
bool exec_perpp(void);

// Matrix Operations
bool exec_madd(void);
bool exec_msmult(void);
bool exec_mvmult(void);
bool exec_mmmult(void);
bool exec_mtran(void);
bool exec_miden(void);
bool exec_meq(void);

#endif
