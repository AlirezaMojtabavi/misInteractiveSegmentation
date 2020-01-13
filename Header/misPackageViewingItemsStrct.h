#pragma once

#include "misGuiStructures.h"
#include "misStringTools.h"
#include "misShort3DModelViewingStrct.h"

class misPackageViewingItemsStrct
{
public:
	std::string name;
	misUID packegeUID;
	MisObjectType packageType;
	std::vector<misShortImageViewingStrct> imageProperties;
	std::vector<misShortImageContainedPolydataViewingStrct> imageContainedProperties;
	std::vector<misShort3DModelViewingStrct> polyaDataProperties;
	std::vector<misShort3DModelViewingStrct> planningDataProperties;
	std::vector<misShort3DModelViewingStrct> fmriDataProperties;

};

typedef  std::vector< misPackageViewingItemsStrct >    PackageViewingListTypedef;
