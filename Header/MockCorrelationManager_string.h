#pragma once

#include <ICoordinateSystemCorrelationManager.h>

using ICorrelationManager_string = ICoordinateSystemCorrelationManager<std::string>;

MOCK_BASE_CLASS(MockCorrelationManager_string, ICorrelationManager_string)
{
	MOCK_NON_CONST_METHOD(SetTransform, 3, void(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform));

	MOCK_NON_CONST_METHOD(SetTransform, 3, void(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TimedTransformConstPtr transform),
		SetTransform_Timed);

	MOCK_NON_CONST_METHOD(RemoveTransform, 2, void(const CoordinateSystemType & source, const CoordinateSystemType &destination));

	MOCK_CONST_METHOD(GetTransform, 2, ComputedCorrelationConstPtr(
		const CoordinateSystemType &source, const CoordinateSystemType &destination));

	MOCK_NON_CONST_METHOD(ConcatTransform, 3, void(
		const CoordinateSystemType &source, const CoordinateSystemType &destination, TransformConstPtr transform));

	MOCK_NON_CONST_METHOD(DecatTransform, 2, void(const CoordinateSystemType & source, const CoordinateSystemType &destination));
	MOCK_CONST_METHOD(GetDirectCorrelationsList, 0, std::list<DirectCorrelation>());
	MOCK_NON_CONST_METHOD(SetDirectCorrelationsList, 1, void(const std::list<DirectCorrelation>& newList));
	MOCK_NON_CONST_METHOD(PurgeInvalidCorrelations, 0, void());
};