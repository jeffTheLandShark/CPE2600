#include <stdio.h>
#include <string.h>

int main() {
    char line[100]; // Buffer for reading lines
    char *token;
    const char delimiters[] = " \t\n"; // Delimiters for tokenization

    printf("Enter a line of text: ");

    // Read a line of input using fgets
    if (fgets(line, sizeof(line), stdin) != NULL) {

        // Tokenize the line using strtok
        token = strtok(line, delimiters);
        while (token != NULL) {
            printf("Token: %s\n", token);
            token = strtok(NULL, delimiters);
        }
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
