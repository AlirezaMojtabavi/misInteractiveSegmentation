#pragma once

struct ApproachAndModelInformationStrct;
struct ImageInformationStrct;

namespace parcast
{

	class IDentalPlanningUiUserSide
	{
	public:
		virtual ~IDentalPlanningUiUserSide() = default;

		virtual void OnSelected() = 0;
		virtual void TaskOnLeave() = 0;
		virtual void ImageTreeViewClicked(const ImageInformationStrct& imageInfo) = 0;
		virtual void ApproachAndModelTreeViewClicked(const ApproachAndModelInformationStrct& modelInfo)= 0;
		virtual void CreateNewScrew() = 0;
		virtual void DeletePlanSelected() = 0;
		virtual void SetPlanVisibility(bool visible) = 0;
		virtual void SetScrewDiameter(double screwWidth) = 0;
		virtual void SetPlanCentricViewAngle(double angle) = 0;
		virtual void NewPanoramicCurve() = 0;
		virtual void AcceptPanoramicCurve() = 0;
	};

}
