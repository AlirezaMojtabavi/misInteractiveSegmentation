#pragma once

#include "IDentalPlanningUiAppSide.h"
#include "ISplineVisualizer.h"

namespace parcast
{
	class IPackageRepo;
	class IPlanningGroupViewer;
	class ISubsequenceUiEventHandler;

	// This class is modeled after the old PlanningHelperObserver. It is used to expose UI (both WPF and VTK) events through 
	// method calls. It is also responsible for synchronizing the states of the WPF and VTK GUI components. It ensures that both 
	// components show the same package, have focus on the same plan, etc., show the same zoom level...
	class DentalPlanningUiAppSide : public IDentalPlanningUiAppSide
	{
	public:
		DentalPlanningUiAppSide(
			ISubsequenceUiEventHandler* subseqEventHandler,
			std::shared_ptr<IPlanningGroupViewer> groupViewer,
			std::shared_ptr<ISplineVisualizer> splineVisualizer);

		void ChangeStatus(const std::string& statusString) override;
		void UpdatePackageList(const PackageViewingListTypedef& packageList) override;
		void SelectPackage(const std::string& packageUid) override;
		void SelectPlan(const std::string& planUid, bool refereshPkg) override;
		void UpdatePlan(std::shared_ptr<IPackagePlanRel> rel) override;
		void UpdatePlanIndicators(const PlanIndicators& indicators) override;
		void UpdatePlanCentricViewAngle(double angle) override;

	private:
		template <class EventType, typename PayloadType>
		void InvokeLoadedEvent(const PayloadType& payload);

		template <class EventType>
		void InvokeUnloadedEvent();

		ISubsequenceUiEventHandler* m_SubseqEventHandler;
		std::shared_ptr<IPlanningGroupViewer> m_GroupViewer;
		std::shared_ptr<IPackageRepo> m_PackageRepo;
		std::shared_ptr<ISplineVisualizer> m_SplineVisualizer;
	};

}
