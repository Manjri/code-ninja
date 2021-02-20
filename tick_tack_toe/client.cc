#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

#define BUF_SIZE 512

int main(){

    int err = 0;
    struct sockaddr_in serv_addr, client_addr;
    char buffer_rcvd[BUF_SIZE];
    string buffer;
    socklen_t client_len;

    //create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0){
        cout<<"ERROR opening socket"<<endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9004);

    err = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(err < 0){
        cout<<"ERROR Connecting to server "<<endl;
        return err;
    }
    cout<<"Client Connected to server at port "<<9004 <<endl;

    buffer = "Hello! This is client!";
    const char *cstr = buffer.c_str();
    send(socket_fd, cstr, sizeof(buffer), 0);

    int msg_rcvd = recv(socket_fd, buffer_rcvd, BUF_SIZE, 0);
    cout<<"Msg from server: "<< msg_rcvd <<endl;
    for(int i = 0; i < msg_rcvd; i++){
        cout<<buffer_rcvd[i];
    }
    cout<<endl;


    return 0;
}