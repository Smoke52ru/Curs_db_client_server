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

//Обработка числа
int numhandler(char* number, int* size, char* wordname){
    char* ptr = number;
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

    if (size != NULL){
        *size = i;
    } else {
        fprintf(stderr, "ERROR: Empty [%s]\n", wordname);
        *size = 0;
        return 1;
    }

    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}

//Обработка слова
int wordhandler(char* word, int* size, char* wordname){
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

    if (size != NULL){
        *size = i;
    } else {
        fprintf(stderr, "ERROR: Empty [%s]\n", wordname);
        *size = 0;
        return 1;
    }

    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}

// Обработка данных БЕЗ команды 
int datahandler(char* data, int* size){
    char* ptr = data;
    int count = 1, wordsize = 0, datasize = 0;

    if (numhandler(data, &wordsize,"Index")) return 1;
    datasize += wordsize;
    while ((*ptr != '\0') && (count < 2)){
        ptr += wordsize;
        if (wordhandler(ptr,&wordsize, "Data")) return 1;
        datasize += wordsize;
        count++;
    }
    if (*ptr == '\0') {
        fprintf(stderr,"ERROR: Unexpected end of data (word = %d)", );
        return 1;
    }
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
        ///
        ///
        //
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
    
}

