#include "myFunction.h"


char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size * sizeof(char));
    }
    *(str + index) = '\0';

    return str;
}
// עליכם לממש את הפונקציה strtok כלומר שהפונקציה הנ"ל תבצע בדיוק אותו הדבר רק בלי השימוש בפונקציה strtok
char **splitArgument(char *str) {
    int size = 1; // Start with size 1 to account for NULL at the end
    int index = 0;
    int start = 0; // Starting index of a word
    char **arguments = (char **)malloc(size * sizeof(char *));
    int length = strlen(str);
    
    for (int i = 0; i <= length; i++) {
        // Check for end of a word or end of the string
        if (str[i] == ' ' || str[i] == '\0') {
            // Calculate word lengthchar **splitArgument(char *str)
{
    // str = cp file file file
    //[cp,file,file,file,NULL]
    char *subStr;
    int size = 2;
    int index = 0;
    subStr = strtok(str, " ");
    char **argumnts = (char **)malloc(size * sizeof(char *));
    *(argumnts + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL)
    {
        size++;
        index++;
        *(argumnts + index) = subStr;
        argumnts = (char **)realloc(argumnts,size * sizeof(char *));
    }
    *(argumnts + (index+1)) = NULL;

    return argumnts;
}
            int wordLength = i - start;
            if (wordLength > 0) {
                // Allocate memory for the new word
                arguments[index] = (char *)malloc((wordLength + 1) * sizeof(char));
                memcpy(arguments[index], &str[start], wordLength);
                arguments[index][wordLength] = '\0'; // Null-terminate the word
                index++;
                size++;
                // Reallocate memory for the arguments array to accommodate the new word
                arguments = (char **)realloc(arguments, size * sizeof(char *));
            }
            start = i + 1; // Move start to the next word
        }
    }
    arguments[index] = NULL; // Null-terminate the array of words

    return arguments;
}

// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.
void getLocation() {
    char location[BUFF_SIZE];
    char hostname[BUFF_SIZE];
    char* username = getenv("USER");

    if (username == NULL) {
        puts("Error retrieving username");
        return;
    }

    if (getcwd(location, BUFF_SIZE) == NULL || gethostname(hostname, BUFF_SIZE) != 0) {
        puts("Error retrieving location or hostname");
    } else {
            green();
            printf("%s@%s", username, hostname);
            reset();
            printf("%s", ":");
            blue();
            printf("~%s", location);
            reset();
            printf("%s", "$ ");
            reset();


    }
}

void logout(char *input) {
    // Trim leading spaces
    while(isspace((unsigned char)*input)) input++;

    // Check if the first word is "exit"
    if (strncmp(input, "exit", 4) == 0) {
        char *next_char = input + 4;

        // Check if "exit" is followed by spaces or end of string
        if (*next_char == '\0' || isspace((unsigned char)*next_char)) {
            // If there's more text after "exit", ensure it's only spaces
            while(*next_char != '\0') {
                if (!isspace((unsigned char)*next_char)) {
                    printf("Invalid command. To exit, type 'exit' without additional text.\n");
                    free(input);
                    return;
                }
                next_char++;
            }

            // If only "exit" or "exit" followed by spaces, perform logout
            free(input);
            puts("Logging out...");
            exit(EXIT_SUCCESS);
        }
    }

    // If input is not "exit" or "exit" with spaces, do not exit
    printf("Invalid command. To exit, type 'exit' without additional text.\n");
    free(input);
}


void echo(char **arg)
{
    // int i = 1;

    // while (arg[i] != NULL)
    //     printf("%s ", arg[i++]);
    // while (*(arg + i) != NULL)
    //     printf("%s ", *(arg + i++));
    // while (*(arg + i))
    // {
    //     printf("%s ", *(arg + i));
    //     i++;
    // }
    while (*(++arg))
        printf("%s ", *arg);
    puts("");
}
// יש לטפל במקרים בהם מקבלים נתיב המכיל רווחים, תזכרו - נתיב כזה צריך להיות מסומן בגרשיים ולכן יש לוודא זאת ואם הוא אכן כזה
// שמכיל סוגריים אז יש לבנות מחרוזת חדשה שאותה יש לשלוח לפונקציה שמשנה נתיב לתהליך.
void cd(char **arg) {
    // If the first argument starts with a quote, we need to handle spaces in the path.
    if (arg[1][0] == '\"') {
        char path[BUFF_SIZE] = "";
        int i = 1;
        // Concatenate all parts of the path until we find an argument that ends with a quote.
        while (arg[i] != NULL && arg[i][strlen(arg[i]) - 1] != '\"') {
            strcat(path, arg[i]);
            strcat(path, " ");  // Add space between parts
            i++;
        }
        // Add the last part of the path (the one that ends with a quote).
        if (arg[i] != NULL) {
            strcat(path, arg[i]);
        }
        // Remove the quotes from the beginning and the end of the path.
        memmove(path, path+1, strlen(path));
        path[strlen(path) - 1] = '\0';
        // Change the directory
        if (chdir(path) != 0) {
            printf("-myShell: cd: %s: No such file or directory\n", path);
        }
    } else {
        // Handle normal path (without spaces or quotes).
        if (arg[1] != NULL && chdir(arg[1]) != 0) {
            printf("-myShell: cd: %s: No such file or directory\n", arg[1]);
        }
    }
}


void cp(char **arguments)
{
    char ch;
    FILE *src, *des;
    if ((src = fopen(arguments[1], "r")) == NULL)
    {
        puts("Erorr");
        return;
    }
    if ((des = fopen(arguments[2], "w")) == NULL)
    {
        puts("Erorr");
        fclose(src);
        return;
    }

    while((ch=fgetc(src))!=EOF){
        fputc(ch,des);
    }
    fclose(src);
    fclose(des);
}
// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות


// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות