#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nnls.h"

#define USAGE "." 

int load_a_matrix(char *filename) {

  long x = 0;
  long y = 0;
  char *line = NULL;
  size_t len = 0;

  fh = fopen(filename, "r");
  if(fh == NULL) {
    fprintf(stderr, "Could not open %s\n", filename);
    exit(EXIT_FAILURE);
  }
    
  if(getline(&line, &len, fp) != -1) {

  }

  while ((read = getline(&line, &len, fp)) != -1) {

  }


}
int main(int argc, char **argv) {


  int c;

  char *a_matrix_filename = NULL;
  char *b_matrix_filename = NULL;
  char *output_filename = NULL;
  char *format = NULL;

  long x = 0;
  long y = 0;

  int verbose = 0;

  long width = 0;
  long height = 0;

  while (1) {
    static struct option long_options[] = {
      {"a", required_argument, 0, 'a'},
      {"b", required_argument, 0, 'b'},
      {"output", required_argument, 0, 'o'},
      {"verbose", no_argument, 0, 'v'},
      {"format", required_argument, 0, 'f'},
      {"version", no_argument, 0, 'V'},
      {0, 0, 0, 0}
    };

    int option_index = 0;

    c = getopt_long (argc, argv, "i:o:hdvV", long_options, &option_index);

    if (c == -1)
      break;

    switch (c) {
      case 0:
      case 'a':
        a_matrix_filename = optarg;
        break;
      case 'b':
        b_matrix_filename = optarg;
        break;
      case 'o':
        output_filename = optarg;
        break;
      case 'f':
        format = optarg;
        break;
      case 'v':
        verbose = 1;
        break;
      case 'V':
        printf("%s\n", VERSION);
        exit(EXIT_SUCCESS);
        break;
      case 'h':
        printf("%s\n", USAGE);
        exit(EXIT_SUCCESS);
        break;
      default:
        break;
    }
  }


  if(a_matrix_filename == NULL) {
    fprintf(stderr, "Error: a matrix file (-a) must be specified\n\n");
    fprintf(stderr, "%s\n", USAGE);
    exit(EXIT_FAILURE);
  }

  if(b_matrix_filename == NULL) {
    fprintf(stderr, "Error: b matrix file (-b) must be specified\n\n");
    fprintf(stderr, "%s\n", USAGE);
    exit(EXIT_FAILURE);
  }

  if(output_filename == NULL) {
    fprintf(stderr, "Error: output filename (-o) must be specified\n\n");
    fprintf(stderr, "%s\n", USAGE);
    exit(EXIT_FAILURE);
  }

  if(format == NULL) {
    format = "%10lf";
  }

  if(verbose) { 
    printf("a matrix: %s\n", a_matrix_filename);
    printf("b matrix: %s\n", a_matrix_filename);
    printf("output file: %s\n", output_filename);
  }

  if(access (a_matrix_filename, F_OK) == -1) {
    fprintf(stderr, "Error: could not open %s\n", a_matrix_filename);
    exit(EXIT_FAILURE);
  }

  if(access (b_matrix_filename, F_OK) == -1) {
    fprintf(stderr, "Error: could not open %s\n", b_matrix_filename);
    exit(EXIT_FAILURE);
  }

  // load our matricies
  double *a_matrix = load_a_matrix(a_matrix_filename);
  double *b_matrix = load_b_matrix(b_matrix_filename);

  // run NNLS
  double *solution = nnls(a_matrix, b_matrix, height, width);

  // print to stdout if the user supplies "-" as the output argument
  FILE *output_fh = NULL;
  if(strcmp(output_filename, "-") == 0) {
    output_fh = stdout;
  }
  else {
    output_fh = fopen(output_filename, "w");
  }

  if(output_fh == NULL) { 
    fprintf(stderr, "Could not open %s for writing\n", output_filename);
    exit(EXIT_FAILURE);
  }
  for(x = 0; x < height; x++) {
      fprintf(output_fh, format, solution[x]);
  }
  fclose(output_fh);

  return EXIT_SUCCESS;
}
