#pragma once

#include "ITrackerImageSynchronizer.h"


MOCK_BASE_CLASS(MockTrackerImageSynchronizer, ITrackerImageSynchronizer)
{
	MOCK_NON_CONST_METHOD(SetToolPosition, 1, void(double* center));
	MOCK_NON_CONST_METHOD(AddTool, 1, void(std::shared_ptr<ITrackingTool> toolData));
	MOCK_NON_CONST_METHOD(SetRenderingToolSceneReference, 1, void(std::string refernce));
	MOCK_NON_CONST_METHOD(SetToolTransform, 1, void(vtkMatrix4x4* toolTransform));
	MOCK_NON_CONST_METHOD(UpdateVirtualTipLength, 1, void(double lenght));
	MOCK_NON_CONST_METHOD(ShowTorus, 1, void(bool visibility));
	MOCK_NON_CONST_METHOD(SetViewers, 1, void(std::map<std::shared_ptr<IVolumeRenderer>, ToolVisulizationProp>  val));
	MOCK_NON_CONST_METHOD(Freeze, 0, void());
	MOCK_NON_CONST_METHOD(SetPanoramicTransformConvertor, 1, void(std::shared_ptr<IPanoramicTransformConverter> val));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinateConverter, 1, void(std::shared_ptr<IPanoramicCoordinatesConverter> val));
	MOCK_NON_CONST_METHOD(Unfreeze, 0, void());
	MOCK_NON_CONST_METHOD(AddExistingRepresentation, 0, void());
	MOCK_NON_CONST_METHOD(ClearViewers, 0, void());
};

