#include "vector.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const int cmd_max_len = 5;

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
  printf(" + ");
  print_vec(&v2);
  printf(" = ");
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
  printf("%d", c);
  print_vec(&vec);
  printf(" = ");
  print_vec(&prod);
  printf("\n");

  return true;
}

// help() outputs program mannual and developer info.
// effects: produces output
void help() {
  printf("Help is on the way~\n");
}

int main(void) {
  printf("Welcome to MATH 136 Tutor!\n");
  printf("Developer: Henry Zhao\n\n");
  printf("Please enter 'help' to get started.\n\n\n");
  
  while (true) {
    char cmd[11];
    printf("Command: ");
    if (1 != scanf("%10s", cmd) || !strcmp(cmd, "e")) {
      break;
    }
    printf("\n");
    
    if (!strcmp(cmd, "help")) {
      help();
    } else if (!strcmp(cmd, "va")) {
      exec_vec_add();
    } else if (!strcmp(cmd, "vsm")) {
      exec_vec_scalar_mult();
    } else {
      printf("Invalid command! Please enter 'help' to see the program mannual.\n");
    }

    printf("\n");
  }

  printf("Hope you ace MATH 136! See you next time.\n");
}
