#pragma once
#include "misLicenseStrct.h"
class misLicWriter
{
public:
	misLicWriter(void);
	~misLicWriter(void);
	static std::string XmlGeneratedLicense( LicenseInformation licenseInfo );
};

