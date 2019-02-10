/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatSession.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatRoom.hpp"
#include "ChatMessage.hpp"
#include "ChatParticipant.hpp"

#include <boost/asio/ip/tcp.hpp>

#include <deque>
#include <memory>


using boost::asio::ip::tcp;

class ChatSession : public ChatParticipant, public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(ChatRoom& chatroom, tcp::socket socket);

	virtual void on_message(ChatMessage const& message) override;

	void start();

private:
	ChatRoom& chat_room;

	tcp::socket socket;

	ChatMessage read_message;
	std::deque<ChatMessage> message_queue;

	void do_read_header();
	void do_read_body();

	void do_write();
};