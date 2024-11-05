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
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

int current_max = INITIAL_SIZE;
int size = 0;
Vect *storage;

void init() {
  atexit(cleanup_storage);
  storage = malloc(INITIAL_SIZE * sizeof(Vect));
}

void cleanup_storage() { free(storage); }

void assignVect(Vect src, Vect dst) {
  // if destination exists, replace it
  if (findVect(dst.name) < current_max) {
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
  if (loc < current_max) {
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
  return current_max;
}

void insertVect(Vect src) {
  // if in bounds, add item to array
  if (size < current_max) {
    storage[size++] = src;
  } else {
    current_max = current_max * 2;
    storage = realloc(storage, current_max * sizeof(Vect));
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
  free(storage);
  init();
  // reset size
  size = 0;
}

void list() {
  // iterate through storage and print
  for (int i = 0; i < size; i++) {
    printf("%d | ", i + 1);
    displayVect(storage[i]);
  }
}

void display(const char *name) {
  // get the vect
  if (findVect(name) < current_max) {
    // print the vect
    displayVect(getVect(name));
  } else {
    printf("Vect %s not found.", name);
  }
}

void displayVect(Vect vect) {
  // print struct elements
  printf("%5s: %3d, %3d, %3d\n", vect.name, vect.x, vect.y, vect.z);
}

Vect vectEquals(const char *name, int x, int y, int z) {
  // copies a vect by its parameters
  Vect vect;
  strcpy(vect.name, name);
  vect.x = x;
  vect.y = y;
  vect.z = z;
  return vect;
}