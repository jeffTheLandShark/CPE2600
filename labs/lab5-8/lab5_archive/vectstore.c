/**
 * @file vectstore.c
 * @brief methods for storing vectors
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 *
 */
#include "vectstore.h"
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10

int size = 0;
Vect storage[10];

void assignVect(Vect src, Vect dst) {
  // if destination exists, replace it
  if (findVect(dst.name) < MAX_SIZE) {
    replaceVect(src, dst);
    // else, add a new with the same name
  } else {
    insertVect(copyVect(src, dst));
  }
}

Vect copyVect(Vect src, Vect dst) {
  Vect vect;
  strcpy(vect.name, dst.name);
  vect.x = src.x;
  vect.y = src.y;
  vect.z = src.z;
  return vect;
}

Vect getVect(const char *name) {
  // get vect location in array
  int loc = findVect(name);
  // if exists (in bounds), return vect at location
  if (loc < MAX_SIZE) {
    return storage[loc];
    // if out of bounds, return empty vect at next available location
  } else {
    Vect vect;
    strcpy(vect.name, name);
    insertVect(vect);
    return vect;
  }
}

int findVect(const char *name) {
  // iterate through array
  for (int i = 0; i < size; i++) {
    // if names match, give it
    if (!strcmp(name, storage[i].name)) {
      return i;
    }
  }
  // if not found, return max size
  return MAX_SIZE;
}

void insertVect(Vect src) {
  // if in bounds, add item to array
  if (size < MAX_SIZE) {
    storage[size++] = src;
  } else {
    printf("You are at maximum capacity for vectors. Please clear storage or "
           "replace a vector.");
  }
}

void replaceVect(Vect src, Vect dst) {
  // get array location
  int loc = findVect(dst.name);
  // replace item at location
  storage[loc] = src;
}

void clear() {
  // clear memory
  memset(storage, 0, sizeof(storage));
  // reset size
  size = 0;
}

void list() {
  // iterate through storage and print
  for (int i = 0; i < size; i++) {
    displayVect(storage[i]);
  }
}

void display(const char *name) {
  // get the vect
  if (findVect(name) < MAX_SIZE) {
    // print the vect
    displayVect(getVect(name));
  } else {
    printf("Vect %s not found.", name);
  }
}

void displayVect(Vect vect) {
  // print struct elements
  printf("%s: %d, %d, %d\n", vect.name, vect.x, vect.y, vect.z);
}