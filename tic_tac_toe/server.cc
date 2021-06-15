#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <array>
#include "utils.h"

#define MAX_QUEUE_SIZE 5 //5 clients can connect

int main(){

    std::array<int, 2> client_fds;
    int err = 0;
    struct sockaddr_in serv_addr, client_addr;
    //char buffer[BUF_SIZE];
    socklen_t client_len;
    std::string send_msg;

   LOG("Start Server");
    //create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        LOG("ERROR opening socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    //bind it to an address
    err = bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(err < 0){
        LOG("ERROR binding address to socket");
        return err;
    }

    LOG("Listening on port %d" , PORT);

    //wait for 2 clients to connect.
    for(int i = 0; i < 2; i++){
        //server will now listen to this address
        err = listen(socket_fd, MAX_QUEUE_SIZE);
        if(err < 0){
            LOG("ERROR listening to socket");
            return err;
        }

        //accept the client connection
        int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
        if(client_fd < 0){
            LOG("ERROR accepting connection from client");
            return client_fd;
        }

        LOG("Connected to client %d at %d ", i, client_fd);
        client_fds[i] = client_fd;
    }

#if 0
    int msg_len = recv(client_fds[0], buffer, BUF_SIZE, 0);
    LOG("Msg from client: %d", msg_len);

    /*for(int i = 0; i < msg_len; i++){
        LOG("%s",buffer[i]);
    }
    printf("\n");*/

    send_msg = "Hi! This is Server!";
    const char* send_msg_str = send_msg.c_str();
    send(client_fd, send_msg_str, sizeof(send_msg), 0);


//send from server maybe to client
    close(client_fd);
#endif
    return 0;
}

