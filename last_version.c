#include<stdlib.h>
#include"bd_operation.h"

// фукнция отделения операции от данных(делит строку по первому пробелу)
void string_split(char *string, char first[], char second[]){
    char *p = strchr(string, ' ');

    strncpy(first, string, p - string);
    second[p - string] = 0;
    strcpy(second, p + 1);
}

// главная функция выполнения команд, получает на вход строку, парсит ее и выполняет операции
int get_operation(char* string){
    char operation[4], data[MAXNAME + MAXSURNAME + 1];
    // если пользователь хочет закончить работу с бд
    if(!strcmp(string, "CL")){
        printf("operation = %s, data = NONE", string);
        dbclose();
    }
    // иначе ищем среди доступных команд
    else{
        string_split(string, operation, data);
        printf("operation = %s, data = %s\n", operation, data);

        if (!strcmp(operation, "OP"))
            dbopen(data);
        else if(!strcmp(operation, "RD"))
            dbread(atoi(data));
        else if(!strcmp(operation, "WR")){
            char string_number[2], str[MAXNAME + MAXSURNAME + 1];
            
            string_split(data, string_number, str);
            dbwrite(atoi(string_number), str);
        }
        else if(!strcmp(operation, "AD"))
            dbadd(data);
        else if(!strcmp(operation, "DL"))
            dbdelete(atoi(data));
    }
}

int main(){
    get_operation("OP text.txt");
    get_operation("WR 1 DIMA SMIRNOV");
    get_operation("WR 2 NIKITA KURNOSOV");
    get_operation("AD LEMA TAPIN");
    get_operation("RD 3");
    printf("%s %s\n", data.name, data.surname);
    get_operation("DL 1");
    get_operation("RD 1");
    printf("%s %s\n", data.name, data.surname);
    get_operation("CL");

    return 0;
}