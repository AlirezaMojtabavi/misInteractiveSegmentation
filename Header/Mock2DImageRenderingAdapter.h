#pragma once

#include "I2DImageRenderingAdapter.h"

MOCK_BASE_CLASS(Mock2DImageRenderingAdapter, I2DImageRenderingAdapter)
{
	MOCK_NON_CONST_METHOD(ShowImages, 5, void(std::shared_ptr<IImage> , bool, std::shared_ptr<IImage> , bool, double ));
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(SetImage, 2, void(std::shared_ptr<IImage> , double ), SetImage_Overload_1);
	MOCK_NON_CONST_METHOD(SetImage, 3, void(misLayerEnum , std::shared_ptr<IImage> , double ), SetImage_Overload_2);
	MOCK_NON_CONST_METHOD(SetNextImage, 4, void(misPlaneEnum , misLayerEnum , std::shared_ptr<IImage> , double ), SetNextImage_Overload_1);
	MOCK_NON_CONST_METHOD(SetNextImage, 3, void(misPlaneEnum , std::shared_ptr<IImage> , double ), SetNextImage_Overload_2);
	MOCK_NON_CONST_METHOD(GetCurrentWindowLevel, 1, misWindowLevelStr(misUID ));
	MOCK_CONST_METHOD(GetCorrespondingPlaneIndex, 1, misPlaneEnum(misUID ));
	MOCK_NON_CONST_METHOD(SetWidgetType, 1, void(misCursorType ));
};
