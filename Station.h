

#ifndef SENECA_STATION_H
#define SENECA_STATION_H


#include <string>
#include <iostream>
#include <iomanip>

namespace utils
{
	class Station 
	{

		int station_id;
		std::string item_name;
		std::string station_desc;
		unsigned int number_item;
		unsigned int current_stock;
		static size_t m_widthField;
		static int id_generator;

	public:
		Station();
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;


	};

}
#endif // SENECA_STATION_H