#include "printer.h"

#include <stdio.h>

void print_space(const int num_spaces) {
  for (int i = 0; i < num_spaces; ++i) {
    printf(" ");
  }
}

void print_real(const double num) {
  if (num == -0.0) {
    printf("%d", 0);
  } else {
    printf("%g", num);
  }
}
