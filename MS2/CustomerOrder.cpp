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
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds
{
	//Initialization of Class Variables
	size_t CustomerOrder::m_widthField{};

	//Custom Constructor
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		//Use Utilities object to extract the tokens from string and populate the current instance.
		//The fields in the string are separated by a delimiter
		Utilities utils;
		size_t pos = 0;
		bool isMore = true;

		std::string itemName{};
		Item** tempArr{ nullptr };

		//Extract Order Customer Name
		m_name = utils.extractToken(str, pos, isMore);

		//Extract product being assembled
		m_product = utils.extractToken(str, pos, isMore);

		//Create Item objects
		while (isMore) {
			itemName = utils.extractToken(str, pos, isMore);
			Item* oneItem = new Item(itemName);
			//Item oneItem(itemName);
			m_cntItem++;

			if (m_lstItem != nullptr) {
				//Create a new array of pointers to Items to save the current pointers
				tempArr = new Item * [m_cntItem - 1];
				//Copy each pointer to item to temporary array
				for (auto i = 0u; i < m_cntItem - 1; ++i) {
					tempArr[i] = m_lstItem[i];
				}

				//Steps to Resize Array of Pointers
				//Step 1. Delete current array of pointers to Items
				//(now we have the pointers saved in the temporary Array
				//delete m_lstItem[0];
				delete[] m_lstItem;

				//Step 2. Create a new array of pointers of the new required size
				m_lstItem = new Item * [m_cntItem];

				//Step 3. Copy current addresses from temporary array (old size array) to new size array
				for (auto i = 0u; i < m_cntItem - 1; ++i) {
					m_lstItem[i] = tempArr[i];
				}

				//Step 4. Add address of oneItem to the end of new size array of pointers
				m_lstItem[m_cntItem - 1] = oneItem;

				//Step 5. Deallocate memory used for temporary array
				delete[] tempArr;

			}
			else {
				m_lstItem = new Item * [m_cntItem];
				m_lstItem[0] = oneItem;
			}

		}
		
		if (m_widthField < utils.getFieldWidth()) {
		//if (m_widthField < m_product.length()) {
				m_widthField = m_product.length();
		}
	}

	//Copy Constructor
	CustomerOrder::CustomerOrder(const CustomerOrder& orig)
	{
		throw "EXC. Copy Constructor not allowed!";
	}

	//Move Constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& orig) noexcept
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
		
		//Calling Move Assignment Operator
		*this = std::move(orig);
	}

	//Move Assignment Operator
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& orig) noexcept
	{
		//1. CHECK FOR SELF ASSIGNMENT
		if (this != &orig) {
			//2. CLEANUP TO GUARANTEE THIS ALWAYS WORKS
			for (auto i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			//3. SHALLOW MOVE
			m_name = orig.m_name;
			orig.m_name = "";

			m_product = orig.m_product;
			orig.m_product = "";

			m_cntItem = orig.m_cntItem;
			orig.m_cntItem = 0;

			//4. DEEP MOVE
			m_lstItem = orig.m_lstItem;
			orig.m_lstItem = nullptr;
		}
		return *this;
	}

	//Destructor
	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
	}

	//Returns true if all the items in the order have been filled
	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;
		
		for (auto i = 0u; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				result = false;
			}
		}

		return result;
	}

	//Returns true if all items specified by itemName have been filled
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result{};

		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName) {
					result = m_lstItem[i]->m_isFilled ? true : false;
			}
			else {
				//If the item does not exist in the order, this query returns true
				result = true;
			}
		}

		return result;
	}

	//Fills one item in the current order that the Station specified in the first parameter handles
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		size_t itemsNeeded{};
		size_t itemsHanded{};

		for (auto i = 0u; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				itemsNeeded++;
			}
		}

		//Search for the item handled by station in the order
		for (auto i = 0u; i < m_cntItem; ++i) {
			//Check if the item handled by the station exists in the order
			if (m_lstItem[i]->m_itemName == station.getItemName()) {

				//Check if item has not been filled
				if (!m_lstItem[i]->m_isFilled) {

					//Check if Station's inventory contains at least one item
					if (station.getQuantity() > 0) {

						//Fill the order with one single item from the station
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						itemsHanded++;
						if (itemsHanded == itemsNeeded) {
							m_lstItem[i]->m_isFilled = true;
							os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
						}

					}
					else { //Station's inventory is empty
						os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;

					}
				}
				
			} //If the order doesn't contain the item handled, this function does nothing
		}

	}

	//Displays the state of the current object
	void CustomerOrder::display(std::ostream& os) const
	{
		//Format:
		//CUSTOMER_NAME - PRODUCT
		//[SERIAL] ITEM_NAME - STATUS
		//[SERIAL] ITEM_NAME - STATUS
		//...

		os << m_name << " - " << m_product << std::endl;
		for (auto i = 0u; i < m_cntItem; ++i) {

			if (m_lstItem[i]->m_isFilled) {
				os << "[" << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] "
					<< std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - "
					<< "FILLED" << std::endl;
			}
			else {
				os << "[" << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] "
					<< std::setfill(' ') << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << "   - "
					<< "TO BE FILLED" << std::endl;
			}



		}

	}




}