///
//  mandel.c
//  Based on example code found here:
//  https://users.cs.fiu.edu/~cpoellab/teaching/cop4610_fall22/project3.html
//
//  Converted to use jpg instead of BMP and other minor changes
//
///

// @note: created so that mandel.c functions can be used in other files

#include "jpegrw.h"

// local routines
int iteration_to_color(int i, int max);
int iterations_at_point(double x, double y, int max);
void compute_image(imgRawImage *img, double xmin, double xmax, double ymin,
                   double ymax, int max);
void show_help();

void mandel(double xcenter, double ycenter, double xscale, double yscale,
            int image_width, int image_height, int max, const char *outfile);

void fly_in(int num_children, double xscale, double yscale, int image_width,
            int image_height, int max, const char *outfile);