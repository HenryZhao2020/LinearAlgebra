#include "real.h"

#include <stdio.h>

int numlen(double num) {
  char buffer[40];
  int length = sprintf(buffer, "%.39g", num);
  return length;
}
