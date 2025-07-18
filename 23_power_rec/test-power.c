#include <stdlib.h>
#include <stdio.h>
#include "power.c"
unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned actual_ans = power(x, y);
  if (actual_ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}
int main(void)
{
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(1, 1, 1);
  run_check(1, 2, 1);
  run_check(3, 0, 1);
  run_check(3, 1, 3);
  run_check(3, 2, 9);
  run_check(3, 3, 27);
  run_check(-3, 2, 9);
  run_check(0xffffffff, 1, 0xffffffff);
  return EXIT_SUCCESS;
}
