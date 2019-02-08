/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatRoom.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatParticipant.hpp"

#include <memory>
#include <unordered_set>


class ChatRoom
{
public:
	void add_participant(std::shared_ptr<ChatParticipant> participant);
	void remove_participant(std::shared_ptr<ChatParticipant> participant);

private:
	std::unordered_set<std::shared_ptr<ChatParticipant>> participants;
};