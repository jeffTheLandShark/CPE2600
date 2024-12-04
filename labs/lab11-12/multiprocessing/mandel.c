///
//  mandel.c
//  Based on example code found here:
//  https://users.cs.fiu.edu/~cpoellab/teaching/cop4610_fall22/project3.html
//
//  Converted to use jpg instead of BMP and other minor changes
//
///
#include "mandel.h"
#include "jpegrw.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_IMAGES 50

void fly_in(int num_children, double xscale, double yscale, int image_width,
            int image_height, int max, const char *outfile) {
  int i;
  double scale;
  int status;
  pid_t pid;

  double xcenter = -1.0 / 15.0;
  double ycenter = 2.0 / 3.0;

  int living_children = 0;
  int max_scale;

  for (i = 0; i < NUM_IMAGES; i++) {
    if (living_children >= num_children) {
      wait(&status);
      living_children--;
    }
    pid = fork();
    if (pid == 0) {
      char filename[100];
      sprintf(filename, "%s%02d.jpg", outfile, i);
      scale =
          (double)(NUM_IMAGES - i) / (double)NUM_IMAGES; // scale from 1 to 0
      max_scale = (1 - scale) / 0.4 + 1;
      scale = scale * scale;
      mandel(xcenter, ycenter, xscale * scale, yscale * scale, image_width,
             image_height, max * max_scale, filename);
      exit(0);
    } else {
      living_children++;
    }
  }

  for (i = living_children; i > 0; i--) {
    wait(&status);
  }
}

void mandel(double xcenter, double ycenter, double xscale, double yscale,
            int image_width, int image_height, int max, const char *outfile) {

  // Calculate y scale based on x scale (settable) and image sizes in X and Y
  // (settable)
  yscale = xscale / image_width * image_height;

  // Create a raw image of the appropriate size.
  imgRawImage *img = initRawImage(image_width, image_height);

  // Fill it with a black
  setImageCOLOR(img, 0);

  // Compute the Mandelbrot image
  compute_image(img, xcenter - xscale / 2, xcenter + xscale / 2,
                ycenter - yscale / 2, ycenter + yscale / 2, max);

  // Save the image in the stated file.
  storeJpegImageFile(img, outfile);

  // free the mallocs
  freeRawImage(img);

  // Display the configuration of the image.
  printf("mandel: x=%lf y=%lf xscale=%lf yscale=%1f max=%d outfile=%s\n",
         xcenter, ycenter, xscale, yscale, max, outfile);
}

/*
Return the number of iterations at point x, y
in the Mandelbrot space, up to a maximum of max.
*/

int iterations_at_point(double x, double y, int max) {
  double x0 = x;
  double y0 = y;

  int iter = 0;

  while ((x * x + y * y <= 4) && iter < max) {

    double xt = x * x - y * y + x0;
    double yt = 2 * x * y + y0;

    x = xt;
    y = yt;

    iter++;
  }

  return iter;
}

/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to
"max"
*/

void compute_image(imgRawImage *img, double xmin, double xmax, double ymin,
                   double ymax, int max) {
  int i, j;

  int width = img->width;
  int height = img->height;

  // For every pixel in the image...

  for (j = 0; j < height; j++) {

    for (i = 0; i < width; i++) {

      // Determine the point in x,y space for that pixel.
      double x = xmin + i * (xmax - xmin) / width;
      double y = ymin + j * (ymax - ymin) / height;

      // Compute the iterations at that point.
      int iters = iterations_at_point(x, y, max);

      // Set the pixel in the bitmap.
      setPixelCOLOR(img, i, j, iteration_to_color(iters, max));
    }
  }
}

/*
Convert a iteration number to a color.
Here, we just scale to gray with a maximum of imax.
Modify this function to make more interesting colors.
*/
int iteration_to_color(int iters, int max) {
  int color = 0xFFFFFF * iters / (double)max;
  return color;
}

// Show help message
void show_help() {
  printf("Use: mandel [options]\n");
  printf("Where options are:\n");
  printf("-m <max>    The maximum number of iterations per point. "
         "(default=1000)\n");
  printf("-x <coord>  X coordinate of image center point. (default=0)\n");
  printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
  printf("-s <scale>  Scale of the image in Mandlebrot coordinates (X-axis). "
         "(default=4)\n");
  printf("-W <pixels> Width of the image in pixels. (default=1000)\n");
  printf("-H <pixels> Height of the image in pixels. (default=1000)\n");
  printf("-o <file>   Set output file. (default=mandel.bmp)\n");
  printf("-h          Show this help text.\n");
  printf("\nSome examples are:\n");
  printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
  printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
  printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}
