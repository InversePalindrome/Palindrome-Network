/*
Copyright (c) 2019 InversePalindrome
Palindrome Network - ChatRoom.cpp
http://inversepalindrome.com
*/


#include "ChatRoom.hpp"


void ChatRoom::add_participant(std::shared_ptr<ChatParticipant> participant)
{
	participants.insert(participant);
}

void ChatRoom::remove_participant(std::shared_ptr<ChatParticipant> participant)
{
	participants.erase(participant);
}