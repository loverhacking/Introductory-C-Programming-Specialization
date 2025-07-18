#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findMaxId(int * arry, int size) {
    int max = 0;
    int max_id = 0;
    // find max and max_id
    for (int i = 0; i < size; i++) {
        if (max < arry[i]) {
            max = arry[i];
            max_id = i;
        }
    }
    return max_id;
}

int break_encryption(FILE * f) {
    int count_char[26] = {0};
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            count_char[c -'a']++;
        }
    }
    int max_id = findMaxId(count_char, 26);
    for (int i = 0; i < 26; i++) {
        if (count_char[i] == count_char[max_id] && i != max_id) {
            fprintf(stderr,"Can not break encryption according to given file\n");
            return EXIT_FAILURE;
        }
    }
    int cons = 'e' - 'a';
    int key;
    if (max_id < cons) {
        key = max_id  + 26 * 1 - cons;
    } else {
        key = max_id + 26 * 0 - cons;
    }
    return key;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    int key = break_encryption(f);
    printf("%d\n", key);
}
