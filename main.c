#include "vector.h"
#include "matrix.h"
#include "basis.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const int cmd_max_len = 10;

// read_vec(vec, var) reads the dimension n and the components of a vector.  
//   If the input is valid, it updates vec and returns true.  
//   Otherwise, vec remains unchanged, and the function returns false.  
//   var represents the name of vec.  
// requires: vec and var are not NULL.
// effects: reads input, produces output
//          may mutate vec.
bool read_vec(struct vector *vec, const char *var) {
  assert(vec);
  assert(var);

  int n = 0;
  int comp[100];

  printf("Defining vector %s\n", var);
  printf("Dimension: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  printf("Defining components of the vector %s\n", var);
  for (int i = 0; i < n; ++i) {
    printf("x%d: ", (i + 1));
    if (1 != scanf("%d", &comp[i])) {
      return false;
    }
  }

  vec->n = n;
  for (int i = 0; i < n; ++i) {
    vec->comp[i] = comp[i];
  }

  return true;
}

// exec_vec_add() executes vector addition.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vec_add() {
  struct vector v1 = {0, {0}};
  struct vector v2 = {0, {0}};

  if (!read_vec(&v1, "v1")) {
    return false;
  }
  printf("\n");
  if (!read_vec(&v2, "v2")) {
    return false;
  }
  printf("\n");

  struct vector sum = vec_add(&v1, &v2);
  printf("Vector addition:\n");
  print_vec(&v1);
  printf("+\n");
  print_vec(&v2);
  printf("=\n");
  print_vec(&sum);
  printf("\n");

  return true;
}

// exec_vec_scalar_mult() executes scalar vector multiplication.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_vec_scalar_mult() {
  struct vector vec = {0, {0}};
  if (!read_vec(&vec, "v")) {
    return false;
  }
  printf("\n");

  int c = 0;
  printf("c: ");
  if (1 != scanf("%d", &c)) {
    return false;
  }
  printf("\n");

  struct vector prod = vec_scalar_mult(&vec, c);
  printf("Vector scalar multiplication:\n");
  printf("%d\n", c);
  printf("*\n");
  print_vec(&vec);
  printf("=\n");
  print_vec(&prod);
  printf("\n");

  return true;
}

// exec_std_basis() produces the standard basis for Rn.
//   The function produces true if the operation is successful and false otherwise.
// effects: reads input, produces output
bool exec_std_basis() {
  int n = 0;
  printf("n: ");
  if (1 != scanf("%d", &n)) {
    return false;
  }

  struct matrix basis = std_basis(n);
  printf("Standard basis for R%d\n", n);
  print_matrix(&basis);
  return true;
}

// help() outputs program mannual and developer info.
// effects: produces output
void help() {
  const int dashes = 35;

  printf("(#)\tCommand\t\tOperation\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");
  printf("(0)\texit\t\tterminate the program\n");
  printf("(1)\thelp\t\tprogram manual and developer info\n");
  printf("(2)\tva\t\tvector addition\n");
  printf("(3)\tvsm\t\tvector scalar multiplication\n");
  printf("(4)\tstdb\t\tstandard basis of Rn\n");

  printf("\nProgram Information\n");
  for (int i = 0; i < dashes; ++i) printf("-");
  printf("\n");
  printf("Developer:\tHenry Zhao\n");
  printf("Version:\tv1.0\n");
  printf("Reference:\tD. Wolczuk, MATH 136 Course Notes Edition 2024.1\n");
}

int main(void) {
  printf("Welcome to Linear Algebra Tutor!\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11];
    printf("Enter number or command (e.g. 2 or va): ");
    if (1 != scanf("%10s", cmd)) {
      break;
    }
    printf("\n");
    
    if (!strcmp(cmd, "exit") || !strcmp(cmd, "0")) {
      break;
    } else if (!strcmp(cmd, "help") || !strcmp(cmd, "1")) {
      help();
    } else if (!strcmp(cmd, "va") || !strcmp(cmd, "2")) {
      exec_vec_add();
    } else if (!strcmp(cmd, "vsm") || !strcmp(cmd, "3")) {
      exec_vec_scalar_mult();
    } else if (!strcmp(cmd, "stdb") || !strcmp(cmd, "4")) {
      exec_std_basis();
    } else {
      printf("Invalid command! Please enter 'help' to see the program manual.\n");
    }

    printf("\n");
  }

  printf("\nHope you ace linear algebra! See you next time.\n");
}
