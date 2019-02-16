/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Server - Timestamp.cpp
http://inversepalindrome.com
*/


#include "Timestamp.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>


std::string Utility::getTimestamp()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	
	std::ostringstream oStream;
	oStream << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ");

	return oStream.str();
}