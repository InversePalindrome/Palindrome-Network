/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Client - ChatClient.hpp
http://inversepalindrome.com
*/


#pragma once

#include "Protocol.hpp"
#include "ChatClient.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <array>
#include <queue>


using boost::asio::ip::tcp;

class ChatClient
{
public:
	ChatClient(std::array<char, Protocol::MAX_NAME_SIZE> const& name, boost::asio::io_service& service, 
		tcp::resolver::iterator endpoint_iterator);

	void write(std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message);
	void close();

private:
	boost::asio::io_service& service;

	tcp::socket socket;

	std::array<char, Protocol::MAX_NAME_SIZE> name;
	std::array<char, Protocol::MAX_MESSAGE_SIZE> read_message;
	std::queue<std::array<char, Protocol::MAX_MESSAGE_SIZE>> write_messages;

	void do_name();
	void do_read();
	void do_write();
};