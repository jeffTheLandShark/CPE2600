/*
 * @file: benchmark.c
 * @brief: This file is used to benchmark the performance of the mandelbrot
 *         Collects the runtime for 1, 2, 5, 10, and 20 children processes
 *         and graphs the results
 */

#include "mandel.h"
#include <bits/types/timer_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static void benchmark();
static void graph();

int main(void) {
  benchmark();
  graph();
  return 0;
}

void benchmark() {
  int benchmark_values[] = {1, 2, 5, 10, 20};
  int num_values = sizeof(benchmark_values) / sizeof(benchmark_values[0]);

  const char *outfile = "movie/mandel";

  double xscale = 4;
  int image_width = 1000;
  int image_height = 1000;
  int max = 1000;
  int num_children = 1;

  int yscale = xscale * image_height / image_width;

  double runtimes[num_values];
  for (int i = 0; i < num_values; i++) {
    num_children = benchmark_values[i];
    struct timespec start, end;

    printf("Benchmarking with %d children\n", num_children);

    clock_gettime(CLOCK_MONOTONIC, &start);
    fly_in(num_children, xscale, yscale, image_width, image_height, max,
           outfile);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double runtime =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    runtimes[i] = runtime;
  }

  FILE *fp = fopen("benchmarking/benchmark.csv", "w");
  if (fp == NULL) {
    perror("fopen");
    exit(1);
  }

  fprintf(fp, "num_children,runtime\n");
  for (int i = 0; i < num_values; i++) {
    fprintf(fp, "%d,%f\n", benchmark_values[i], runtimes[i]);
  }

  fclose(fp);
}

void graph() {
  FILE *fp = popen("gnuplot", "w");
  if (fp == NULL) {
    perror("popen");
    exit(1);
  }

  fprintf(fp, "set terminal png\n");
  fprintf(fp, "set output 'benchmarking/benchmark.png'\n");
  fprintf(fp, "set title 'Mandelbrot Benchmark'\n");
  fprintf(fp, "set xlabel 'Number of Children'\n");
  fprintf(fp, "set ylabel 'Runtime (s)'\n");
  fprintf(fp, "set datafile separator ','\n");
  fprintf(fp, "plot 'benchmarking/benchmark.csv' using 1:2 with linespoints\n");
  fprintf(fp, "quit\n");

  pclose(fp);
}