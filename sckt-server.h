#ifndef sckt_server
#define sckt_server

#include <netinet/in.h>

using namespace std;

int create_server_socket(string hostname, int port, int incomming)
{
  // creating socket
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // specifying the address
  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(port);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  // binding socket.
  bind(serverSocket, (struct sockaddr *)&serverAddress,
       sizeof(serverAddress));

  // listening to the assigned socket
  listen(serverSocket, incomming);

  return serverSocket;
}

#endif