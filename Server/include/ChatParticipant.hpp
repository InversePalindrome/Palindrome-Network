/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatParticipant.hpp
http://inversepalindrome.com
*/


#pragma once

#include "Protocol.hpp"

#include <array>


class ChatParticipant
{
public:
	virtual ~ChatParticipant() = default;

	virtual void on_message(std::array<char, Protocol::MAX_MESSAGE_SIZE> const& message) = 0;

	std::array<char, Protocol::MAX_NAME_SIZE> const& getName();

protected:
	std::array<char, Protocol::MAX_NAME_SIZE> name;
};