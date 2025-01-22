/*
 * @file thread_args.h
 * @brief Struct for passing arguments to a thread.
 */

#ifndef THREAD_ARGS_H
#define THREAD_ARGS_H

#include "jpegrw.h"

typedef struct thread_args {
  int start, end;                /** The range of rows to compute. */
  imgRawImage *img;              /** The image to write to. */
  double xmin, xmax, ymin, ymax; /** The bounds of the image. */
  int max;                       /** The maximum number of iterations. */
} thread_args;


#endif