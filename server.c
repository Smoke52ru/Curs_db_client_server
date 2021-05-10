#include "client.h"
#include "db_operation.h"
#include <ctype.h>

int main(){
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    int read_res;
    char client_fifo[FIFO_SIZE];

    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    if (server_fifo_fd == -1){
        fprintf(stderr, "Server fifo failure\n");
        exit(EXIT_FAILURE);
    }

    do {
        read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
        if (read_res > 0){
            //Преобразуем
            if (get_operation(my_data.some_data) == -1){
                memset(my_data.some_data,0,BUFFER_SIZE-1);
                sprintf(my_data.some_data, "%s %s", data.name, data.surname);
                //printf(my_data.some_data, )
            }

            //Отправляем обратно
            sprintf(client_fifo,CLIENT_FIFO_NAME, my_data.client_pid);
            client_fifo_fd = open(client_fifo, O_WRONLY);
            if (client_fifo_fd != -1) {
                write(client_fifo_fd, &my_data, sizeof(my_data));
                close(client_fifo_fd);
            }            
        }
    } while (read_res >0);
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);
    exit(EXIT_SUCCESS);
}
