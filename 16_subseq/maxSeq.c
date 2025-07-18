#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
    if (n <= 1) {
        return n;
    }
    size_t maxSeq = 0;
    for (size_t i = 0; i < n; i++) {
        size_t count = 1;
        for (size_t j = i;j < n - 1; j++) {
            if (array[j] < array[j + 1]) {
                count++;
            } else {
                i = j;
                break;
            }
        }
        if (count > maxSeq) {
            maxSeq = count;
        }
    }
    return maxSeq;
}
