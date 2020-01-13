#pragma once

#include "IDentalPlanningUiAdapter.h"
#include "IDentalPlanningUiAppSide.h"
#include "misPackageViewingItemsStrct.h"
#include "IPackageViewingExtractorFactory.h"

namespace parcast
{

	class DentalPlanningUiAdapter : public IDentalPlanningUiAdapter
	{
	public:
		explicit DentalPlanningUiAdapter(
			std::shared_ptr<IDentalPlanningUiAppSide> UiAppSide,
			std::unique_ptr<IPackageViewingExtractorFactory> packageViewingExtractorFactory,
			std::shared_ptr<parcast::IPackagePlanRelRepo> packagePlanRelRepo);
		~DentalPlanningUiAdapter();

		void UpdateList(const std::vector<std::shared_ptr<ISimpleDataPackage>>& packages) override;
		void SetState(DentalPlanningStatus state) override;
		void SelectPlan(std::shared_ptr<IPlan> plan, bool refreshPkg) override;
		void SelectPackage(std::shared_ptr<ISimpleDataPackage> package) override;
		void UpdatePlan(std::shared_ptr<IPlan> plan) override;
		void UpdatePlanIndicators(const PlanIndicators& indicators) override;
		void SetPlanCentricViewAngle(double angle) override;

	private:
		const std::map<DentalPlanningStatus, std::string> StatesMap = {
			std::make_pair(DentalPlanningStatus::Initial, "StateInitialized"),
			std::make_pair(DentalPlanningStatus::ImageSelected, "ImageSelected"),
			std::make_pair(DentalPlanningStatus::DrawingCurve, "DrawingCurve"),
			std::make_pair(DentalPlanningStatus::AddingPlan, "StartNewApproach"),
			std::make_pair(DentalPlanningStatus::PlanSelected, "BothPointsSelected")};

		PackageViewingListTypedef CreateViewingList(const std::vector<std::shared_ptr<ISimpleDataPackage>>& packages) const;
		std::shared_ptr<IDentalPlanningUiAppSide> m_UiAppSide;
		std::unique_ptr<IPackageViewingExtractorFactory> m_PackageViewingExtractorFactory;
		std::shared_ptr<parcast::IPackagePlanRelRepo> m_PackagePlanRelRepo;
	};

}
