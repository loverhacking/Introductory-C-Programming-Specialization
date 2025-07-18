#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 12


void store(char * ptr, char * str) {
    for (int i = 0; i < 10; i++) {
        ptr[i] = str[i];
    }
}

void rotate(char matrix[10][10]) {
    char copy[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = copy[9 - j][i];
        }
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr,"Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr,"null text file\n");
        return EXIT_FAILURE;
    }
    char board[10][10] = {0};

    char line[LINE_SIZE];
    int count = 0;

    // note: LINE_SIZE = 10 + 1 + 1 = 12
    // include '\n' and '\0'
    while (fgets(line, LINE_SIZE, f) != NULL) {
       if (count >= 10) {
            fprintf(stderr, "Too many lines!\n");
            return EXIT_FAILURE;
        }
        if (strchr(line, '\n') == NULL) {
            fprintf(stderr,"Line too long\n");
            return EXIT_FAILURE;
        }
        if (strlen(line) < 11) {
            fprintf(stderr,"Line too short\n");
            return EXIT_FAILURE;
        }
        store(board[count], line);
        count++;
    }

    if (count < 10) {
        fprintf(stderr, "Not enough number of lines\n");
        return EXIT_FAILURE;
    }
    
    rotate(board);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
