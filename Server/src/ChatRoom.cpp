/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatRoom.cpp
http://inversepalindrome.com
*/


#include "ChatRoom.hpp"

#include <iostream>


ChatRoom::ChatRoom() :
	max_recent_messages(100)
{
}

void ChatRoom::broadcast(ChatMessage const& message)
{
	recent_messages.push_back(message);

	while (size(recent_messages) > max_recent_messages)
	{
		recent_messages.pop_front();
	}

	for (auto participant : participants)
	{
		participant->on_message(message);
	}
}

void ChatRoom::add_participant(std::shared_ptr<ChatParticipant> participant)
{
	std::cout << "Participant has joined.\n";

	participants.insert(participant);

	for(auto const& message : recent_messages)
	{
		participant->on_message(message);
	}
}

void ChatRoom::remove_participant(std::shared_ptr<ChatParticipant> participant)
{
	std::cout << "Participant has left.\n";

	participants.erase(participant);
}