#pragma once

#include "IDentalPlanningAdapter.h"
#include "ISplineVisualizer.h"

namespace parcast
{
	class IPlanRepo;
	class IPackageRepo;
	class IDentalPlanning;

	class DentalPlanningAdapter : public IDentalPlanningAdapter
	{

	public:
		DentalPlanningAdapter(
			std::shared_ptr<IDentalPlanning> planning,
			std::weak_ptr<IPackageRepo> pkgRepo,
			std::weak_ptr<IPlanRepo> planRepo);

		void SequenceActivated() override;
		void SequenceDeactivated() override;
		void ImageTreeViewClicked(const ImageInformationStrct& itemInfo) override;
		void AddPlanClicked() override;

		void ViewerAddLanmarkEvent(const misLandmarkInfoStruct& lndStr) override;
		void ViewerModifyScrewWidget(const misScrewWidgetData& screwWidgetVal) override;
		
		void ApproachandModelTreeViewClicked(const ApproachAndModelInformationStrct& itemInfo) override;
		void DeletePlanSelected() override;

		void SetScrewDiameter(double screwWidth) override;
		void SetPlanVisibility(bool visible) override;
		
		void NewPanoramicCurve() override;
		void AcceptPanoramicCurve(const ISplineVisualizer::SplinePoints& splinePts) override;
		void SetPlanCentricViewAngle(double angle) override;

	private:
		std::shared_ptr<IDentalPlanning> m_Planning;
		std::shared_ptr<IPackageRepo> m_PackageRepo;
		std::shared_ptr<IPlanRepo> m_PlanRepo;
	};

}
