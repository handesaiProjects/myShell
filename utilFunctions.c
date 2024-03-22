#include "utilFunctions.h"

// Function to reconstruct a string from an array of strings, given start and end indices.
char* reconstructString(char **arguments, int startIndex, int endIndex) {
    int length = 0;
    // Calculate the total length needed for the reconstructed string.
    for (int i = startIndex; i < endIndex; i++) {
        length += strlen(arguments[i]) + 1; // +1 for space or null terminator
    }
    // Allocate memory for the result string.
    char *result = malloc(length);
    if (result) {
        result[0] = '\0'; // Initialize to empty string
        // Concatenate each argument into the result string.
        for (int i = startIndex; i < endIndex; i++) {
            strcat(result, arguments[i]);
            // Add a space between arguments, but not after the last one.
            if (i < endIndex - 1) strcat(result, " ");
        }
    }
    return result;
}

// Function to handle redirection in command line arguments.
void handleRedirection(char **arguments, int redirectIndex, void (*redirectFunction)(char **)) {
    // Ensure there are arguments before and after the redirection symbol.
    if (arguments[1] != NULL && arguments[redirectIndex + 1] != NULL) {
        // Reconstruct the string from arguments to pass to the redirection function.
        char *reconstructedString = reconstructString(arguments, 1, redirectIndex);
        if (reconstructedString) {
            // Prepare the arguments for the redirection function.
            char *argsForRedirect[] = {NULL, reconstructedString, arguments[redirectIndex + 1], NULL};
            // Call the redirection function with the prepared arguments.
            redirectFunction(argsForRedirect);
            // Free the dynamically allocated reconstructed string.
            free(reconstructedString);
        }
    } else {
        // Print an error message if the syntax around redirection is incorrect.
        printf("Syntax error near redirection\n");
    }
}