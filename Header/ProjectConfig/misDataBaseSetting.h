#pragma once
#include "misEnums.h"
#include "serializable.h"

struct misDataBaseSetting : public Serializable
{
	bool LoggerEnabled;
	bool forceToSaveAllContianedOfSoluion;
	std::string ConnectionStringDataSource;
	misSaveSolutionMode SavingMode;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};
