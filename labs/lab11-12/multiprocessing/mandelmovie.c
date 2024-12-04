/*
 * @file mandelmovie.c
 * @brief: Use child processes to generate 50 images
 *         by progressively changing one or more image
 *         parameters (e.g., the scale, the center,
 *         the maximum number of iterations, etc.)
 *         Must allow the number of child processes to
 *         be specified on the command line.
 *         The command line must be interpreted using the getopt function.
 */

#include "mandel.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char c;

  const char *outfile = "movie/mandel";

  double xscale = 4;
  double yscale = 0; // calc later
  int image_width = 1000;
  int image_height = 1000;
  int max = 1000;
  int num_children = 1;

  while ((c = getopt(argc, argv, "s:W:H:m:o:n:h")) != -1) {
    switch (c) {
    case 's':
      xscale = atof(optarg);
      break;
    case 'W':
      image_width = atoi(optarg);
      break;
    case 'H':
      image_height = atoi(optarg);
      break;
    case 'm':
      max = atoi(optarg);
      break;
    case 'o':
      outfile = optarg;
      break;
    case 'n':
      num_children = atoi(optarg);
      break;
    default:
      printf("Usage: %s [-s scale] [-W width] [-H "
             "height] [-m max] [-o outfile] [-n num_children]\n",
             argv[0]);
      exit(1);
      break;
    }
  }

  yscale = xscale * image_height / image_width;

  fly_in(num_children, xscale, yscale, image_width, image_height, max, outfile);

  return 0;
}