#pragma once
#include "ISplineVisualizer.h"
struct ApproachAndModelInformationStrct;
class misScrewWidgetData;
struct misLandmarkInfoStruct;
struct ImageInformationStrct;
namespace parcast
{
	class IDentalPlanningAdapter
	{

	public:
		virtual	~IDentalPlanningAdapter() = default;

		virtual void SequenceActivated() = 0;
		virtual void SequenceDeactivated() = 0;
		virtual void ImageTreeViewClicked(const ImageInformationStrct& itemInfo) = 0;
		virtual void AddPlanClicked() = 0;
		virtual void ViewerAddLanmarkEvent(const misLandmarkInfoStruct& lndStr) = 0;
		virtual void ViewerModifyScrewWidget(const misScrewWidgetData& screwWidgetVal) = 0;
		virtual void ApproachandModelTreeViewClicked(const ApproachAndModelInformationStrct& itemInfo) = 0;
		virtual void DeletePlanSelected() = 0;
		virtual void SetScrewDiameter(double screwWidth) = 0;
		virtual void SetPlanVisibility(bool visible) = 0;
		virtual void SetPlanCentricViewAngle(double angle) = 0;
		virtual void NewPanoramicCurve() = 0;
		virtual void AcceptPanoramicCurve(const ISplineVisualizer::SplinePoints& splinePts) = 0;
	};
}