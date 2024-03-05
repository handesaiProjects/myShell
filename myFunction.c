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



// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות