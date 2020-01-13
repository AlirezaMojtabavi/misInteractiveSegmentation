#pragma once

#include "IDentalViewVector.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockDentalViewVector, parcast::IDentalViewVector)
	{
		MOCK_CONST_METHOD(CalculateMesiodistalView, 0, ViewVectors());
		MOCK_CONST_METHOD(CalculateOcclusalView, 0, ViewVectors());
		MOCK_CONST_METHOD(CalculateBuccolingualView, 0, ViewVectors());
		MOCK_NON_CONST_METHOD(SetViewDirections, 2, void(const ViewVectors::VectorType& plan, 
			const ViewVectors::VectorType& mesiodistal));
		MOCK_NON_CONST_METHOD(SetRightViewAngularOffset, 1, void(double angle));
	};
}
