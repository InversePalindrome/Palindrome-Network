/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatParticipant.hpp
http://inversepalindrome.com
*/


#pragma once

#include "ChatMessage.hpp"


class ChatParticipant
{
public:
	virtual ~ChatParticipant() = default;

	virtual void on_message(ChatMessage const& message) = 0;
};