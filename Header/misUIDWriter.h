#pragma once

#include "misLicenseStrct.h"

class misUIDWriter
{
public:
	misUIDWriter(void);
	~misUIDWriter(void);
	static std::string XmlGeneratedUIDs( misUIDForLicenseStrct UIDsInfo );
};

