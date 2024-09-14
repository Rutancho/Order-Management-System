
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <utility>
#include <iomanip>
#include <iostream>
#include <string>
#include "Station.h"

namespace utils
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;

	public:
		CustomerOrder();	
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& cus);
		CustomerOrder& operator=(const CustomerOrder& c) = delete;
		CustomerOrder(CustomerOrder&& cus) noexcept;
		CustomerOrder& operator=(CustomerOrder&& cus) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};

}
#endif 