#include "InputHandler.h"

InputHandler & InputHandler::Instance()
{
	static InputHandler handler;
	return handler;
}

LRESULT CALLBACK KeyboardEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	DWORD SHIFT_key = 0;
	DWORD CTRL_key = 0;
	DWORD ALT_key = 0;
	KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
	std::string wparam = std::bitset<sizeof(wParam) * 8>(wParam).to_string();
	std::string lparam = std::bitset<sizeof(lParam) * 8>(lParam).to_string();
	std::string kcode = std::bitset<sizeof(hooked_key.vkCode) * 8>(hooked_key.vkCode).to_string();
	std::string message = "0 " + wparam + ' ' + lparam + ' ' + kcode + '\0';
	InputHandler::Instance().sentMessage = message;
	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		DWORD dwMsg = 1;
		dwMsg += hooked_key.scanCode << 16;
		dwMsg += hooked_key.flags << 24;
		char lpszKeyName[1024] = { 0 };


		int key = hooked_key.vkCode;

		// TO DO SEND: key and command


		SHIFT_key = GetAsyncKeyState(VK_SHIFT);
		CTRL_key = GetAsyncKeyState(VK_CONTROL);
		ALT_key = GetAsyncKeyState(VK_MENU);

		printf("Keycode = %c\n", key);

		if (key >= 'A' && key <= 'Z')
		{

			if (GetAsyncKeyState(VK_SHIFT) >= 0) key += 32;
			
			SHIFT_key = 0;
			CTRL_key = 0;
			ALT_key = 0;
		}
	}	
	std::cout << message << std::endl;
	return CallNextHookEx(InputHandler::Instance().hKeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseEventProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		// TO DO: Send wparam to define comand
		printf("Mouse position X = %d  Mouse Position Y = %d\n", pMouseStruct->pt.x, pMouseStruct->pt.y);
		// TO DO: Calc delta movement, send it
		std::string wparam = std::bitset<sizeof(wParam) * 8>(wParam).to_string();
		std::string lparam = std::bitset<sizeof(lParam) * 8>(lParam).to_string();
		/*std::string wheel = std::bitset<sizeof(GET_WHEEL_DELTA_WPARAM(wParam)) * 8>(GET_WHEEL_DELTA_WPARAM(wParam)).to_string();*/
		std::string message = "1 " + wparam + ' ' + lparam  + '\0';
		InputHandler::Instance().sentMessage = message;
		std::cout << message << std::endl;

	}
	return CallNextHookEx(InputHandler::Instance().hMouseHook, nCode, wParam, lParam);
}

void InputHandler::MyMouseLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseEventProc, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hMouseHook);

}

void InputHandler::MyKeyboardLogger()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEventProc, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);

}

void InputHandler::MessageLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void InputHandler::Run()
{
	try
	{
		std::thread mouseThread(&InputHandler::MyMouseLogger, InputHandler::Instance());
		std::thread keyboardThread(&InputHandler::MyKeyboardLogger, InputHandler::Instance());

		mouseThread.join();
		keyboardThread.join();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

class connection : public boost::enable_shared_from_this<connection>
{
public:
	typedef boost::shared_ptr<connection> pointer;

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new connection(io_service));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		//Read from client, make json and send appropriate response
		boost::asio::async_read(socket_, message_,
			boost::bind(&connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

private:
	connection(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}

	void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
	{
		std::cout << "Handle Read of connection\n";

		if (error && error != boost::asio::error::eof) {
			std::cout << "Error: " << error.message() << "\n";
			return;
		}
		std::string buf = "Hello ,It's me";
		buf += '\0';
		/*std::cin >> buf;*/
		socket().write_some(boost::asio::buffer(buf));
		//std::cout << buf << std::endl;


	}

	tcp::socket socket_;
	boost::asio::streambuf message_;
};