/**
 * @file vectstore.h
 * @brief defines methods for storing vects
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 *
 */
#include "Vect.h"

void assignVect(Vect src, Vect dst);

Vect copyVect(Vect src, Vect dst);

Vect getVect(const char *name);

int findVect(const char *name);

void insertVect(Vect src);

void replaceVect(Vect src, Vect dst);

void clear();

void list();

void display(const char *name);

void displayVect(Vect vect);