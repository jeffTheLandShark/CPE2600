/*
 * Filename : function_poly.c
 * Description : how to use function pointer in typedefs
 * Author : Bob Turney
 * Date : 3 / 26 / 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct shape {
  int x;
  int y;
  int width;
  int height;
  void (*draw)(struct shape *);
} shape;

void drawRect(shape *this) {
  printf("drawing a %d x %d rectangle at %d %d\n", this->width, this->height,
         this->x, this->y);
  return;
}

void drawCircle(shape *this) {
  printf("drawing a %d radius circle at %d, %d\n", this->width, this->x,
         this->y);
  return;
}

shape newRectangle(int x, int y, int width, int height) {
  shape rect;
  rect.x = x;
  rect.y = y;
  rect.width = width;
  rect.height = height;
  rect.draw = drawRect;
  return rect;
}

shape newCircle(int x, int y, int radius) {
  shape circle;
  circle.x = x;
  circle.y = y;
  circle.width = radius;
  circle.draw = drawCircle;
  return circle;
}

#define DRAW(shape) (shape)->draw(shape)

int main() {
  int i;
  shape shapes[3];
  shapes[0] = newRectangle(5, 10, 15, 20);
  shapes[1] = newCircle(55, 60, 75);
  shapes[2] = newRectangle(85, 90, 95, 100);
  /* draw */
  for (i = 0; i < 3; i++) {
    (*(shapes[1].draw))(&shapes[1]);
    (*(shapes + 1)->draw)(shapes + i);
    DRAW(shapes + i);
    DRAW(&shapes[1]);
  }
  return 0;
}