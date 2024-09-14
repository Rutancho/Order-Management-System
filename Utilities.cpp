

#include "Utilities.h"

namespace utils
{
	  char Utilities::m_delimiter = ' ';

	Utilities::Utilities()
	{
		m_widthField = 1;

	}

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string save_str;

		if (more)
		{
			if (next_pos >= str.length())
			{
				more = false;
				throw "Invaild Location";
			}
			if (str[next_pos] == m_delimiter)  
			{
				more = false;
				throw "Invaild Location";
			}

			size_t temp = str.find(m_delimiter, next_pos);

			if (temp == std::string::npos)
			{
				save_str = str.substr(next_pos);
				more = false;
			}
			else
			{
				save_str = str.substr(next_pos, temp - next_pos);
				next_pos = temp + 1;
				more = true;
			}
			save_str = save_str.erase(0, save_str.find_first_not_of(' '));
			save_str = save_str.erase(save_str.find_last_not_of(' ')+1);
		}

		if (save_str.length() > m_widthField)
		{
			m_widthField = save_str.length();
		}

		return save_str;

	}

	void Utilities::setDelimiter(char newDelimiter)
	{

		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;

	}





}