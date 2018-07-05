#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment(lib , "ws2_32.lib")

using namespace std;

int main() {
	string ipAddress = "127.0.0.1";
	int port = 54000;


	WSADATA Data;
	WORD ver = MAKEWORD(2, 2);
	//Initialize
	int wsResult = WSAStartup(ver, &Data);
	if (wsResult != 0) {
		cerr << "Can't initialize winsock" << endl;
		return 1;
	}
	//Create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create a socket" << endl;
		WSACleanup();
		return 2;
	}
	
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
	
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server" << endl;
			closesocket(sock);
			WSACleanup();
			return 3;
	}


//sss
	char buf[4096];
	string userInput;
	do
	{
		cout << "Server > ";
		getline(cin, userInput);
		if (userInput.size() > 0) {
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				ZeroMemory(buf, 4096);
				int bytesRecieved = recv(sock, buf, 4096, 0);
				if (bytesRecieved >0)
				{
				cout << "Displayed on client :" << string(buf, 0, bytesRecieved) << endl;
				}
			}
		}
	} while (userInput.size() >0);
	//


	closesocket(sock);
	WSACleanup();

	return 0;
}