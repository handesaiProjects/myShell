#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);
        char **arguments = splitArgument(input);

        // Check for piping
        int piping = -1;
        int appendToFile = -1; // Index for ">>"
        for (int i = 0; arguments[i] != NULL; i++) {
            if (strcmp(arguments[i], "|") == 0) {
                piping = i;
                break;
            } else if (strcmp(arguments[i], ">>") == 0) {
                appendToFile = i;
                break;
            }
        }

        if (piping != -1) {
            arguments[piping] = NULL; // Split the arguments array into two NULL-terminated arrays
            char **argv1 = arguments;
            char **argv2 = arguments + piping + 1;
            mypipe(argv1, argv2);
            wait(NULL);
        } else if (appendToFile != -1 && strcmp(arguments[0], "echo") == 0) {
            // Ensure there is a command before ">>" and a file path after
            if (arguments[1] != NULL && arguments[appendToFile + 1] != NULL) {
                // Reconstruct the string to append from the arguments before ">>"
                char *toAppend = NULL;
                int length = 0;
                for (int i = 1; i < appendToFile; i++) { // Start from 1 to skip "echo"
                    length += strlen(arguments[i]) + 1; // +1 for space or null terminator
                }
                toAppend = malloc(length);
                if (toAppend) {
                    toAppend[0] = '\0'; // Initialize to empty string
                    for (int i = 1; i < appendToFile; i++) { // Start from 1 to skip "echo"
                        strcat(toAppend, arguments[i]);
                        if (i < appendToFile - 1) strcat(toAppend, " "); // Add space between arguments
                    }
                    // Call echoppend with the reconstructed string and the file path
                    char *argsForEchoppend[] = {NULL, toAppend, arguments[appendToFile + 1], NULL};
                    echoppend(argsForEchoppend);
                    free(toAppend);
                }
            } else {
                printf("Syntax error near '>>'\n");
            }
        } else if (strcmp(arguments[0], "echo") == 0)
            echo(arguments);
        else if (strcmp(arguments[0], "cd") == 0)
            cd(arguments);
        else if (strcmp(arguments[0], "cp") == 0)
            cp(arguments);
        else if (strcmp(arguments[0], "delete") == 0)
            delete(arguments);
        else if (strcmp(arguments[0], "move") == 0)
            move(arguments);
        else {
            systemCall(arguments);
            wait(NULL);
        }
        free(arguments);
        free(input);
    }
    return 1;
}


void welcome()
{
    const char* welcome_message[] = {
        "                     aSPY//YASa",
        "              apyyyyCY//////////YCa       |",
        "             sY//////YSpcs  scpCY//Pp     | Welcome to myShell",
        "  ayp ayyyyyyySCP//Pp           syY//C    | Version 1.0",
        "  AYAsAYYYYYYYY///Ps              cY//S   |",
        "          pCCCCY//p          cSSps y//Y   | https://github.com/handesaiProjects/myShell",
        "          SPPPP///a          pP///AC//Y   |",
        "               A//A            cyP////C   | Have fun?",
        "               p///Ac            sC///a   |",
        "               P////YCpc           A//A   | The best shell you never used",
        "        scccccp///pSP///p          p//Y   | and you never will",
        "       sY/////////y  caa           S//P   |                      -- unknown",
        "        cayCyayP//Ya              pY/Ya   |",
        "         sY/PsY////YCc          aC//Yp  ",
        "          sc  sccaCY//PCypaapyCP//YSs   ",
        "                   spCPY//////YPSps     ",
        "                        ccaacs          "
    };

    // Loop through welcome messages and print them one at a time
    for (size_t i = 0; i < sizeof(welcome_message)/sizeof(*welcome_message); ++i) {
        puts(welcome_message[i]);
    }
}