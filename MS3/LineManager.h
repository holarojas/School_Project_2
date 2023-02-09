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
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include "Workstation.h"


namespace sdds
{

	//The LineManager class manages an assembly line of active stations
	class LineManager
	{
		//Instance Variables
		std::vector<Workstation*> m_activeLine{}; //The collection of workstations for the current assembly line
		size_t m_cntCustomerOrder{}; //The total number of CustomerOrder objects
		Workstation* m_firstStation{ nullptr }; //Points to the first active station on the current line

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_LINEMANAGER_H

