/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatRoom.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatMessage.hpp"
#include "ChatParticipant.hpp"

#include <deque>
#include <memory>
#include <unordered_set>


class ChatRoom
{
public:
	ChatRoom();

	void broadcast(ChatMessage const& message);

	void add_participant(std::shared_ptr<ChatParticipant> participant);
	void remove_participant(std::shared_ptr<ChatParticipant> participant);

private:
	std::deque<ChatMessage> recent_messages;
	std::unordered_set<std::shared_ptr<ChatParticipant>> participants;

	const std::size_t max_recent_messages;
};