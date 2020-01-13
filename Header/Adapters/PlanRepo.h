#pragma once
#include "IPlanRepo.h"
#include "IPackagePlanRelRepo.h"

class IDatasetManager;

namespace parcast
{

	class IPlanFactory;


	class PlanRepo : public IPlanRepo
	{
	public:
		std::weak_ptr<IPlan> Get(std::string const& uid) override;
		std::weak_ptr<IPlan> CreateNewPlan(std::string  const& parentImageUid) override;
		void SetPlanFactory(std::weak_ptr<IPlanFactory> factory);
		void SetPackagePlanRelRepo(std::weak_ptr<IPackagePlanRelRepo> relRepo);
		std::vector<std::weak_ptr<IPlan>> GetAllPlans() const override;
		void Delete(std::string const& uid) override;
		void Clear() override;

	private:
		std::weak_ptr<IPlanFactory> m_PlanFactory;
		std::vector<std::shared_ptr<IPlan> > m_Plans;
		std::weak_ptr<IPackagePlanRelRepo> m_PackagePlanRelRepo;
	};

}

