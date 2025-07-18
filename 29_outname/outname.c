#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
    char * newFileName;
    newFileName = malloc((strlen(inputName) + 8)
    * sizeof(char));
    strcpy(newFileName, inputName);
    strcat(newFileName, ".counts");
    return newFileName;
}
