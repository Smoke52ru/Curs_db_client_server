#include "client.h"
#include "handler.h"
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    int times_to_send; //FIXME Временно до беск.цикла
    char client_fifo[FIFO_SIZE];

    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if (server_fifo_fd == -1) {
        fprintf(stderr, "Sorry, no server \n");
        exit(EXIT_FAILURE);
    }
    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, (int)my_data.client_pid);
    unlink(client_fifo);
    if (mkfifo(client_fifo, 0777) == -1) {
        fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
        exit(EXIT_FAILURE);
    }


    //Отправка данных
    //TODO Бесконечный цикл 
    for(times_to_send = 0; times_to_send < 2; times_to_send++) {
        scanf("%[^\n]%*c",my_data.some_data); //Считывание команды
        if (handler(my_data.some_data) == 0) {
            write(server_fifo_fd, &my_data, sizeof(my_data));
        } else {continue;}
        client_fifo_fd = open(client_fifo, O_RDONLY);
        if (client_fifo_fd != -1) {
            if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0){
                printf("recieved from server: {%s}\n", my_data.some_data);
            }
            close(client_fifo_fd);
        }
    }
    close(server_fifo_fd);
    unlink(client_fifo);
    exit(EXIT_SUCCESS);
}
