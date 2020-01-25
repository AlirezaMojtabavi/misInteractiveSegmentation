#pragma once
#include <misLandmarkenums.h>
#include "misSimplePointType.h"
#include "ILandmarkPointerRepresentation.h"
#include "IImage.h"

class ILandamrkListCategorizer
{
public:
	virtual ~ILandamrkListCategorizer() = default;
	virtual misSimplePointListType GetLandamrks(misLandmarkType lndType,
	                                           const std::vector<std::shared_ptr<ILandmarkPointerRepresentation>>&) = 0;
};
