#pragma once

class ISimpleDataPackage;

namespace parcast
{

	class IPackageRepo
	{
	public:

		virtual ~IPackageRepo() = default;

		virtual std::shared_ptr<ISimpleDataPackage> Get(const std::string& packageUid) const = 0;
		virtual std::vector<std::shared_ptr<ISimpleDataPackage>> 
			GetBySolutionId(const std::string& solutionId) const = 0;
	};

}
