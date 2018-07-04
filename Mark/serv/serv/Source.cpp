#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib , "ws2_32.lib")

using namespace std;

int main() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	//Initialize
	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0) {
		cerr << "Can't initialize winsock" << endl;
		return 1;
	}
	//Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket" << endl;
		return 2;
	}

	//Bind  ip address and port to the socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	//Listening

	listen(listening, SOMAXCONN);

	//Wait for connection

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Error socket" << endl;
		return 3;
	}

	char host[NI_MAXHOST];
	char service[NI_MAXHOST];
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	}
	// Close
	closesocket(listening);

	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		int bytesRecieved = recv(clientSocket, buf, 4096, 0);
		if (bytesRecieved == SOCKET_ERROR) {
			cerr << "Error in rcv()" << endl;
			return 4;
		}
		if (bytesRecieved == 0) {
			cout << "Client disconnected" << endl;
			break;

		}
		cout << string(buf, 0, bytesRecieved) << endl;
		send(clientSocket, buf, bytesRecieved + 1, 0);
	}


	closesocket(clientSocket);
	WSACleanup();

	return 0;
}