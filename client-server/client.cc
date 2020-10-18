#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){

  std::cout<<"*** CLIENT ***"<<std::endl;

  int network_socket;

  //create socket
  network_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(network_socket < 0){
      std::cout<<"Error creating client socket! "<<std::endl;
      return EXIT_FAILURE;
  }

  //specify address for this socket
  struct sockaddr_in server_add;
  server_add.sin_family = AF_INET;
  server_add.sin_port = htons(9002); //htons converts endianess
  server_add.sin_addr.s_addr = INADDR_ANY;


  //connect to remote socket
  int connection_status = connect(network_socket, (struct sockaddr *)&server_add, sizeof(server_add));
  if(connection_status == -1){
    std::cout<<" Error! Unable to connect to remote socket! "<<std::endl;
    return EXIT_FAILURE;
  }

  /*std::string hello = "Hiii from client";

  send(network_socket, hello.c_str(), hello.size(), 0);
  std::cout<<"Sending hi from client "<<std::endl;*/

  char server_response[256] = {0};
  /* memset(server_response, 0, sizeof(server_response)); */
  recv(network_socket, &server_response, sizeof(server_response), 0);

  //print servers reponse
  std::cout<<"Server sent data: "<<server_response <<std::endl;

  return 0;
}
