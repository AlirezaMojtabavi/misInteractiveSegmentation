#pragma once
#include "IRepresentation.h"
#include "ILandmarkPointerRepresentation.h"

class IUpdateLandmarkCameraView
{
public:
	virtual ~IUpdateLandmarkCameraView() = default;
	virtual void Update(itk::BoundingBox<double, 3, double>::Pointer, std::shared_ptr<ILandmarkPointerRepresentation> ) = 0;
};
