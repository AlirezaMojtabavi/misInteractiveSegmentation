#pragma once

class ISimpleDataPackage;

namespace parcast
{

	class IPlan;
	class IPackagePlanRel;

	class IPackagePlanRelRepo
	{
	public:
		virtual std::shared_ptr<IPackagePlanRel> Create(
			std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IPlan> plan) = 0;
		virtual std::vector<std::shared_ptr<IPackagePlanRel>> GetByPlanUid(const std::string& planUid) const = 0;
		virtual std::vector<std::shared_ptr<IPackagePlanRel>> GetByPackageUid(const std::string& packageUid) const = 0;
		virtual void DeleteByPackageUid(const std::string& uid) = 0;
		virtual void DeleteByPlanUid(const std::string& uid) = 0;
		virtual void Delete(const std::string& pkgUid, const std::string& planUid) = 0;
		virtual std::shared_ptr<IPackagePlanRel> Get(const std::string& pkgUid, const std::string& planUid) const = 0;
	};

}
