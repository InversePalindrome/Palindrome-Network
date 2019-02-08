/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatClient.cpp
http://inversepalindrome.com
*/


#include "ChatClient.hpp"

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>


ChatClient::ChatClient(boost::asio::io_service& service, tcp::resolver::iterator endpoint_iterator) :
	service(service),
	socket(service)
{
	boost::asio::async_connect(socket, endpoint_iterator,
	[](auto const& error_code, auto) 
	{
		if (!error_code)
		{

		}
	});
}

void ChatClient::do_read()
{
	/*
	boost::asio::async_read(socket, boost::asio::buffer(data(read_message), size(read_message)), 
    [this](auto error_code, auto)
	{
		if (!error_code)
		{
			do_read();
		}
		else
		{
			socket.close();
		}
	});*/
}

void ChatClient::do_write()
{
	auto const& message = message_queue.front();

	boost::asio::async_write(socket, boost::asio::buffer(data(message), size(message)), 
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			message_queue.pop();

			if (!empty(message_queue))
			{
				do_write();
			}
		}
		else
		{
			socket.close();
		}
	});
}