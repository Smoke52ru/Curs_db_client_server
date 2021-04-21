#include <string.h>
#include <stdio.h>
#include <ctype.h>

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
    if (sizep != NULL){
        *sizep = i;
    }
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
    if (sizep != NULL){
        *sizep = i;
    }
    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}



//Проверка отправляемой строки на валидность
int handler(char *data) {

    //Перевод команды в верхний регистр
    for (int i = 0; i < 2; i++){
        *(data + i) = toupper(*(data + i));;
    }
    

    //Команда == OP
    if (strncmp(data, "OP ", 3) == 0){
        fprintf(stdout,"cmd is %s\n","OP");
        if (wordhandler(data+3,NULL,"DBName") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == RD
    } else if(strncmp(data, "RD ", 3) == 0){
        fprintf(stdout,"cmd is %s\n","RD");
        if (numhandler(data+3,NULL,"Index") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == WR
    } else if(strncmp(data, "WR ", 3) == 0){
        fprintf(stdout,"cmd is %s\n","WR");
        if (numhandler(data+3,NULL,"Index") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == AD
    } else if(strncmp(data, "AD ", 3) == 0){
        fprintf(stdout,"cmd is %s\n","AD");

        return 0; 

    //Команда == DL
    } else if(strncmp(data, "DL ", 3) == 0){
        fprintf(stdout,"cmd is %s\n","DL");
        if (numhandler(data+3,NULL,"Index") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }
    }

    //Исключение

    fprintf(stderr,"ERROR: Request is incorrect\n");
    return 1;
    
/*
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
*/
}

