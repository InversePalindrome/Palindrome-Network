/*
Copyright (c) 2019 InversePalindrome
Palindrome Network Common - ChatMessage.hpp
http://inversepalindrome.com
*/


#pragma once

#include <utility>


class ChatMessage
{
public:
	static std::size_t const header_size = 4;
	static std::size_t const max_body_size = 512;

	ChatMessage();

	char* data();
	char const* data() const;

	char* body_data();
	char const* body_data() const;

	std::size_t size() const;
	std::size_t body_size() const;

	void set_body_size(std::size_t body_size);

	void encode_header();

	bool decode_header();

private:
	std::size_t body_length;
	char message_data[header_size + max_body_size];
};