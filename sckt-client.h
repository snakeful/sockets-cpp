#ifndef sckt_client
#define sckt_client

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int send_msg(string message, uint16_t port)
{
  const char* msg = message.c_str();
  // creating socket
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  // specifying address
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  // connectiong to socket
  connect(clientSocket, (struct sockaddr *)&serverAddress,
          sizeof(serverAddress));
  // sending connection request
  send(clientSocket, msg, strlen(msg), 0);
  // closing socket
  close(clientSocket);

  return 0;
}

#endif