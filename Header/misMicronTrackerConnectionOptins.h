#pragma once
#include "misToolProperties.h"
#include "misProjectSettingMacro.h"

struct MISPROJECTSETTINGLIBEXPORTS misMicronTrackerConnectionOptins : public Serializable
{
	std::string NameOFiniFile;
	std::string m_DriverName;

	misToolPropertiesListTypdef ToolList;

	misMicronTrackerConnectionOptins();

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);	
};

