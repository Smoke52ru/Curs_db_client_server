#include <string.h>
#include <stdio.h>

int iseng(char ch){
    return (((ch >= 'a') && (ch <='z')) || ((ch >= 'A') && (ch <='Z')));
}
int isdig(char ch){
    return ((ch >= '0') && (ch <='9'));
}
int isseparator(char* ch, char* separators){
    char* ptr = separators;
    while(*ptr !='\0'){
        if (*ch == *ptr)
            return 1;
        ptr++;
    }
    return 0;
}

int numhandler(char* word, int* sizep, char* wordname){
    char* ptr = word;
    int i = 0;
    while ((*ptr != ' ') && (*ptr != '\0')) {
        if (isdig(*ptr)){ //  Цифра
            ptr++;
            i++;
        } else {
            fprintf(stderr, "ERROR: Invalid [%s]\n", wordname);
            return 1;
        }
    }
    *sizep = i;
    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}

int wordhandler(char* word, int* sizep, char* wordname){
    char* ptr = word;
    int i = 0;
    while ((*ptr != ' ') && (*ptr != '\0')) {
        if (iseng(*ptr)){ //  Буква
            ptr++;
            i++;
        } else {
            fprintf(stderr, "ERROR: Invalid [%s]\n", wordname);
            return 1;
        }
    }
    *sizep = i;
    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}


// Прототип (TODO поддержка команд)
int handler(char *data) {

    char *str[5] = {"OP", "RD", "WR", "AD", "DL"}; // Набор команд
    int cmd_num, cur_char, size;

    for (cmd_num = 0; cmd_num < 5; cmd_num++) {
        if (strncmp(data, str[cmd_num], 2) == 0) {
            cur_char = 3;
            if (numhandler(&data[cur_char], &size, "Index")){
                return 1;
            }
            cur_char += size+1;

            if(wordhandler(&data[cur_char], &size, "Name")){
                return 1;
            }
            cur_char += size+1;

            if(wordhandler(&data[cur_char], &size, "Surname")){
                return 1;
            }
            return 0;
        } else {
            continue;
        }
    }
    fprintf(stderr,"ERROR: Request is incorrect\n");
    return 1;
}

