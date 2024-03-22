#include "utilFunctions.h"

char* reconstructString(char **arguments, int startIndex, int endIndex) {
    int length = 0;
    for (int i = startIndex; i < endIndex; i++) {
        length += strlen(arguments[i]) + 1; // +1 for space or null terminator
    }
    char *result = malloc(length);
    if (result) {
        result[0] = '\0'; // Initialize to empty string
        for (int i = startIndex; i < endIndex; i++) {
            strcat(result, arguments[i]);
            if (i < endIndex - 1) strcat(result, " "); // Add space between arguments
        }
    }
    return result;
}

void handleRedirection(char **arguments, int redirectIndex, void (*redirectFunction)(char **)) {
    if (arguments[1] != NULL && arguments[redirectIndex + 1] != NULL) {
        char *reconstructedString = reconstructString(arguments, 1, redirectIndex);
        if (reconstructedString) {
            char *argsForRedirect[] = {NULL, reconstructedString, arguments[redirectIndex + 1], NULL};
            redirectFunction(argsForRedirect);
            free(reconstructedString);
        }
    } else {
        printf("Syntax error near redirection\n");
    }
}