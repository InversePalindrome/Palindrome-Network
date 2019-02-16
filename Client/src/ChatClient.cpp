/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Client - ChatClient.cpp
http://inversepalindrome.com
*/


#include "ChatClient.hpp"

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>

#include <iostream>


ChatClient::ChatClient(std::array<char, Protocol::MAX_NAME_SIZE> const& name, boost::asio::io_service& service, 
	tcp::resolver::iterator endpoint_iterator) :
	name(name),
	service(service),
	socket(service)
{
	memset(data(read_message), '\0', Protocol::MAX_MESSAGE_SIZE);

	boost::asio::async_connect(socket, endpoint_iterator,
	[this](auto const& error_code, auto) 
	{
		if (!error_code)
		{
			do_name();
		}
	});
}

void ChatClient::write(std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message)
{
	service.post(
	[this, message]()
	{
		auto is_writing = !empty(write_messages);

		write_messages.push(message);

		if (!is_writing)
		{
			do_write();
		}
	});
}

void ChatClient::close()
{
	service.post([this]() { socket.close(); });
}

void ChatClient::do_name()
{
	boost::asio::async_write(socket, boost::asio::buffer(name, size(name)),
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			do_read();
		}
		else
		{
			socket.close();
		}
	});
}

void ChatClient::do_read()
{
	boost::asio::async_read(socket, boost::asio::buffer(read_message, size(read_message)),
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			std::cout << data(read_message) << '\n';

			do_read();
		}
		else
		{
			socket.close();
		}
	});
}

void ChatClient::do_write()
{
	auto const& message = write_messages.front();

	boost::asio::async_write(socket, boost::asio::buffer(message, size(message)), 
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			write_messages.pop();

			if (!empty(write_messages))
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