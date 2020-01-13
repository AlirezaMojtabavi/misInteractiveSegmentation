#pragma once

#include <turtle/mock.hpp>

#include "IImageSliceViewSettings.h"

MOCK_BASE_CLASS(MockSelectorSlicePlaneExtractor, IImageSliceViewSettings)
{
	MOCK_CONST_METHOD(GetPlaneAndBoxConfig, 0, const misPlaneAndBoxConfiguration& ())
	MOCK_NON_CONST_METHOD(SetPlaneAndBoxConfig, 1, void (const misPlaneAndBoxConfiguration &))
	MOCK_CONST_METHOD(GetViewPlaceholder, 0, ViewPlaceholderType ())
	MOCK_NON_CONST_METHOD(SetViewPlaceholder, 1, void (ViewPlaceholderType))
	MOCK_CONST_METHOD(IsOblique, 0, bool ())
	MOCK_NON_CONST_METHOD(SetIsOblique, 1, void (bool))
	MOCK_NON_CONST_METHOD(GetImageSliceQuad, 0, misQuadGeometry ())
	MOCK_NON_CONST_METHOD(GetViewUpVector, 0, VectorType ()
	MOCK_CONST_METHOD(GetPlaneNormalVector, 0, const VectorType& ())
	MOCK_NON_CONST_METHOD(SetPlaneNormalVector, 1, void (const VectorType &))
	MOCK_CONST_METHOD(GetViewUpCalculationMode, 0, ViewUpCalculationMode ())
	MOCK_NON_CONST_METHOD(SetViewUpCalculationMode, 1, void (ViewUpCalculationMode))
};