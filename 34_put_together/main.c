#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void stripNewline(char* str) {
    char * p = strchr(str, '\n');
    if (p != NULL) {
        *p = '\0';
    }
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "invalid file");
        exit(EXIT_FAILURE);
    }

    size_t sz = 0;
    ssize_t len = 0;
    char * line = NULL;
    while((len = getline(&line, &sz, f)) >= 0) {
        // note there is a '\n' at the end of line
        // which should be omitted for lookupValue()
        stripNewline(line);
        char * val = lookupValue(kvPairs, line);
        addCount(c, val);
    }
    free(line);
    int result = fclose(f);
    if (result != 0) {
      fprintf(stderr, "can not close file");
      exit(EXIT_FAILURE);
    }
    return c;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
        fprintf(stderr, "The number of parameters is incorrect");
        return EXIT_FAILURE;
    }
    //read the key/value pairs from the file named by argv[1] (call the result kv)
    kvarray_t * kvpair = readKVs(argv[1]);
    //count from 2 to argc (call the number you count i)
    for (size_t i = 2; i < argc; i++) {
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        ////   (call this result c)
        counts_t * c = countFile(argv[i], kvpair);

        //compute the output file name from argv[i] (call this outName)
        char * output = computeOutputFileName(argv[i]);

        //open the file named by outName (call that f)
        //print the counts from c into the FILE f
        FILE * f = fopen(output, "w");
        printCounts(c, f);

        //close f
        int result = fclose(f);
        if (result != 0) {
            fprintf(stderr, "can not close file");
            return EXIT_FAILURE;
        }

        //free the memory for outName and c
        free(output);
        freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kvpair);
  return EXIT_SUCCESS;
}
