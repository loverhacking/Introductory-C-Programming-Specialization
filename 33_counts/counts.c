#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t * ct = malloc(sizeof(*ct));
  ct->size = 0;
  ct->unknownSize = 0;
  ct->array = NULL;
  return ct;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknownSize++;
    return;
  }
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(c->array[i]->str, name) == 0) {
      c->array[i]->count++;
      return;
    }
  }
  c->size++;
  c->array = realloc(c->array, c->size * sizeof(one_count_t*));
  c->array[c->size-1] = malloc(sizeof(one_count_t));
  c->array[c->size - 1]->count = 1;
  c->array[c->size - 1]->str = malloc((strlen(name) + 1)* sizeof(char));
  strcpy(c->array[c->size -1]->str, name);
}

void printCounts(counts_t * c, FILE * outFile) {
  if (outFile == NULL) {
    fprintf(stderr, "invalid file");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %lu\n",
      c->array[i]->str, c->array[i]->count);
  }
  if (c->unknownSize != 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->unknownSize);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    free(c->array[i]->str);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
