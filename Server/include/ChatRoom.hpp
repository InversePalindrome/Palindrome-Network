/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatRoom.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatParticipant.hpp"

#include <queue>
#include <string>
#include <memory>
#include <unordered_set>


class ChatRoom
{
public:
	void broadcast(std::string const& message);

	void add_participant(std::shared_ptr<ChatParticipant> participant);
	void remove_participant(std::shared_ptr<ChatParticipant> participant);

private:
	std::queue<std::string> recent_messages;
	std::unordered_set<std::shared_ptr<ChatParticipant>> participants;

	const std::size_t max_recent_messages = 100;
};