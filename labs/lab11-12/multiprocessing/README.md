# System Programming Lab 11 Multiprocessing
## Repo Guide

- Lab reports are in the `/reports` folder
- `mandelmovie.c` is the main program, which if you call `make` will compile to `mandelmovie`
  - The program saves 50 frames of the mandelbrot set to `movie/` which can be compiled into a movie using `ffmpeg movie/mandel%02d.jpg mandel.mp4`
  - Previously created movies and other artifacts are in `movie_artifacts/`
- `mandel.c` has been modified
  - the `fly_in()` function has been added
  - `compute_image()` has been modified to use multithreading
- `mandel.h` has been modified to include all the necessary functions and variables
- `benchmark.c` is the benchmarking program
  - `benchmark` is the compiled version of `benchmark.c` which is compiled by calling `make benchmark`
  - The program will run `fly_in()` on the five cases {1, 2, 5, 10, 20} for number of processes and for number of threads
  - The program saves the results in `benchmarking/`
