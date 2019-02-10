/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Client - Main.cpp
http://inversepalindrome.com
*/


#include "ChatClient.hpp"
#include "ChatMessage.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <thread>
#include <iostream>


using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";

			return 1;
		}

		boost::asio::io_service service;
		tcp::resolver resolver(service);

		auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });

		ChatClient chat_client(service, endpoint_iterator);

		std::thread thread([&service]() { service.run(); });

		char line[ChatMessage::max_body_size + 1];

		while (std::cin.getline(line, ChatMessage::max_body_size + 1))
		{
			ChatMessage message;
			message.set_body_size(std::strlen(line));
			std::memcpy(message.body_data(), line, message.body_size());
			message.encode_header();

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