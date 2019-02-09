/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatServer.cpp
http://inversepalindrome.com
*/


#include "ChatServer.hpp"
#include "ChatSession.hpp"


ChatServer::ChatServer(boost::asio::io_service& service, tcp::endpoint const& endpoint) :
	acceptor(service, endpoint),
	socket(service)
{
	do_accept();
}

void ChatServer::do_accept()
{
	acceptor.async_accept(socket,
	[](auto const& error_code)
	{
		if (!error_code)
		{
			std::make_shared<ChatSession>(std::move(socket), chat_room)->start();
		}

		do_accept();
	});
}