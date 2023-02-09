/*----------------------------------------------
// FINAL PROJECT
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Dec 3rd, 2022
------------------------------------------------
// I confirm that I am the only author of this
// file and the content was created entirely
// by me.
---------------------------------------------- */
#include <iostream>
#include <iomanip>
#include <string>

#include "Station.h"
#include "Utilities.h"

namespace sdds
{
	//Initialization of Class Variables
	size_t Station::m_widthField{};
	int Station::id_generator{};

	//Custom Constructor
	Station::Station(const std::string& str)
	{
		Utilities utils;
		size_t pos = 0;
		bool isMore = true;

		std::string temp{};
		
		//Extract item name
		m_itemName = utils.extractToken(str, pos, isMore);
		
		//Extract serial number
		temp = utils.extractToken(str, pos, isMore);
		m_serialNumber = std::stoi(temp);

		//Extract quantity in stock
		temp = utils.extractToken(str, pos, isMore);
		m_itemsInStock = std::stoi(temp);

		//Updates Station::m_widthField to the max value
		m_widthField = m_itemName.length();

		//Extract description
		m_desc = utils.extractToken(str, pos, isMore);

		//Every time a new instance is created, the curent value of the id_generator is stored in that instance, and id_generator is incremented.
		m_id = ++id_generator;
	}

	//Returns the name of the current Station object
	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	//Returns the next serial number to be used on the assembly line and increments m_serialNumber
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	//Returns the remaining quantity of items in the Station object
	size_t Station::getQuantity() const
	{
		return m_itemsInStock;
	}

	//Subtracts 1 from the available quantity; should not drop below 0
	void Station::updateQuantity()
	{
		m_itemsInStock == 0 ? m_itemsInStock = 0 : --m_itemsInStock;
	}

	//Inserts information about the current object into stream os
	void Station::display(std::ostream& os, bool full) const
	{
		if (!full) {
			//Inserts only the ID, name and serial number
			//ID | NAME | SERIAL |
			os << std::setw(3) << std::right << std::setfill('0') << m_id << " | " <<
				std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | " <<
				std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " |";
		}
		else {
			//Inserts the information in the following format
			//ID | NAME | SERIAL | QUANTITY | DESCRIPTION
			os << std::setw(3) << std::right << std::setfill('0') << m_id << " | " <<
				std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | " <<
				std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | " <<
				std::setw(4) << std::right << std::setfill(' ') << m_itemsInStock << " | " <<
				std::left << m_desc;
		}
		os << std::endl;
	}


}