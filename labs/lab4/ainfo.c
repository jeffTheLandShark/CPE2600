/**
* @file ainfo.c
* @brief contains funcations for printing ascii tables and values
*
* Course: CPE2600
* Section: 121
* Assignment: Lab 4
* Name: Leigh Goetsch
*
*/

#include <stdio.h>
#include <string.h>

#define ASCII_TABLE {"NUL","SOH", "STX","ETX","EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SS", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN" , "EM", "SUB", "ESC",  "FS", "GS", "RS", "US", " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?", "@", "A",  "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "]", "\\", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "{", "|", "}", "~", "DEL"}
#define MAX_CHARS 128

const char *ascii[MAX_CHARS] = ASCII_TABLE;

void printAscii(int columns) {
    // calculate rows
    int rows = MAX_CHARS / columns;
    // check for overflow + add a row if true
    if (MAX_CHARS % columns != 0){
        rows++;
    }

    // print top row
    char empty[] = "";
    for (int i = 0; i < columns; i++) {
        printf("Dec Hex %5s", empty);
    }
    printf("\n");

    // print rows of characters using a nested for loop
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns; j++) {
            int location = (j * rows) + i ;
            if (location < MAX_CHARS) {
                printf("%3d %3x %3s  ", location, location, ascii[location]);
            }
        }
        printf("\n");
    }
}

void printAsciiDefault() {
    // default to 8 columns
    printAscii(8);
}

void binaryConversion(int asciiChar, char binVal[]){
    // division method for converting decimal to binary
    int remain;
    for (int i = 7; i >= 0; i--){
        remain = asciiChar % 2;
        asciiChar = asciiChar / 2;
        // convert int to char before adding
        binVal[i] = remain + '0';
    }
}

void printAsciiChar(char asciiChar) {
    // get value for char
    int asciiVal = (int)asciiChar;
    // create binary string
    char binVal[8];
    binaryConversion(asciiVal, binVal);
    // print result
    printf("ASCII Value for '%c':\nDEC HEX BIN\n%3d %3x %8s\n", asciiChar, asciiVal, asciiVal, binVal);
}


void printHelpText() {
    printf("Welcome to ACSCII Printer\n\nDefault:\n\tPrint the ASCII table to 8 columns\n\n-c <num columns>\n\tPrint the ASCII table to <num columns> columns\n\n<character>\n\nprint ASCII value <character> in decimal, hex, and 8-bit binary\n");
}

void printErrorText() {
    printf("Please choose an integer between 1 and 9 for column size.\n");
}