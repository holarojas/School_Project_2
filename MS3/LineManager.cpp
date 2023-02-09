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
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"

namespace sdds
{
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	//Custom Constructor
	//Receives the name of the file that identifies the active stations on the assembly line
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream f(file);

		if (!f) {
			throw std::string("Unable to open [") + file + "] file.";
		}

		std::string record{};
		std::string nameWS{};
		size_t foundPipe{};

		while (!f.eof())
		{
			std::getline(f, record);

			//Find if the line has a | character
			foundPipe = record.find('|');
			if (foundPipe != std::string::npos) {
				nameWS = record.substr(0, foundPipe);

				//Find the address of the Station found in the file and assign it to the LineManager collection
				std::for_each(stations.begin(), stations.end(), [&nameWS, this](Workstation* elem) {
					if (elem->getItemName() == nameWS) {
						m_activeLine.push_back(elem);
					}
					});

				nameWS = record.substr(foundPipe + 1);

				//Find the address of the Next Station found in the file and assign it to the Workstation attribute
				std::for_each(stations.begin(), stations.end(), [&nameWS, this](Workstation* elem) {
					if (elem->getItemName() == nameWS) {
						m_activeLine[m_activeLine.size() - 1]->setNextStation(elem);
					}
					});
			}
			else {
				//Find the address of the Station found in the file and assign it to the LineManager collection
				std::for_each(stations.begin(), stations.end(), [&nameWS, this](Workstation* elem) {
					if (elem->getItemName() == nameWS) {
						m_activeLine.push_back(elem);
					}
					});

				//Set the nextStation to nullptr
				m_activeLine[m_activeLine.size() - 1]->setNextStation(nullptr);

			}


		}

		//Find the first station in the assembly line
		auto firstStation = std::find_if(stations.begin(), stations.end(), [&stations](Workstation* elem) {
			bool elemIsFirst = true;

			//Search for "elem" in the m_pNextStation attribute for each Workstation. If it's found, it means this "elem" is not the first one.
			std::for_each(stations.begin(), stations.end(), [&elem, &elemIsFirst](Workstation* compare) {
				if (elem == compare->getNextStation()) {
					elemIsFirst = false;
				}
				});

			return elemIsFirst;
			});

		m_firstStation = *firstStation;

		//Update the attribute that holds the total number of orders in the g_pending deque
		m_cntCustomerOrder = g_pending.size();

		//TODO: If something goes wrong, this constructor reports an error

		f.close();
	}

	//Reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> temp;
		Workstation* currentStation{ nullptr };
		
		//The elements in the reordered collection start with the first station.
		currentStation = m_firstStation;
		
		//Get the ordered assembly line into the temp vector
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&temp, &currentStation](const Workstation* elem ) {
			temp.push_back(currentStation);
			currentStation = currentStation->getNextStation();
			});
		
		//Copy the temp vector to the original assembly line 
		m_activeLine = temp;
	}

	static size_t runCnt{};

	//Performs one iteration of operations on all the workstations in the current assembly line
	bool LineManager::run(std::ostream& os)
	{
		bool result{};
		//How many times this function has been called by the client
		runCnt++;

		//Inserts into stream os the iteration number
		os << "Line Manager Iteration: " << runCnt << std::endl;

		//Moves the order at the front of g_pending queue to the m_firstStation, and remove it from the queue
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* elem) {

			//For each station on the line, executes one fill operation
			elem->fill(os);	});

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* elem) {

			//For each station on the line, attempts to move an order down the line
			elem->attemptToMoveOrder();

			});


		//Return true if all customer orders have been filled or cannot be filled, otherwise returns false
		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder ) {
			result = true;
		}

		return result;
	}

	//Displays all active stations on the assembly line in their current order
	void LineManager::display(std::ostream& os) const
	{
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* elem) {
			elem->display(os);
			});
	}


}