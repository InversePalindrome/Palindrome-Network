/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - Server.cpp
http://inversepalindrome.com
*/


#include "Server.hpp"


Server::Server(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint const& endpoint) :
	acceptor(service, endpoint)
{
}