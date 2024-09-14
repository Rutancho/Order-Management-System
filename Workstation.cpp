

#include <iostream>
#include <deque>
#include <ostream>
#include <string>
#include "Workstation.h"
#include "Station.h"
#include "CustomerOrder.h"

namespace utils
{
	 std::deque<CustomerOrder> g_pending;
	 std::deque<CustomerOrder> g_completed;
	 std::deque<CustomerOrder> g_incomplete;

	 Workstation::Workstation(const std::string& str) : Station(str) {};


	 void Workstation::fill(std::ostream& os)
	 {
		 if (!m_orders.empty())
		 {
			 m_orders.front().fillItem(*this, os);
		 }
	 }

	 bool Workstation::attemptToMoveOrder()
	 {
		 bool move_order = false;

		 if (m_orders.size() > 0)
		 {
			 if (m_orders.front().isOrderFilled() || (m_orders.front().isItemFilled(getItemName()) || getQuantity() < 1))
			 {
				 if (m_pNextStation)
				 {
					 m_pNextStation -> operator+=(std::move(m_orders.front()));
				 }
				 else if (m_orders.front().isOrderFilled())
				 {
					 g_completed.push_back(std::move(m_orders.front()));
				 }
				 else
				 {
					 g_incomplete.push_back(std::move(m_orders.front()));
				 }
				 m_orders.pop_front();
				 move_order = true;
			 }

		 }
		 return move_order;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;

	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (m_pNextStation)
		{
			os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl; 
		}
		else
		{
			os << getItemName() << " --> " << "End of Line" << std::endl;
		}

	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));

		return *this;
	}


}