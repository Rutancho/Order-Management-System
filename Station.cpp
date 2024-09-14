

#include "Station.h"
#include "Utilities.h"

namespace utils
{

	 size_t Station::m_widthField = 0;

	 int Station::id_generator = 0;

	Station::Station()
	{
		station_id = {};
		item_name = {};
		 station_desc = {};
		 number_item = {};
		 current_stock = {};
		
	}

	Station::Station(const std::string& record) : Station()
	{
		Utilities util;
		bool more = true;
		size_t next_pos = 0;
		Station::id_generator++;  
		station_id = id_generator;

		item_name = util.extractToken(record, next_pos, more);

			if (more)
			{
				number_item = stoi(util.extractToken(record, next_pos, more));
				
			}

			if (more)
			{
				current_stock = stoi(util.extractToken(record, next_pos, more));
			}

			if (Station::m_widthField < util.getFieldWidth()) 
			{
				Station::m_widthField = util.getFieldWidth();
			}

			if (more)
			{
				station_desc = util.extractToken(record, next_pos, more);

			}

			
	}

	const std::string& Station::getItemName() const
	{
		return item_name;
	}

	size_t Station::getNextSerialNumber()
	{
		return number_item++;
	}
	size_t Station::getQuantity() const
	{
		return current_stock;
	}

	void Station::updateQuantity()
	{
		if (current_stock > 0)
		{
			current_stock--;
		}

	}


	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setfill('0') << std::right << std::setw(3) << station_id << " | " << std::setfill(' ');

		os << std::left << std::setw(m_widthField) << item_name << " | " << std::setfill('0') << std::right << std::setw(6) << number_item << " | " << std::setfill(' ');

		if (full)
		{
			os << std::setw(4) << current_stock << " | " << std::left << station_desc << std::endl;
		}
		else 
		{
			os << std::endl;
		}
	}

}
