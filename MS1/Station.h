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
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds
{
	//A Station object manages a single station on the assembly line. Each station handles a specific item for filling customer
	class Station
	{
		//Instance Variables
		int m_id{};						//ID of the station
		std::string m_itemName{};		//Name of the item handled by the station
		std::string m_desc{};			//Description of the station
		unsigned int m_serialNumber{};	//Next serial number to be assigned to an item at this station
		unsigned int m_itemsInStock{};	//Number of items currently in stock

		//Class Variables
		static size_t m_widthField;		//Maximum number of characters required to print to the screen the item name for any object of type Station.
		static int id_generator;		//Variable used to generate IDs for new instances of type Station.

	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H

