#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void deal_with_file(FILE * f) {
  char ** lines = NULL;
  char * cur = NULL;
  size_t sz = 0;
  size_t count_lines = 0;
  while (getline(&cur, &sz, f) >= 0) {
    lines = realloc(lines,
      (count_lines + 1) * sizeof(*lines));
    lines[count_lines] = cur;
    cur = NULL;
    count_lines++;
  }
  free(cur);
  sortData(lines, count_lines);
  for (size_t i = 0; i < count_lines; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    deal_with_file(stdin);
  } else if (argc > 1) {
    for (size_t i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
      }
      deal_with_file(f);
      if(fclose(f) != 0) {
	fprintf(stderr, "Could not close file\n");
	return EXIT_FAILURE;
      }
    }
  } else {
    printf("wrong argument number\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
