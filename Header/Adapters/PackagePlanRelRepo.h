#pragma once
#include "IPackagePlanRelRepo.h"
#include "IPackagePlanRelFactory.h"

namespace parcast 
{

	class PackagePlanRelRepo : public IPackagePlanRelRepo
	{
	public:
		void SetRelFactory(std::shared_ptr<IPackagePlanRelFactory> relFactory);
		
		std::shared_ptr<IPackagePlanRel> Create(
			std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IPlan> plan) override;

		std::vector<std::shared_ptr<IPackagePlanRel>> GetByPlanUid(const std::string& planUid) const override;

		void DeleteByPackageUid(const std::string& uid) override;

		std::vector<std::shared_ptr<IPackagePlanRel>> GetByPackageUid(const std::string& packageUid) const override;
		void Delete(const std::string& pkgUid, const std::string& planUid) override;

		void DeleteByPlanUid(const std::string& uid) override;
		std::shared_ptr<IPackagePlanRel> Get(const std::string& pkgUid, const std::string& planUid) const override;

	private:
		using TableType = std::map<std::pair<std::string, std::string>, std::shared_ptr<IPackagePlanRel>>;
		
		template<typename T> void EraseIfOnMap(T& condition);

		std::shared_ptr<IPackagePlanRelFactory> m_RelFactory;
		TableType m_Table;
	};

}
