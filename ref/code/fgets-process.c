#include <stdio.h>
#include <string.h>

void process_token(const char *token) {
    printf("Token: %s\n", token);
}

int main() {
    char line[100];
    char *token;
    const char delimiters[] = " \t\n"; // Delimiters for strtok

    printf("Enter a line of text: ");
    if (fgets(line, sizeof(line), stdin) != NULL) {
        // Get the first token
        token = strtok(line, delimiters);

        // Process each token
        while (token != NULL) {
            process_token(token);
            token = strtok(NULL, delimiters);
        }
    }

    return 0;
}
