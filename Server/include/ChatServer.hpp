/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatServer.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatRoom.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>


using boost::asio::ip::tcp;

class ChatServer
{
public:
    ChatServer(boost::asio::io_service& service, tcp::endpoint const& endpoint);

private:
    ChatRoom chat_room;
    tcp::acceptor acceptor;
    tcp::socket socket;

    void do_accept();
};