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
    int inQuotes = 0; // Flag to check if we are inside quotes

    for (int i = 0; i <= length; i++) {
        // Toggle inQuotes flag if a quote is found
        if (str[i] == '\"') {
            inQuotes = !inQuotes;
            if (inQuotes) {
                // If we're starting a quoted word, move start past the quote
                start = i + 1;
            } else {
                // If we're ending a quoted word, process it without including the ending quote
                int wordLength = i - start;
                if (wordLength > 0) {
                    arguments[index] = (char *)malloc((wordLength + 1) * sizeof(char));
                    memcpy(arguments[index], &str[start], wordLength);
                    arguments[index][wordLength] = '\0'; // Null-terminate the word
                    index++;
                    size++;
                    arguments = (char **)realloc(arguments, size * sizeof(char *));
                }
                start = i + 1; // Move start past the quote for the next word
            }
            continue; // Skip the quote processing below
        }

        // Check for end of a word or end of the string, respecting quotes
        if ((str[i] == ' ' && !inQuotes) || str[i] == '\0') {
            int wordLength = i - start;
            if (wordLength > 0) {
                arguments[index] = (char *)malloc((wordLength + 1) * sizeof(char));
                memcpy(arguments[index], &str[start], wordLength);
                arguments[index][wordLength] = '\0'; // Null-terminate the word
                index++;
                size++;
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
    if (arg[1] != NULL && chdir(arg[1]) != 0) {
        printf("-myShell: cd: %s: No such file or directory\n", arg[1]);
    }
}


void cp(char **arguments) {
    if (strcmp(arguments[1], arguments[2]) == 0) {
        printf("cp: '%s' and '%s' are the same file\n", arguments[1], arguments[2]);
        return;
    }

    FILE *src = fopen(arguments[1], "r");
    if (src == NULL) {
        printf("cp: cannot open '%s' for reading: No such file or directory\n", arguments[1]);
        return;
    }

    FILE *dest = fopen(arguments[2], "w");
    if (dest == NULL) {
        fclose(src);
        printf("cp: cannot create '%s': No such file or directory\n", arguments[2]);
        return;
    }

    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File '%s' successfully copied to '%s'\n", arguments[1], arguments[2]);
}

void delete(char **arg) {
    if (unlink(arg[1]) != 0)
        printf("-myShell: delete: %s: No such file or directory\n", arg[1]);
}

void systemCall(char **arg)
{

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arg[0], arg) == -1)
        exit(1);
}
void mypipe(char **argv1, char **argv2)
{
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            /* stdout now goes to pipe */
            /* child process does command */
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
}


void move(char **args) {
    // Check if the correct number of arguments are passed
    if (args[1] == NULL || args[2] == NULL) {
        printf("move: missing file operand\n");
        return;
    }

    // Copy the file to the new location
    cp(args);

    // If the copy is successful, delete the original file
    // Note: It's important to check if the copy was successful to avoid data loss
    FILE *file = fopen(args[1], "r");
    if (file != NULL) {
        fclose(file);
        delete(args);
    } else {
        printf("move: failed to copy '%s' to '%s'\n", args[1], args[2]);
    }
}

// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות
