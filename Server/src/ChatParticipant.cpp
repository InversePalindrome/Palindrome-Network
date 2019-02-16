/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - ChatParticipant.cpp
http://inversepalindrome.com
*/


#include "ChatParticipant.hpp"


std::array<char, Protocol::MAX_NAME_SIZE> const& ChatParticipant::getName()
{
	return name;
}