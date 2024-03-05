#include "myShell.h"
#include "myFunction.h"

int main()
{
    welcome();

    while (1)
    {
        getLocation();
        char *input = getInputFromUser();
        // cp\0<file>\0<file>\0
        // cp <file> <file>\0
        // [cp, <file>, <file> ]
        // [input,input+3,input+10]

        char **arg = splitArgument(input);
        int i = 0;
        while (*(arg + i) != NULL)
        {
            puts(arg[i]);
            i++;
        }

        if (strcmp(input, "exit") == 0)
        {
            free(arg);
            free(input);
            puts("log out");
            break;
        }



        
        free(arg);
        free(input);
    }
    return 0;
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