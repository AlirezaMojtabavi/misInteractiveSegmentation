#pragma once

#include "serializable.h"

class misAuthenticationSettings : public Serializable
{
public:
	misAuthenticationSettings(void);
	
	std::string GetUsersRegistryFilePath() const;
	std::string GetDefaultUserId() const;
	std::string GetLogonUserId() const;
	std::string GetPreferencesFileName() const;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

private:
	std::string m_UsersRegistryFilePath;
	std::string m_DefaultUserId;
	std::string m_LogonUserId;
	std::string m_PreferencesFileName;
};

