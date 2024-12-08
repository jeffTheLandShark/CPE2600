/*
 * @file: benchmark.c
 * @brief: This file is used to benchmark the performance of the mandelbrot
 *         Collects the runtime for 1, 2, 5, 10, and 20 children processes
 *         and graphs the results
 * @date: 2024-12-01
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

static void benchmark_children();
static void benchmark_threads();
static void benchmark(int mode, char *benchmarkfile);
static void graph(char *outfile);
static void graph_both(char *outfile);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    benchmark_children();
    benchmark_threads();
    graph_both("benchmarking/both");
    return 0;
  }

  int mode = atoi(argv[1]);
  if (mode == 1) {
    benchmark_children();
  } else if (mode == 2) {
    benchmark_threads();
  } else {
    fprintf(stderr, "Invalid mode\n");
    exit(1);
  }

  return 0;
}

void benchmark_children() {
  benchmark(1, "benchmarking/children");
  graph("benchmarking/children");
}
void benchmark_threads() {
  benchmark(2, "benchmarking/threads");
  graph("benchmarking/threads");
}

void benchmark(int mode, char *benchmarkfile) {
  int benchmark_values[] = {1, 2, 5, 10, 20};

  // Number of values in the benchmark_values array
  int num_values = sizeof(benchmark_values) / sizeof(benchmark_values[0]);

  // **** default values match the values in mandelmovie.c ****
  const char *outfile = "movie/mandel";

  double xscale = 4;
  int image_width = 1000;
  int image_height = 1000;
  int max = 1000;
  int num_children = 1;
  int num_threads = 1;

  int yscale = xscale * image_height / image_width;
  // *****************************************************

  double runtimes[num_values]; // Array to store the runtimes
  struct timespec start, end;  // Structs to store the start and end times

  // run benchmarks
  for (int i = 0; i < num_values; i++) {
    if (mode == 1) {
      num_children = benchmark_values[i];
      printf("Benchmarking with %d children\n", num_children);
    } else {
      num_threads = benchmark_values[i];
      printf("Benchmarking with %d threads\n", num_threads);
    }

    clock_gettime(CLOCK_MONOTONIC, &start); // start
    fly_in(num_children, xscale, yscale, image_width, image_height, max,
           num_threads, outfile); // run the mandelbrot function

    clock_gettime(CLOCK_MONOTONIC, &end); // end

    // Calculate the runtime
    double runtime =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    runtimes[i] = runtime; // Store the runtime
  }

  // write the results to a csv file
  char filename[256];
  sprintf(filename, "%s.csv", benchmarkfile);
  printf("Writing results to %s\n", filename);
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(1);
  }

  if (mode == 1) {
    fprintf(fp, "Children,Runtime\n");
  } else {
    fprintf(fp, "Threads,Runtime\n");
  }
  for (int i = 0; i < num_values; i++) {
    fprintf(fp, "%d,%f\n", benchmark_values[i], runtimes[i]);
  }

  fclose(fp);
}

void graph(char *outfile) {
  printf("Graphing results to %s.png\n", outfile);
  // Use gnuplot to graph the results using cmd line commands
  FILE *fp = popen("gnuplot", "w");
  if (fp == NULL) {
    perror("popen");
    exit(1);
  }

  fprintf(fp, "set terminal png\n");                 // file type png
  fprintf(fp, "set output '%s.png'\n", outfile);     // file name
  fprintf(fp, "set title 'Mandelbrot Benchmark'\n"); // title
  fprintf(fp, "set xlabel 'Number of Children'\n");  // x-axis label
  fprintf(fp, "set ylabel 'Runtime (s)'\n");         // y-axis label
  fprintf(fp, "set datafile separator ','\n");       // csv file separator
  fprintf(fp, "plot '%s.csv' using 1:2 with linespoints\n", outfile);
  fprintf(fp, "quit\n");

  pclose(fp);
}

void graph_both(char *outfile) {
  printf("Graphing results to %s.png\n", outfile);
  // Use gnuplot to graph the results using cmd line commands
  FILE *fp = popen("gnuplot", "w");
  if (fp == NULL) {
    perror("popen");
    exit(1);
  }

  fprintf(fp, "set terminal png\n");                 // file type png
  fprintf(fp, "set output '%s.png'\n", outfile);     // file name
  fprintf(fp, "set title 'Mandelbrot Benchmark'\n"); // title
  fprintf(fp, "set xlabel 'Number of Children'\n");  // x-axis label
  fprintf(fp, "set ylabel 'Runtime (s)'\n");         // y-axis label
  fprintf(fp, "set datafile separator ','\n");       // csv file separator
  fprintf(fp, "plot 'benchmarking/children.csv' using 1:2 with linespoints, "
              "'benchmarking/threads.csv' using 1:2 with linespoints\n");
  fprintf(fp, "quit\n");

  pclose(fp);
}