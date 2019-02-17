/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatRoom.hpp
http://inversepalindrome.com
*/


#pragma once

#include "Protocol.hpp"
#include "ChatParticipant.hpp"

#include <queue>
#include <memory>
#include <unordered_set>


class ChatRoom
{
public:
	ChatRoom();

	void broadcast(std::shared_ptr<ChatParticipant> participant, 
		std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message);

	void add_participant(std::shared_ptr<ChatParticipant> participant);
	void remove_participant(std::shared_ptr<ChatParticipant> participant);

private:
	std::queue<std::array<char, Protocol::MAX_MESSAGE_SIZE>> recent_messages;
	std::unordered_set<std::shared_ptr<ChatParticipant>> participants;

	const std::size_t max_recent_messages;

	std::array<char, Protocol::MAX_NAME_SIZE> format_name(std::array<char, Protocol::MAX_NAME_SIZE> name);
};