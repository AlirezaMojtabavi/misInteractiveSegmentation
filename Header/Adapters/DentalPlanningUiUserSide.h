#pragma once

#include "IDentalPlanningUiUserSide.h"
#include "ISplineVisualizer.h"
#include <memory>

namespace itk
{
	class Object;
	class EventObject;
}

namespace parcast
{
	class IDentalPlanningAdapter;
	class IPackageRepo;
	class IPlanRepo;
	class IPlanningGroupViewer;

	class DentalPlanningUiUserSide : public IDentalPlanningUiUserSide
	{
	public:
		DentalPlanningUiUserSide(
			std::shared_ptr<IDentalPlanningAdapter> planningAdapter,
			std::shared_ptr<IPlanningGroupViewer> groupViewer,
			std::shared_ptr<IPackageRepo> packageRepo,
			std::shared_ptr<IPlanRepo> planRepo,
			std::shared_ptr<ISplineVisualizer> splineVisualizer);
		~DentalPlanningUiUserSide();

		void OnSelected() override;
		void ImageTreeViewClicked(const ImageInformationStrct& imageInfo) override;
		void ApproachAndModelTreeViewClicked(const ApproachAndModelInformationStrct& modelInfo) override;
		void CreateNewScrew() override;
		void TaskOnLeave() override;
		void DeletePlanSelected() override;
		void SetPlanVisibility(bool visible) override;
		void SetScrewDiameter(double screwWidth) override;
		void SetPlanCentricViewAngle(double angle) override;
		void NewPanoramicCurve() override;
		void AcceptPanoramicCurve() override;

	private:
		void GroupViewerEventHander(const itk::Object *caller, const itk::EventObject& pEvent);

		std::shared_ptr<IDentalPlanningAdapter> m_PlanningAdapter;
		std::shared_ptr<IPlanningGroupViewer> m_GroupViewer;
		std::shared_ptr<IPackageRepo> m_PackageRepo;
		std::shared_ptr<IPlanRepo> m_PlanRepo;
		std::shared_ptr<ISplineVisualizer> m_SplineVisualizer;
	};

}
