#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sckt-server.h"
#include "sckt-client.h"

using namespace std;

const int BUFFER_SIZE = 1024;

int main()
{
  // creating socket
  int serverSocket = create_server_socket("", 8080, 5);

  while (true) {
    // accepting connection request
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // receiving data
    char buffer[BUFFER_SIZE] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    string msg = string(&buffer[0], BUFFER_SIZE);
    cout << "Message from client: " << msg << endl;
    int commaPos = msg.find(',');
    string port = msg.substr(commaPos + 1, BUFFER_SIZE);
    cout << "Port of client: " << stoi(port) << endl;
    send_msg("Hello client " + msg, stoi(port));
  }

  // closing the socket.
  close(serverSocket);

  return 0;
}
