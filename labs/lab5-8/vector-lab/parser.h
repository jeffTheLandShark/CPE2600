/**
 * @file parser.h
 * @brief contains methods for parsing cmd inputs
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 */
#include "Vect.h"

#include <stdbool.h>

#define MAX_TOKENS 5
#define MAX_CHARS 100

int parse();

void invalidMsg();

int parseCmd(const char *cmd);

void parseMath(char tokens[MAX_TOKENS][MAX_CHARS], bool isAssigned);

Vect vectEquals(const char *name, int x, int y, int z);