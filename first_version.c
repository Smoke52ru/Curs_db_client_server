#include<stdlib.h>
#include"bd_operation.h"

//НЕ ДОПИЛЕННАЯ ВЕРСИЯ, ЧЕКАЙТЕ LAST_VERSION.c
char* OPERATIONS[6] = {"OP", "RD", "WR", "AD", "DL", "CL"};

void string_split(char *string, char first[], char second[]){
    char *p = strchr(string, ' ');

    strncpy(first, string, p - string);
    second[p - string] = 0;
    strcpy(second, p + 1);
}

int get_operation_number(char* operation){
    for(int i = 0; i < 6; i++){
        if(!strcmp(operation, OPERATIONS[i])) return i + 1;
    }
    return 0;
}

int get_operation(char* string){
    char operation[4], data[MAXNAME + MAXSURNAME + 1];
    string_split(string, operation, data);
    printf("operation = %s, data = %s\n", operation, data);
    int operation_number = get_operation_number(operation);

    switch(operation_number){
    case 1:
        printf("OPEN\n");
        dbopen(data);
        break;
    case 2:
        printf("READ\n");
        dbread(atoi(data));
        break;
    case 3:{
        printf("WRITE\n");
        char index[2], strdata[MAXNAME + MAXSURNAME + 1];
        string_split(data, index, strdata);

        dbwrite(atoi(index), strdata);
        break;
    }
    case 4:
        printf("ADD\n");
        dbadd(data);
        break;
    case 5:
        printf("DELETE\n");
        dbdelete(atoi(data));
        break;
    default:
        printf("CLOSE\n");
        dbclose();
        break;
    }
}

int main(){
    get_operation("OP text.txt");
    get_operation("WR 1 DIMA SMIRNOV");
    get_operation("WR 2 NIKITA KURNOSOV");
    get_operation("RD 2");
    printf("%s %s\n", data.name, data.surname);
    get_operation("DL 1");
    get_operation("RD 1");
    printf("%s %s\n", data.name, data.surname);

    char* close = "CL";
    get_operation(close);
    return 0;
}