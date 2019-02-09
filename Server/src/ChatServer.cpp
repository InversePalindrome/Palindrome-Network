/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatServer.cpp
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
	[this](auto const& error_code)
	{
		if (!error_code)
		{
			std::make_shared<ChatSession>(chat_room, std::move(socket))->start();
		}

		do_accept();
	});
}