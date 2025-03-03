#include "real.h"

#include <stdio.h>

int numlen(double num) {
  char buffer[50];
  int length = sprintf(buffer, "%.15g", num);
  return length;
}
