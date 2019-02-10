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


ChatClient::ChatClient(boost::asio::io_service& service, tcp::resolver::iterator endpoint_iterator) :
	service(service),
	socket(service)
{
	boost::asio::async_connect(socket, endpoint_iterator,
	[this](auto const& error_code, auto) 
	{
		if (!error_code)
		{
			do_read_header();
		}
	});
}

void ChatClient::write(ChatMessage const& message)
{
	service.post(
	[this, message]()
	{
		auto is_writing = !empty(message_queue);

		message_queue.push_back(message);

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

void ChatClient::do_read_header()
{
	boost::asio::async_read(socket, boost::asio::buffer(read_message.data(), ChatMessage::header_size),
	[this](auto const& error_code, auto)
	{
		if (!error_code && read_message.decode_header())
		{
			do_read_body();
		}
		else
		{
			socket.close();
		}
	});
}

void ChatClient::do_read_body()
{
	boost::asio::async_read(socket, boost::asio::buffer(read_message.body_data(), read_message.body_size()),
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			std::cout.write(read_message.body_data(), read_message.body_size());
			std::cout << '\n';

			do_read_header();
		}
		else
		{
			socket.close();
		}
	});
}

void ChatClient::do_write()
{
	auto const& message = message_queue.front();

	boost::asio::async_write(socket, boost::asio::buffer(message.data(), message.size()), 
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			message_queue.pop_front();

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