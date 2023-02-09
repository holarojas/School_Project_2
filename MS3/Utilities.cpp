/*----------------------------------------------
// FINAL PROJECT
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Nov 26th, 2022
------------------------------------------------
// I confirm that I am the only author of this
// file and the content was created entirely
// by me.
---------------------------------------------- */

#include <iostream>
#include "Utilities.h"

namespace sdds
{
	//Initialization of class member
	char Utilities::m_delimiter{};

	//Sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	//Returns the field width of the current object
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	//Extracts a token from std::string str referred to by the first parameter
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token;
		size_t foundPos = str.find(m_delimiter, next_pos);

		if (foundPos != std::string::npos) {
			//Reports an exception if a delimiter is found at next_pos
			if (foundPos == next_pos) {
				more = false;
				throw "EXC: Delimiter found at next_pos.";
			}

			next_pos = str.find_first_not_of(" \t\f\v\n\r", next_pos);

			token = str.substr(next_pos, foundPos - next_pos);
			//Remove whitespaces
			trimWhiteSp(token);

			//Update next_pos with the position of the next token
			next_pos = foundPos + 1;
			//More tokens to get
			more = true;
		}
		else {
			next_pos = str.find_first_not_of(" \t\f\v\n\r", next_pos);

			//Get all characters until the end of the string
			token = str.substr(next_pos, std::string::npos);
			//Remove whitespaces
			trimWhiteSp(token);

			//No more tokens to get
			more = false;
		}

		//Updates the current object's widthField 
		if (m_widthField < token.length()) {
			m_widthField = token.length();
		}

		return token;
	}

	//Function that removes whitespaces to the left and to the right of the token
	void Utilities::trimWhiteSp(std::string& str)
	{
		const std::string WHITESPACE = " \n\r\t\f\v";

		size_t start = str.find_first_not_of(WHITESPACE);
		if (start == std::string::npos) {
			str = "";
		}
		else {
			str = str.substr(start);
		}

		size_t end = str.find_last_not_of(WHITESPACE);
		if (end == std::string::npos) {
			str = "";
		}
		else {
			str = str.substr(0, end + 1);
		}
	}

	//Sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	//Returns the delimiter for this class
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}