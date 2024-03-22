#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* reconstructString(char **arguments, int startIndex, int endIndex);
void handleRedirection(char **arguments, int redirectIndex, void (*redirectFunction)(char **));