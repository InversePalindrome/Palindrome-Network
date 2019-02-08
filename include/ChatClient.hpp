/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatClient.hpp
http://inversepalindrome.com
*/


#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include <queue>
#include <string>


using boost::asio::ip::tcp;

class ChatClient
{
public:
	ChatClient(boost::asio::io_service& service, tcp::resolver::iterator endpoint_iterator);

private:
	boost::asio::io_service& service;

	tcp::socket socket;

	std::string read_message;
	std::queue<std::string> message_queue;

	void do_read();
	void do_write();
};