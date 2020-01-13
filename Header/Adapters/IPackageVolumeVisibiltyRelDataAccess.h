#pragma once
#include "VolumeVisibility.h"

class IPackageVolumeVisibiltyRelDataAccess
{
public:
	virtual void Insert(const parcast::VolumeVisibility& data) = 0;
	virtual std::vector<parcast::VolumeVisibility> GetByVolumeUid(const std::string& uid) const = 0;
};