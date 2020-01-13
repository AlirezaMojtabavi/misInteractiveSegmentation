#pragma once
#include "IUpdateLandmarkCameraView.h"

class misUpdateplanningLandmarkView:public IUpdateLandmarkCameraView
{
public:
	void Update(itk::BoundingBox<double, 3, double>::Pointer, std::shared_ptr<ILandmarkPointerRepresentation>) override;
};
