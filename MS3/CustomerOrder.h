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
#ifndef SDDS_CUSTOMER_ORDER
#define SDDS_CUSTOMER_ORDER

#include "Station.h"

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) { };
		
	};

	//A Customer Order object manages a single  order on the assembly line
	class CustomerOrder
	{
		
		//Instance variables
		std::string m_name{};		//Name of the customer
		std::string m_product{};	//Name of the product being assembled
		size_t m_cntItem{};			//Count of the number of items in the customer's order
		Item** m_lstItem{nullptr};	//Dynamically allocated array of pointers. Each element points to a dynamically allocated object of type Item.

		//Class variables
		static size_t m_widthField; //Maximum width of a field , used for display purposes

	public:
		CustomerOrder() { };
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& orig); 
		CustomerOrder& operator=(const CustomerOrder& orig) = delete;
		CustomerOrder(CustomerOrder&& orig) noexcept;
		CustomerOrder& operator=(CustomerOrder&& orig) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMER_ORDER

