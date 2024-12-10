/*
 * @file mandelmovie.c
 * @brief: This file is used to create a movie of the mandelbrot set
 * @note: to combine the images into a movie, run the following command:
 *       ffmpeg -i movie/mandel%02d.jpg movie.mp4
 */

#include "mandel.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// main similar to mandel.c original main
int main(int argc, char *argv[]) {
  char c;

  const char *outfile = "movie/mandel"; // default output file

  double xscale = 4;
  double yscale = 0; // calc later
  int image_width = 1000;
  int image_height = 1000;
  int max = 1000;
  int num_children = 1;
  int num_threads = 1;

  // parse command line arguments
  while ((c = getopt(argc, argv, "s:W:H:m:o:n:t:h")) != -1) {
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
    case 't':
      num_threads = atoi(optarg);
      break;
    default:
      printf("Usage: %s [-s scale] [-W width] [-H "
             "height] [-m max] [-o outfile] [-n num_children] [-t num_threads]\n",
             argv[0]);
      exit(1);
      break;
    }
  }

  yscale = xscale * image_height / image_width; // calculate yscale

  // call fly_in function with the given parameters to create the movie
  fly_in(num_children, xscale, yscale, image_width, image_height, max,
         num_threads, outfile);

  return 0;
}