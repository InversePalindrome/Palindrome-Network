/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatRoom.cpp
http://inversepalindrome.com
*/


#include "ChatRoom.hpp"


void ChatRoom::broadcast(std::string const& message)
{
	recent_messages.push(message);

	while (size(recent_messages) > max_recent_messages)
	{
		recent_messages.pop();
	}

	for (auto participant : participants)
	{
		participant->on_message(message);
	}
}

void ChatRoom::add_participant(std::shared_ptr<ChatParticipant> participant)
{
	participants.insert(participant);
}

void ChatRoom::remove_participant(std::shared_ptr<ChatParticipant> participant)
{
	participants.erase(participant);
}