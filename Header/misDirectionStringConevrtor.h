#pragma once
#include "misViewerTypeDirection.h"
class misDirectionStringConevrtor
{
public:
	misDirectionStringConevrtor();

	 misViewerTypeDirection ConvertStringToDirection(std::string direction);
	std::string ConvertDirectionToString(misViewerTypeDirection m_ViewerTypeDirection);
private:
	std::map<std::string, misViewerTypeDirection> stringToDirection;
	std::map<misViewerTypeDirection, std::string> directionToString;
};

