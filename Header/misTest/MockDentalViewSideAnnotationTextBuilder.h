#pragma once

#include "IDentalViewSideAnnotationTextBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDentalViewSideAnnotationTextBuilder, IDentalViewSideAnnotationTextBuilder)
	{
		MOCK_NON_CONST_METHOD(SetViewerType, 1, void(ViewerType viewerType));
		MOCK_NON_CONST_METHOD(SetHasCurve, 1, void(bool hasCurve));
		MOCK_NON_CONST_METHOD(SetDentalQuadrant, 1, void(DentalQuadrant quadrant));
		MOCK_CONST_METHOD(GetSideAnnotations, 0, SideAnnotations());
	};

}
