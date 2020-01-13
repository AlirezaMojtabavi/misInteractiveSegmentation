#pragma once

#include "IDentalPlanning.h"
#include "IDentalPlanningUiAdapter.h"
#include "IPlanFactory.h"

template < typename CST >
class ICoordinateSystemCorrelationManager;

namespace parcast
{
	class IPlanRepo;
	class IRootEntity;
	class IPackageConfirmer;
	class IPackagePlanRelRepo;

	class DentalPlanning : public IDentalPlanning
	{
	public:
		DentalPlanning(
			std::shared_ptr<IDentalPlanningUiAdapter> uiAdapter,
			IRootEntity *rootEntity,
			std::shared_ptr<IPlanRepo> planRepo,
			std::shared_ptr<IPackageConfirmer> confirmer,
			std::weak_ptr<IPackagePlanRelRepo> packagePlanRelRepo);

		void StartUp() override;
		void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> pkg) override;
		void SetCurrentPlan(std::shared_ptr<IPlan> plan) override;
		void CapturePoint(const Point<double, 3>& point) override;
		void EnableAddPlanMode() override;
		void ModifyPlan(std::shared_ptr<IPlan> plan, const PointType& startPoint, const PointType& endPoint) override;
		void NewSpline() override;
		void AcceptSpline(const SplinePoints& points) override;
		void SetScrewDiameter(double diameter) override;
		void SetScrewVisiblity(bool isVisible) override;
		void SetPlanCentricViewAngle(double angle) override;
		void DeletePlan() override;

	private:
		std::vector < std::shared_ptr<ISimpleDataPackage>> GetConfirmedPackages();
		std::shared_ptr<IDentalPlanningUiAdapter> m_UiAdapter;
		IRootEntity* m_RootEntity;
		std::weak_ptr<IPlanRepo> m_PlanRepo;
		DentalPlanningStatus m_State{ DentalPlanningStatus::Initial };
		std::shared_ptr<IPackageConfirmer> m_PackageConfirmer;
		std::shared_ptr<ISimpleDataPackage> m_CurrentPackage = nullptr;
		std::weak_ptr<IPackagePlanRelRepo> m_PackagePlanRelRepo;
		std::shared_ptr<IPlan> m_CurrentPlan;
	};

}