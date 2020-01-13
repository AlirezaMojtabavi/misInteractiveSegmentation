#pragma once

#include "IPackageItemDataAccess.h"
#include "IDataBaseConnection.h"
#include "IPackageItemQueryBuilder.h"

namespace parcast
{

	class PackageItemDataAccess : public IPackageItemDataAccess
	{
	public:
		PackageItemDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection, 
			std::shared_ptr<IPackageItemQueryBuilder> queryBuilder);

		void InsertIfNotExists(const std::string& uid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IPackageItemQueryBuilder> m_QueryBuilder;
	};

}
