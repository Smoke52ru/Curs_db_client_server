#include<stdio.h>
#include<string.h>
#include"bd_operation.h"

// #define OPERATIONS {"OP", "RD", "WR", "AD", "DL"}

int main(void){
    bd_open("text.txt", 128);
    // bd_write_element(0, "DIMA SMIRNOV");
    bd_read(0);
    printf("%s %s\n", data.name, data.surname);
    bd_close();
    return 0;
}
    