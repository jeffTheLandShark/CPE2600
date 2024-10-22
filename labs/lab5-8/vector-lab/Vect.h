/**
 * @file vect.h
 * @brief defines vect struct
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 *
 */
#ifndef VECTSTORE_H
#define VECTSTORE_H

typedef struct Vect {
  int x;
  int y;
  int z;
  char name[20];
} Vect;

#endif