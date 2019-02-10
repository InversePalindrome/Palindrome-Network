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

void ChatSession::on_message(ChatMessage const& message)
{
	auto is_writing = !empty(message_queue);

	message_queue.push_back(message);

	if (!is_writing)
	{
		do_write();
	}
}

void ChatSession::start()
{
	chat_room.add_participant(shared_from_this());

	do_read_header();
}

void ChatSession::do_read_header()
{
	auto self(shared_from_this());

	boost::asio::async_read(socket, boost::asio::buffer(read_message.data(), ChatMessage::header_size),
	[this, self](auto const& error_code, auto)
	{
		if (!error_code && read_message.decode_header())
		{
			do_read_body();
		}
		else
		{
			chat_room.remove_participant(shared_from_this());
		}
	});
}

void ChatSession::do_read_body()
{
	auto self(shared_from_this());

	boost::asio::async_read(socket, boost::asio::buffer(read_message.body_data(), read_message.body_size()),
	[this, self](auto const& error_code, auto)
	{
		if (!error_code)
		{
			chat_room.broadcast(read_message);

			do_read_header();
		}
		else
		{
			chat_room.remove_participant(shared_from_this());
		}
	});
}

void ChatSession::do_write()
{
	auto self(shared_from_this());

	auto const& message = message_queue.front();

	boost::asio::async_write(socket, boost::asio::buffer(message.data(), message.size()),
		[this, self](auto const& error_code, auto)
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
			chat_room.remove_participant(shared_from_this());
		}
	});
}
