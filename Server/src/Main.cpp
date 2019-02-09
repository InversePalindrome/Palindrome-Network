/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - Main.cpp
http://inversepalindrome.com
*/


#include "ChatServer.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <iostream>


using boost::asio::ip::tcp;

const int PORT = 1234;

int main()
{
	try
	{
		boost::asio::io_service service;
		tcp::endpoint endpoint(tcp::v4(), PORT);

		ChatServer server(service, endpoint);

		service.run();
	}
	catch (std::exception const& exception)
	{
		std::cerr << "Exception: " << exception.what() << '\n';
	}
}