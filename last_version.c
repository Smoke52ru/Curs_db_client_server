#include<stdlib.h>
#include"db_operation.h"


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