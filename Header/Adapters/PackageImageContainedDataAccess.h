#pragma once


#include "IDataBaseConnection.h"
#include "IPackageImageContainedDataAccess.h"
#include "IPackageImageContainedQueryBuilder.h"

namespace parcast
{

	class PackageImageContainedDataAccess : public IPackageImageContainedDataAccess
	{
	public:
		PackageImageContainedDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IPackageImageContainedQueryBuilder> queryBuilder);

		void Insert(const PackageImageContainedData& data) override;
		std::vector<PackageImageContainedData> GetByPackageUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IPackageImageContainedQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}
