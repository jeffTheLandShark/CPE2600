/**
 * @file parser.c
 * @brief parses input commands to determine which function to call
 *
 * Course: CPE2600
 * Section: 121
 * Assignment: Lab 5
 * Name: Leigh Goetsch
 *
 */

#include "parser.h"
#include "csvparser.h"
#include "vectmath.h"
#include "vectstore.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse() {
  char buffer[MAX_CHARS] = {};
  char tokens[MAX_TOKENS][MAX_CHARS] = {};
  int counter = 0;
  int cmd;

  // Use fgets correctly to read a full line
  if (fgets(buffer, MAX_CHARS, stdin) == NULL) {
    printf("Error reading input.\n");
    return 0;
  }

  // remove trailing newline if present
  buffer[strcspn(buffer, "\n")] = '\0';

  // load first token
  char *token = strtok(buffer, " ");

  // get token loop until all out
  while (token != NULL) {
    // don't overfill the tokens array
    if (counter >= MAX_TOKENS) {
      invalidMsg();
      return 1;
    }
    // save token to tokens array
    strcpy(tokens[counter], token);
    // printf("token[%d]: %s\n", counter, tokens[counter]);
    counter++;
    // next token
    token = strtok(NULL, " ");
  }

  bool isassignment = counter > 2 && !strcmp(tokens[1], "=");
  // only accept math commands that are assignments
  // create a different way to do it

  int x = 0, y = 0, z = 0;
  // choose bahaviour based on number of tokens
  switch (counter) {
  case 1: // single command
    cmd = parseCmd(tokens[0]);
    return cmd;
  case 2:
    if (!strcmp(tokens[0], "load")) {
      parse_csv(tokens[1]);
      list();
    } else {
      invalidMsg();
    }
    break;

  case 3: // a = x
          // assign a digit
    if (isassignment) {
      if (isdigit(*tokens[2])) {
        x = strtol(tokens[2], NULL, 10);
        Vect vect = vectEquals(tokens[0], x, y, z);
        assignVect(vect, getVect(tokens[0]));
      } else {
        // copy and assign a vect
        Vect src = getVect(tokens[2]);
        Vect dst = getVect(tokens[0]);
        assignVect(copyVect(src, dst), dst);
      }
      display(tokens[0]);

    } else {
      // there is no assignment
      parseMath(tokens, false);
    }
    break;

  case 4: // a = x y
    // assignments should be scalar
    if (!isdigit(*tokens[3]) || !isdigit(*tokens[2])) {
      invalidMsg();
      break;
    }
    x = strtol(tokens[2], NULL, 10);
    y = strtol(tokens[3], NULL, 10);
    Vect vect = vectEquals(tokens[0], x, y, z);
    assignVect(vect, getVect(tokens[0]));
    display(tokens[0]);
    break;

  case 5: // a = x y z or a = x op y
    parseMath(tokens, true);
    break;

  default: // no commands with 2 tokens
    printf("Invalid number of arguments.\n");
    invalidMsg();
  }
  return 1;
}

void invalidMsg() { printf("Invalid command. Please try again.\n"); }

int parseCmd(const char *cmd) {
  // parse one word cmds
  if (!strcasecmp(cmd, "quit")) {
    return 0;
  }
  if (!strcasecmp(cmd, "list")) {
    list();
  } else if (!strcasecmp(cmd, "clear")) {
    clear();
  } else {
    display(cmd);
  }
  return 1;
}

void parseMath(char tokens[MAX_TOKENS][MAX_CHARS], bool isAssigned) {
  int name, a, op, b;
  // if assigned, there are 5 tokens (name = a op b)
  // if not assigned, there are three tokens (a op b)
  if (isAssigned) {
    name = 0, a = 2, op = 3, b = 4;
  } else {
    name = 0, a = 0, op = 1, b = 2;
  }

  // get the operation char
  char *operation = tokens[op];
  // set integer default values
  int x = 0, y = 0;
  // determine if operation or assignment
  bool isVectOp = !isdigit(*tokens[a]);

  // if not a vect op, pull the integers
  if (!isVectOp) {
    x = strtol(tokens[a], NULL, 10);
    y = strtol(tokens[b], NULL, 10);
  }

  Vect src;
  // 3d vector assignment
  if (isdigit(*tokens[op]) && isAssigned) {
    x = strtol(tokens[a], NULL, 10);
    y = strtol(tokens[op], NULL, 10);
    int z = strtol(tokens[b], NULL, 10);
    src = vectEquals(tokens[name], x, y, z);
    // add operation
  } else if (!strcasecmp(operation, "+")) {
    if (isVectOp) {
      src = addVect(tokens[name], getVect(tokens[a]), getVect(tokens[b]));
    } else {
      src = addScalar(tokens[name], x, y);
    }
    // subtract operation
  } else if (!strcasecmp(operation, "-")) {
    if (isVectOp) {
      src = subtractVect(tokens[name], getVect(tokens[a]), getVect(tokens[b]));
    } else {
      src = subtractScalar(tokens[name], x, y);
    }
    // dot product operation
  } else if (!strcasecmp(operation, ".")) {
    if (isVectOp) {
      src =
          dotProductVect(tokens[name], getVect(tokens[a]), getVect(tokens[b]));
    } else {
      printf("This is not a viable operation.\n");
      invalidMsg();
      return;
    }
    // cross product operation
  } else if (!strcasecmp(operation, "X")) {
    if (isVectOp) {
      src = crossProduct(tokens[name], getVect(tokens[a]), getVect(tokens[b]));
    } else {
      printf("This is not a viable operation.\n");
      invalidMsg();
      return;
    }
    // scalar multiplication operation
  } else if (!strcasecmp(operation, "*")) {
    if (isVectOp) {
      int scalar = strtol(tokens[b], NULL, 10);
      src = scalarVectProduct(tokens[name], getVect(tokens[a]), scalar);
    } else {
      src = scalarProduct(tokens[name], x, y);
    }
    // If something else is there (not an operation symbol or digit),
    // it is invalid
  } else {
    invalidMsg();
    return;
  }
  // if the result is assigned, save it to the array
  if (isAssigned) {
    assignVect(src, getVect(tokens[name]));
  }
  displayVect(src);
}