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
#include <iostream>
#include "Workstation.h"
#include "Station.h"

namespace sdds
{

	//Custom Constructor
	Workstation::Workstation(const std::string& str) : Station(str)
	{
		//Receives a reference to an unmodifiable reference to std::string and passes it to the Station base class.
	}

	//Fills the order at the front of the queue if there are CustomerOrders in the queue
	void Workstation::fill(std::ostream& os)
	{
		if (m_orders.size() > 0) {
			m_orders.front().fillItem(*this, os);
		}
		
	}

	//Attemps to move the order at the front of the queue to the next station in the assembly line
	bool Workstation::attemptToMoveOrder()
	{
		bool orderMoved{}; //If an order has been moved, return true; false otherwise

		//If the order requires no more service at this station or cannot be filled (not enough inventory), move it to the next station;
		if (!m_orders.empty()) {
			CustomerOrder& order = m_orders.front();

			if (order.isItemFilled(getItemName()) == true || this->getQuantity() < 1) {

				if (m_pNextStation != nullptr) {
					
					//Move the order to the next station
					*m_pNextStation += std::move(order);
	
				}
				else { //If there is no next station in the assembly line, then the order is moved into g_completed or g_incomplete queue
					if (order.isOrderFilled()) {
						g_completed.push_back(std::move(order));
					}
					else {
						g_incomplete.push_back(std::move(order));
					}
				}
				m_orders.pop_front();
				orderMoved = true;


			} // otherwise do nothing
		}
		

		return orderMoved;
	}

	//Stores the address of the referenced Workstation object in the pointer to the m_pNextStation
	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	//Returns the address of next Workstation
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	//Inserts the name of the Item for which the current object is responsible into stream os
	void Workstation::display(std::ostream& os) const
	{
		if (getNextStation() != nullptr) {
			//ITEM_NAME --> NEXT_ITEM_NAME
			os << this->getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
		else {
			//If the current object is the last Workstation in the assembly line this query inserts:
			//ITEM_NAME --> End of Line
			os << this->getItemName() << " --> End of Line" << std::endl;
		}

	}

	//Moves the CustomerOrder referenced in parameter newOrder to the back of the queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}



}