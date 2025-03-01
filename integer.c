#include "integer.h"

int numlen(int num) {
  int len = (num < 0);
  if (num < 0) {
    num = -num;
  }

  do {
    num /= 10;
    len++;
  } while (num != 0);

  return len;
}
