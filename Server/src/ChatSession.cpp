/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatSession.cpp
http://inversepalindrome.com
*/


#include "ChatSession.hpp"

#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>


ChatSession::ChatSession(ChatRoom& chat_room, tcp::socket socket) :
	chat_room(chat_room),
	socket(std::move(socket))
{
}

void ChatSession::on_message(std::string const& message)
{
	auto is_writing = !empty(message_queue);

	message_queue.push(message);

	if (!is_writing)
	{
		do_write();
	}
}

void ChatSession::start()
{
	chat_room.add_participant(shared_from_this());

	do_read();
}

void ChatSession::do_read()
{
	boost::asio::async_read(socket, boost::asio::buffer(data(read_message), size(read_message)),
	[this](auto const& error_code, auto)
	{
		if (!error_code)
		{
			chat_room.broadcast(read_message);

			do_read();
		}
		else
		{
			chat_room.remove_participant(shared_from_this());
		}
	});
}

void ChatSession::do_write()
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
			chat_room.remove_participant(shared_from_this());
		}
	});
}
