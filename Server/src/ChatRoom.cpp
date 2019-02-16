/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatRoom.cpp
http://inversepalindrome.com
*/


#include "ChatRoom.hpp"
#include "Timestamp.hpp"

#include <iostream>


ChatRoom::ChatRoom() :
	max_recent_messages(100)
{
}

void ChatRoom::broadcast(std::shared_ptr<ChatParticipant> participant, 
	std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message)
{
	std::array<char, Protocol::MAX_MESSAGE_SIZE> formatted_message;

	strcpy(data(formatted_message), Utility::getTimestamp().c_str());
	strcat(data(formatted_message), data(participant->getName()));
	strcat(data(formatted_message), data(message));

	recent_messages.push(formatted_message);

	while (size(recent_messages) > max_recent_messages)
	{
		recent_messages.pop();
	}

	for (auto participant : participants)
	{
		participant->on_message(formatted_message);
	}
}

void ChatRoom::add_participant(std::shared_ptr<ChatParticipant> participant)
{
	std::cout << "Participant has joined the chat room.\n";

	participants.insert(participant);
}

void ChatRoom::remove_participant(std::shared_ptr<ChatParticipant> participant)
{
	std::cout << "Participant has left the chat room.\n";

	participants.erase(participant);
}