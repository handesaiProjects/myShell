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


void cp(char **arguments) {
    char srcPath[BUFF_SIZE] = "";
    char destPath[BUFF_SIZE] = "";
    int i = 1;

    // Handle source path with potential spaces
    if (arguments[i][0] == '\"') {
        // Concatenate all parts of the path until we find an argument that ends with a quote
        while (arguments[i] != NULL && arguments[i][strlen(arguments[i]) - 1] != '\"') {
            strcat(srcPath, arguments[i]);
            strcat(srcPath, " "); // Add space between parts
            i++;
        }
        // Add the last part of the path (the one that ends with a quote)
        if (arguments[i] != NULL) {
            strcat(srcPath, arguments[i]);
            // Remove the quotes from the beginning and the end of the path
            memmove(srcPath, srcPath + 1, strlen(srcPath));
            srcPath[strlen(srcPath) - 1] = '\0';
        }
        i++; // Move to next argument
    } else {
        strcpy(srcPath, arguments[i++]);
    }

    // Handle destination path with potential spaces
    if (arguments[i][0] == '\"') {
        while (arguments[i] != NULL && arguments[i][strlen(arguments[i]) - 1] != '\"') {
            strcat(destPath, arguments[i]);
            strcat(destPath, " "); // Add space between parts
            i++;
        }
        if (arguments[i] != NULL) {
            strcat(destPath, arguments[i]);
            // Remove the quotes from the beginning and the end of the path
            memmove(destPath, destPath + 1, strlen(destPath));
            destPath[strlen(destPath) - 1] = '\0';
        }
    } else {
        strcpy(destPath, arguments[i]);
    }

    // Check if the source and destination are the same
    if (strcmp(srcPath, destPath) == 0) {
        printf("cp: '%s' and '%s' are the same file\n", srcPath, destPath);
        return;
    }

    // Attempt to open the source file
    FILE *src = fopen(srcPath, "r");
    if (src == NULL) {
        printf("cp: cannot open '%s' for reading: No such file or directory\n", srcPath);
        return;
    }

    // Attempt to open/create the destination file
    FILE *dest = fopen(destPath, "w");
    if (dest == NULL) {
        fclose(src);
        printf("cp: cannot create '%s': No such file or directory\n", destPath);
        return;
    }

    // Copy the content from source to destination
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    // Close the files
    fclose(src);
    fclose(dest);
    printf("File '%s' successfully copied to '%s'\n", srcPath, destPath);
}

void delete(char **path)
{
    if (unlink(path[1]) != 0)
        printf("-myShell: path: %s: No such file or directory\n", path[1]);
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


// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות
