#pragma once


#include "misLicenseStrct.h"

class   misSoftwareLicenseReader
{
private:
	TiXmlDocument* m_pDocument;
	TiXmlElement*  m_Root;

	misUIDForLicenseStrct  m_UIDsInfo;
	LicenseInformation     m_LicenseData;
	std::string                 m_FileName;

	std::string ReadFile(void);
	
public:

	LicenseInformation    GetLicenseData() const;
	misUIDForLicenseStrct GetUIDsData() const;

	misSoftwareLicenseReader(void);
	bool CheckLicense        (std::string  filename);
	bool CheckUIDsInformation(std::string  filename);

	~misSoftwareLicenseReader(void);	
};

 
