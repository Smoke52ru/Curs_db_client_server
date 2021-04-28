#include <string.h>
#include <stdio.h>
#include <ctype.h>

int iseng(char ch){
    return (((ch >= 'a') && (ch <='z')) || ((ch >= 'A') && (ch <='Z')));
}
int isdig(char ch){
    return ((ch >= '0') && (ch <='9'));
}

/* Не используется в коде
int isseparator(char* ch, char* separators){
    char* ptr = separators;
    while(*ptr !='\0'){
        if (*ch == *ptr)
            return 1;
        ptr++;
    }
    return 0;
}
*/

//Обработка числа
int numhandler(char* number, int* size, char* wordname){
    char* ptr = number;
    int i = 0;
    if (size != NULL) { *size = 0;}
    
    while ((*ptr != ' ') && (*ptr != '\0')) {
        if (isdig(*ptr)){ //  Цифра
            ptr++;
            i++;
        } else {
            fprintf(stderr, "ERROR: Invalid [%s]\n", wordname);
            return 1;
        }
    }

    if (i == 0) { //Если слово пустое
        fprintf(stderr, "ERROR: Empty [%s]\n", wordname);
        return 1;
    }
    if (size != NULL){ // Если адрес не заглушка
        *size = i;
    } 

    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}

//Обработка слова
int wordhandler(char* word, int* size, char* wordname){
    char* ptr = word;
    int i = 0;
    if (size != NULL) { // Обнуление размера
        *size = 0;
    }

    while ((*ptr != ' ') && (*ptr != '\0')) {
        if (iseng(*ptr)){ //  Буква
            ptr++;
            i++;
        } else {
            fprintf(stderr, "ERROR: Invalid [%s]\n", wordname);
            return 1;
        }
    }

    if (i == 0) { //Если слово пустое
        fprintf(stderr, "ERROR: Empty [%s]\n", wordname);
        return 1;
    }
    if (size != NULL){ // Если адрес не заглушка
        *size = i;
    } 

    fprintf(stdout, "[%s] is correct\n", wordname);
    return 0;
}

// Обработка данных БЕЗ команды 
int datahandler(char* data, int* size){
    char* ptr = data;
    int count = 0, wordsize = 0, datasize = 0;
    if (size != NULL) { // Обнуление размера
        *size = 0;
    }

    if (numhandler(data, &wordsize,"Index")) return 1;
    datasize += wordsize;
    ptr += wordsize;

    while ((*ptr != '\0') && (count <= 2)){ // Пока обработаны не все слова И не нуль терминатор
        count++;
        if (wordsize == 0) {
            fprintf(stderr,"ERROR: Empty word %d\n", count-1);
            return 1;
        }
        wordsize = 0;
        if (wordhandler(ptr+1,&wordsize, "Data")) {
            fprintf(stderr,"ERROR: in %d word of datastream\n", count);
            return 1;
        }
        datasize += wordsize;
        ptr += wordsize+1; //Устанавливет указатель после слова

        //fprintf(stdout,"count=%d ptr=%p\n", count, ptr);
    }

    if (count != 2) {
        fprintf(stderr,"ERROR: Unexpected quantity of words %d\n", count);
        return 1;
    }
    if (*ptr != '\0') { // Если после запроса есть еще данные
        fprintf(stderr,"ERROR: Unexpected data after [word %d]\n", count);
        return 1;
    }
    if (size != NULL) {
        *size = datasize;
    }
    return 0;
}


//Проверка отправляемой строки на валидность
int handler(char *data) {

    //Обработка команды выхода == [Q,q,\0]
    if (*data == 'q' || *data =='Q' || *data == '\0') exit(EXIT_SUCCESS);



    //Перевод команды в верхний регистр
    *data = toupper(*data);
    *(data + 1) = toupper(*(data + 1));

    

    //Команда == OP
    if (strncmp(data, "OP ", 3) == 0){
        if (wordhandler(data+3,NULL,"DBName") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == RD
    } else if(strncmp(data, "RD ", 3) == 0){
        if (numhandler(data+3,NULL,"Index") == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == WR
    } else if(strncmp(data, "WR ", 3) == 0){

        if (datahandler(data+3,NULL) == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == AD
    } else if(strncmp(data, "AD ", 3) == 0){

        if (datahandler(data+3,NULL) == 0){      
            return 0;
        } else {
            fprintf(stderr,"ERROR: Data is incorrect\n");
            return 1;
        }

    //Команда == DL
    } else if(strncmp(data, "DL ", 3) == 0){
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

