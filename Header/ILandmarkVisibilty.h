#pragma once
#include "ILandmarkPointerRepresentation.h"

class ILandmarkVisibilty
{
public:
	typedef std::vector < std::shared_ptr < ILandmarkPointerRepresentation >> LandmarkListType;
	virtual void CheckVisibility(const LandmarkListType& landMarkList) const = 0;
};
