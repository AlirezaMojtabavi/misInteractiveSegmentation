#pragma once


class SubtabsPriorityChecker
{
public:
	explicit SubtabsPriorityChecker(std::string current);

	bool operator <(SubtabsPriorityChecker const& c2);
	std::string GetSubtab() const;

private:
	std::map<std::string, unsigned int> m_PriorityMap;
	std::string m_Subtab = "default";
};




