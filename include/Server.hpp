/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - Server.hpp
http://inversepalindrome.com
*/


#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>


class Server
{
public:
	Server(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint const& endpoint);

private:
	boost::asio::ip::tcp::acceptor acceptor;
};