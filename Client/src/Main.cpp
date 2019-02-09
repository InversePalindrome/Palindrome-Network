/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Client - Main.cpp
http://inversepalindrome.com
*/


#include "ChatClient.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <thread>
#include <iostream>


using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: chat_client <host> <port>\n";

		return 1;
	}

	try
	{
		boost::asio::io_service service;
		tcp::resolver resolver(service);

		auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });

		ChatClient chat_client(service, endpoint_iterator);

		std::thread thread([&service]() { service.run(); });

		std::string message;

		while (std::getline(std::cin, message))
		{
			chat_client.write(message);
		}

		chat_client.close();
		thread.join();
	}
	catch (std::exception const& exception)
	{
		std::cerr << "Exception: " << exception.what() << '\n';
	}
}