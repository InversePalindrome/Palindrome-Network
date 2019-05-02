/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatSession.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatRoom.hpp"
#include "Protocol.hpp"
#include "ChatParticipant.hpp"

#include <boost/asio/ip/tcp.hpp>

#include <array>
#include <queue>
#include <memory>


using boost::asio::ip::tcp;

class ChatSession : public ChatParticipant, public std::enable_shared_from_this<ChatSession>
{
public:
    ChatSession(ChatRoom& chatroom, tcp::socket socket);

    virtual void on_message(std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message) override;

    void start();

private:
    ChatRoom& chat_room;

    tcp::socket socket;

    std::array<char, Protocol::MAX_MESSAGE_SIZE> read_message;
    std::queue<std::array<char, Protocol::MAX_MESSAGE_SIZE>> write_messages;

    void do_name();
    void do_read();
    void do_write();
};