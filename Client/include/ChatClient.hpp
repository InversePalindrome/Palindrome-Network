/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Client - ChatClient.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatClient.hpp"
#include "ChatMessage.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <deque>


using boost::asio::ip::tcp;

class ChatClient
{
public:
	ChatClient(boost::asio::io_service& service, tcp::resolver::iterator endpoint_iterator);

	void write(ChatMessage const& message);
	void close();

private:
	boost::asio::io_service& service;

	tcp::socket socket;

	ChatMessage read_message;
	std::deque<ChatMessage> message_queue;

	void do_read_header();
	void do_read_body();

	void do_write();
};