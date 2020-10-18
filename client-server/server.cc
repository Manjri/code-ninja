#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){

  std::cout<<"*** SERVER ***"<<std::endl;

  //create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(server_socket < 0){
      std::cout<<"Error creating server socket! "<<std::endl;
      return EXIT_FAILURE;
  }

  //specify address for this socket
  struct sockaddr_in server_add;
  server_add.sin_family = AF_INET;
  server_add.sin_port = htons(9002); //htons converts endianess
  server_add.sin_addr.s_addr = INADDR_ANY;

  //connect to remote socket
  bind(server_socket, (struct sockaddr *)&server_add, sizeof(server_add));
  //TODO: CHECK RETURN TYPE
  
  //LISTEN
  listen(server_socket, 5); //5: max num of connections for this server

  //accepts the connection and creates a new conncted socket and return a new
  //file descriptor to this socket
  int client_socket = accept(server_socket, NULL, NULL);

  std::string hello = "Hello";

  send(client_socket, hello.c_str(), hello.size(), 0);
  std::cout<<"Sending hello "<<std::endl;

  //close connection
  close(server_socket);
  return 0;
}
