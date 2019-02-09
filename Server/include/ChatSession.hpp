/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatSession.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatRoom.hpp"
#include "ChatParticipant.hpp"

#include <boost/asio/ip/tcp.hpp>

#include <queue>
#include <string>
#include <memory>


using boost::asio::ip::tcp;

class ChatSession : public ChatParticipant, public std::enable_shared_from_this<ChatSession>
{
public:
	ChatSession(ChatRoom& chatroom, tcp::socket socket);

	virtual void on_message(std::string const& message) override;

	void start();

private:
	ChatRoom& chat_room;

	tcp::socket socket;

	std::string read_message;
	std::queue<std::string> message_queue;

	void do_read();
	void do_write();
};