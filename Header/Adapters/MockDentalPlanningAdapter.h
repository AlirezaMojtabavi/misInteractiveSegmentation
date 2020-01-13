#pragma once
#include "IDentalPlanningAdapter.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockDentalPlanningAdapter, IDentalPlanningAdapter)
	{
		MOCK_NON_CONST_METHOD(SequenceActivated, 0, void());
		MOCK_NON_CONST_METHOD(SequenceDeactivated, 0, void());
		MOCK_NON_CONST_METHOD(ImageTreeViewClicked, 1, void(const ImageInformationStrct& itemInfo));
		MOCK_NON_CONST_METHOD(AddPlanClicked, 0, void());
		MOCK_NON_CONST_METHOD(ViewerAddLanmarkEvent, 1, void(const misLandmarkInfoStruct& lndStr));
		MOCK_NON_CONST_METHOD(ViewerModifyScrewWidget, 1, void(const misScrewWidgetData& screwWidgetVal));
		MOCK_NON_CONST_METHOD(ApproachandModelTreeViewClicked, 1, void(const ApproachAndModelInformationStrct& itemInfo));
		MOCK_NON_CONST_METHOD(DeletePlanSelected, 0, void());
		MOCK_NON_CONST_METHOD(SetScrewDiameter, 1, void(double screwWidth));
		MOCK_NON_CONST_METHOD(SetPlanVisibility, 1, void(bool visible));
		MOCK_NON_CONST_METHOD(NewPanoramicCurve, 0, void());
		MOCK_NON_CONST_METHOD(AcceptPanoramicCurve, 1, void(const ISplineVisualizer::SplinePoints& splinePts));
		MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double angle));
	};
}
