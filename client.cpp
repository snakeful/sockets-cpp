// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits.h>
#include "sckt-server.h"
#include "sckt-client.h"
#include <thread>

using namespace std;

int port = 8081;
const int BUFFER_SIZE = 1024;
const int INC_CONN = 5;
char hostname[HOST_NAME_MAX];

void receive(int port)
{
  gethostname(hostname, HOST_NAME_MAX);
	cout << hostname;
	int serverSocket = create_server_socket(hostname, port, INC_CONN);
	do
	{
		int clientSocket = accept(serverSocket, nullptr, nullptr);

		// recieving data
		char buffer[1024] = {0};
		recv(clientSocket, buffer, sizeof(buffer), 0);
		cout << "Message from server: " << buffer << endl;
	} while (true);

	// closing the socket.
	close(serverSocket);
}

int main()
{
	thread thr_receive(receive, port);
	thr_receive.detach();
	// sending data
	string message;
	do
	{
		// get input from user
		getline(cin, message);

		// send message to endpoint
		send_msg(message + ',' + to_string(port), 8080);
	} while (message != "exit");

	return 0;
}
