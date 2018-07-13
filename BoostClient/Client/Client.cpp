#include "BoostClient.h"

void ParseMSG(std::string Message, int& wParam, int& lParam, int& Keycode)
{
	std::istringstream iss;
	iss.str(Message);
	int code[4] = { 0 };
	if (Message[0] == '0') {
		for (size_t i = 0; i < 4; i++)
		{
			iss >> code[i];
		}
		wParam = code[1];
		lParam = code[2];
		Keycode = code[3];
	}
	else {
		wParam = code[1];
		lParam = code[2];
	}
}

const char SERVER_IP[] = "10.100.26.160";
const unsigned short PORT_NUMBER = 8080;

int main()
{

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);


	BoostClient client(io_service);

	boost::system::error_code ec;
	client.Connect(endpoint);
	io_service.run(ec);
	if (ec)
		std::cout << "io_service error No: " << ec.value() << " error Message: " << ec.message() << std::endl;

	system("pause");
	return 0;
}



