#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define MAX_QUEUE_SIZE 5 //5 clients can connect
#define BUF_SIZE 512

int main(){

    int err = 0;
    struct sockaddr_in serv_addr, client_addr;
    char buffer[BUF_SIZE];
    socklen_t client_len;
    string send_msg;

    //create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        cout<<"ERROR opening socket"<<endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9004);
    //bind it to an address
    err = bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(err < 0){
        cout<<"ERROR binding address to socket"<<endl;
        return err;
    }

    cout<<"Listening on port " << 9004 <<endl;

    //server will now listen to this address
    err = listen(socket_fd, MAX_QUEUE_SIZE);
    if(err < 0){
        cout<<"ERROR listening to socket"<<endl;
        return err;
    }

    //accept the client connection
    int client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
    if(client_fd < 0){
        cout<<"ERROR accepting connection from client"<<endl;
        return client_fd;
    }

    cout<<"Connected to client "<<client_fd <<endl;

//maybe while loop for while receiving.. till when ?
    int msg_len = recv(client_fd, buffer, BUF_SIZE, 0);
    cout<<"Msg from client: "<< msg_len <<endl;

    for(int i = 0; i < msg_len; i++){
        cout<<buffer[i];
    }
    cout<<endl;

    send_msg = "Hi! This is Server!";
    const char* send_msg_str = send_msg.c_str();
    send(client_fd, send_msg_str, sizeof(send_msg), 0);


//send from server maybe to client
    close(client_fd);
    return 0;
}

