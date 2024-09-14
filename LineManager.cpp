

#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"

namespace utils
{

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::fstream filestream(file, std::ios::in | std::ios::out);


        if (filestream.is_open()) {
            std::string line;
            while (std::getline(filestream, line)) {
                if (line.find('|') != std::string::npos) {
                    size_t delim = line.find('|');
                    std::string workstation, next_workstation;
                    workstation = line.substr(0, delim);
                    next_workstation = line.substr(delim + 1);
                    auto fit = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                        return station->getItemName() == workstation;
                        });
                    if (fit != stations.end()) {
                        m_activeLine.push_back(*fit);
                    }
                    else {
                        std::cerr << "STATION NOT FOUND" << std::endl;
                    }

                    auto nextIt = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                        return station->getItemName() == next_workstation;
                        });

                    if (nextIt != stations.end() && fit != stations.end()) { // Check if both iterators are valid
                        m_activeLine.back()->setNextStation(*nextIt);
                    }
                    else {
                        std::cerr << "STATION NOT FOUND" << std::endl;
                    }
                }
                else {
                    auto it = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                        return station->getItemName() == line;
                        });

                    if (it != stations.end()) {
                        m_activeLine.push_back(*it);
                    }
                    else {
                        std::cerr << "STATION NOT FOUND" << std::endl;
                    }
                }

                auto first = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) {
                        return other != station && other->getNextStation() == station;
                        });
                    });

                if (first != stations.end()) {
                    m_firstStation = *first;
                }
                else {
                    std::cerr << "STATION NOT FOUND" << std::endl;
                }
            }
            m_cntCustomerOrder = g_pending.size();
        }
        else {
            throw std::string("File \"" + file + "\" cannot be opened. Retry with another filename.");
        }
    }


	void LineManager::reorderStations()
	{
		m_activeLine.clear();

		Workstation* current_station = m_firstStation;

		while (current_station != nullptr)
		{
			m_activeLine.push_back(current_station);
			current_station = current_station->getNextStation();
		}



	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t count = 0;

		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty())
		{
			/*m_firstStation += std::move(g_pending.front());*/
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station)
			{
			station->fill(os);
			});
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) 
			{
			station->attemptToMoveOrder();
			});
		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;

	}

	void LineManager::display(std::ostream& os) const
	{
		for (Workstation* station : m_activeLine)
		{
			station->display(os);
		}
	}




}