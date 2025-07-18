#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  size_t ans;
 
  int testArray1[] = {};
  ans = maxSeq(testArray1, 0);
  if (ans != 0) {
    return EXIT_FAILURE;
  }

  int testArray2[] = {1, 2, 3, 0, 1, 2, 3, 4};
  ans = maxSeq(testArray2, 8);
  if (ans != 5) {
    return EXIT_FAILURE;
  }

  int testArray3[] = {2, 2, 2, 3};
  ans = maxSeq(testArray3, 4);
  if (ans != 2) {
    return EXIT_FAILURE;
  }

  int testArray4[] = {1};
  ans = maxSeq(testArray4, 1);
  if (ans != 1) {
    return EXIT_FAILURE;
  }

  int testArray5[] = {2, -3, 5, 6, 8};
  ans = maxSeq(testArray5, 5);
  if (ans != 4) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}
