/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Common - ChatMessage.cpp
http://inversepalindrome.com
*/


#include "ChatMessage.hpp"


ChatMessage::ChatMessage() :
	body_length(0)
{
}

char* ChatMessage::data()
{
	return message_data;
}

char const* ChatMessage::data() const
{
	return message_data;
}

char* ChatMessage::body_data()
{
	return message_data + header_size;
}

char const* ChatMessage::body_data() const
{
	return message_data + header_size;
}

std::size_t ChatMessage::size() const
{
	return header_size + body_length;
}

std::size_t ChatMessage::body_size() const
{
	return body_length;
}

void ChatMessage::set_body_size(std::size_t body_size)
{
	body_length = body_size;

	if (body_length > max_body_size)
	{
		body_length = max_body_size;
	}
}

void ChatMessage::encode_header()
{
	char header[header_size + 1] = "";
	std::sprintf(header, "%4d", body_length);
	std::memcpy(message_data, header, header_size);
}

bool ChatMessage::decode_header()
{
	char header[header_size + 1] = "";
	std::strncat(header, message_data, header_size);
	
	body_length = std::atoi(header);
	if (body_length > max_body_size)
	{
		body_length = 0;

		return false;
	}

	return true;
}