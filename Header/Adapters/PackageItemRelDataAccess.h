#pragma once
#include "IPackageItemRelDataAccess.h"

#include "IDataBaseConnection.h"
#include "IPackageItemRelQueryBuilder.h"

namespace parcast
{

	class PackageItemRelDataAccess : public IPackageItemRelDataAccess
	{
	public:
		PackageItemRelDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection, 
			std::shared_ptr<IPackageItemRelQueryBuilder> queryBuilder);

		void Insert(const PackageItemRelData& data) override;
		std::vector<PackageItemRelData> GetByPackageUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IPackageItemRelQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}
