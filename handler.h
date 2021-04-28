#include <string.h>
#include <stdio.h>

int handler(char *data) {

    char *str[5] = {"OP", "RD", "WR", "AD", "DL"};
    char *strbuf = malloc(2);

    strncpy( strbuf, data, 2);
    for (int i = 0; i < 5; i++) {
        if (strcmp(strbuf, str[i]) == 0) {
            int j = 3;
            while (data[j] != *" ") {
                if ((data[j]>'0') && (data[j]<'9')) {
                puts("Все заебись");

                } else {
                    puts("Мне нехорошо...");
                    return 1;
                }
                j++;
            }
            j++;
            while (data[j] != *" ") {
                puts("Все классно");
                j++;
            }
            j++;
            while (data[j] != *"\0") {
                puts("Все четко");
                j++;
            }
            
            // puts("Строки идентичны");
            return 0;
        } else {
            // puts("Строки отличаются");
            continue;
        }
    }


    return 1;
}

