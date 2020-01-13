#pragma once
#include "IPlanFactory.h"

template < typename CST = std::string >
class ICoordinateSystemCorrelationManager;

namespace parcast
{
	class IPlanTransformCalculator;
	class IPackagePlanRelRepo;
	class ITransformFactory;
	class IPlanRepo;

	class PlanFactory : public IPlanFactory
	{
	public:
		PlanFactory(
			std::weak_ptr<IPackagePlanRelRepo> relRepo,
			std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
			std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
			std::weak_ptr<parcast::ITransformFactory> tranformFactory,
			std::weak_ptr<parcast::IPlanRepo> planRepo);

			std::shared_ptr<IPlan> CreateNewPlan(std::string const& parentImageUid) override;

	private:
		std::weak_ptr<IPackagePlanRelRepo> m_RelRepo;
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> m_corrManager;
		std::weak_ptr<parcast::IPlanTransformCalculator> m_PlanTranformCalculator;
		std::weak_ptr<parcast::ITransformFactory> m_TranformFactory;
		std::weak_ptr<IPlanRepo> m_PlanRepo;
	};

}
