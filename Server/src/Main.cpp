/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - Main.cpp
http://inversepalindrome.com
*/


#include "ChatServer.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <list>
#include <iostream>


using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: PalindromeNetworkServer <port> [<port> ...]\n";
			return 1;
		}

		boost::asio::io_service service;

		std::list<ChatServer> servers;

		for (int i = 1; i < argc; ++i)
		{
			tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
			
			servers.emplace_back(service, endpoint);
		}

		service.run();
	}
	catch (std::exception const& exception)
	{
		std::cerr << "Exception: " << exception.what() << '\n';
	}
}