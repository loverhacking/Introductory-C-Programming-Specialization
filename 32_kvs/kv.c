#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void copy_substring(char * src, char * des, size_t start, size_t end) {
  size_t j = 0;
  for (size_t i = start; i < end; i++) {
    des[j] = src[i];
    j++;
  }
  des[j] = '\0';
}

void split_kvPair(kvarray_t * kvarray, char ** lines) {
  for (size_t i = 0; i < kvarray->len; i++) {
    size_t j = 0;
    size_t len_key = 0;
    kvarray->pairs[i] = malloc(sizeof(kvpair_t));

    while (lines[i][j] != '\n') {
      if (lines[i][j] == '=') {
        char * key = malloc((len_key + 1) * sizeof(char));
        copy_substring(lines[i], key, 0, len_key);
	      // omit '=' and final '\n' so length is total - key - 1 - 1 and plus extra '\0'
        char * val = malloc((strlen(lines[i]) - len_key - 1 - 1 + 1) * sizeof(char));
        copy_substring(lines[i], val, len_key + 1, strlen(lines[i]) - 1);

        kvarray->pairs[i]->key = key;
        kvarray->pairs[i]->val = val;
        break;
      }
      len_key++;
      j++;
    }
  }
}

kvarray_t * readKVs(const char * fname) {
 FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "can not open file");
    exit(EXIT_FAILURE);
  }

  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t count = 0;

  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines,
            (count + 1) * sizeof(*lines));
    lines[count] = curr;
    curr = NULL;
    count++;
  }
  free(curr);

  kvarray_t  * kvPair = malloc(sizeof(kvarray_t));
  kvPair->len = count;
  kvPair->pairs = malloc(count * sizeof(kvpair_t*));
  split_kvPair(kvPair, lines);

  int result = fclose(f);
  if (result != 0) {
    fprintf(stderr, "can not close file");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < count; i++) {
    free(lines[i]);
  }
  free(lines);

  return kvPair; 
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]->val);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n",
      pairs->pairs[i]->key, pairs->pairs[i]->val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->len; i++) {
    if (strcmp(pairs->pairs[i]->key, key) == 0) {
      return pairs->pairs[i]->val;
    }
  }
  return NULL;
}
