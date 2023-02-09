/*----------------------------------------------
// FINAL PROJECT
------------------------------------------------
Name:	Martha Rocio Rojas Martinez
Mail:	mrrojas - martinez@myseneca.ca
ID:		112073218
Date:	Dec 03rd, 2022
------------------------------------------------
// I confirm that I am the only author of this
// file and the content was created entirely
// by me.
---------------------------------------------- */
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

namespace sdds
{
	//The Workstation module consists of three double-ended queues of CustomerOrder and the Workstation class.
	
	//The queues (global variables) hold the orders at either end of the assembly line
	extern std::deque<CustomerOrder> g_pending;		//Holds the orders to be placed onto the assembly line at the first station
	extern std::deque<CustomerOrder> g_completed;		//Holds the orders that have been removed from the last station and have been completely filled
	extern std::deque<CustomerOrder> g_incomplete;		//Holds the orders that have been removed from the las station and could not be filled completely

	//Defines the structure of an active station on the assembly line and contains all the functionality for filling customer orders with station items
	//A Workstation object represents a single location on the assembly line for filling customer orders with items
	class Workstation : public Station
	{
		//Instance Variables
		std::deque<CustomerOrder> m_orders{}; //Entering the back and exiting the front. These are orders that have been placed on this station to receive service (or already received service)
		Workstation* m_pNextStation{ nullptr }; //Pointer to the next Workstation on the assembly line

	public:
		Workstation(const std::string& str);

		Workstation(const Workstation& orig) = delete; //Object cannot be copied
		Workstation& operator=(const Workstation& orig) = delete; //Object cannot be copied
		Workstation(const Workstation&& orig) = delete; //Object cannot be moved
		Workstation& operator=(Workstation&& orig) = delete; //Object cannot be moved

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}


#endif // !SDDS_WORKSTATION_H

